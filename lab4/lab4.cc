#include"physics.h"
#include"coordinate.h"
#include"definitions.h"
#include<mpi.h>
#include<list>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;

enum direction {
    UP,DOWN,LEFT,RIGHT,INSIDE
};

// Return the border that the particle has crossed or INSIDE
// if no crossing
direction get_border(pcord_t *p, cord_t border)
{
    if(p->x < border.x0){
        return LEFT;
    }
    if(p->x > border.x1){
        return RIGHT;
    }
    if(p->y < border.y0){
        return UP;
    }
    if(p->y > border.y1){
        return DOWN;
    }
    return INSIDE;
}

bool particle_sort(const pcord_t &a, const pcord_t &b)
{
    return a.x < b.x;
}

list<pcord_t> generate_particles(int n, int num_processes)
{
    list<pcord_t> particles; 
    pcord_t tmp_part;
    float r, theta;
    for(int i=0;i<n;i++){
        r = rand()/float(RAND_MAX) * MAX_INITIAL_VELOCITY;
        theta = rand()/float(RAND_MAX)*2*PI;
        tmp_part.vx = r*cos(theta);
        tmp_part.vy = r*sin(theta);
        tmp_part.x = rand()/float(RAND_MAX)*BOX_HORIZ_SIZE/num_processes;
        tmp_part.y = rand()/float(RAND_MAX)*BOX_VERT_SIZE/num_processes;
        particles.push_back(tmp_part);
    }
    return particles;
}

int main(int argc, char** argv)
{

    MPI_Status status;
    MPI_Init(NULL, NULL);
    MPI_Comm grid;

    int myid, size;
    int time_steps;
    // Indicating if there are walls
    // in order up, right, down, left
    bool walls[4] = {false, false, false, false};

    // My coordinates in grid
    int coords[2];

    // Grid is not circular
    int period[2] = {0,0};

    // Ranks of neighbours in order:
    // up, right, down, left
    // MPI_PROC_NULL if no neighbour
    int neighbours[4];

    // Communication buffers
    vector<pcord_t> out_comm_buffers[4];
    vector<pcord_t> in_comm_buffers[4];

    int src;
    int in_comm_buffer_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Size of the side of the box
    int side = round(sqrt(size));

    // Dimensions of grid
    int dims[2] = {side, side};

    if(myid == 0){
        if(argc != 2){
            cerr << "Usage: lab4 time_steps" << endl;
            exit(1);
        } 
        if(side*side != size){
            cerr << "Number of processes must be a square" << endl;
            exit(2);
        }

        time_steps = atoi(argv[1]);
    }

    // Broadcast time steps
    MPI_Bcast(&time_steps, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, period, 0, &grid);
    MPI_Cart_coords(grid, myid, 2, coords);

    // Get ranks of neighbours
    MPI_Cart_shift(grid, 0, 1, &src, &(neighbours[RIGHT]));
    MPI_Cart_shift(grid, 1, 1, &src, &(neighbours[DOWN]));
    MPI_Cart_shift(grid, 0, -1, &src, &(neighbours[LEFT]));
    MPI_Cart_shift(grid, 1, -1, &src, &(neighbours[UP]));

    if(coords[0] == 0){
        walls[LEFT] = true;
    } 
    if(coords[0] == side-1){
        walls[RIGHT] = true;
    }
    if(coords[1] == 0){
        walls[UP] = true;
    }
    if(coords[1] == side-1){
        walls[DOWN]= true;
    }

    float collision_time, l_pressure = 0.0;
    float g_pressure = 0.0;
    direction dir;
    // Set walls for each process
    cord_t wall = {0.0, float(BOX_HORIZ_SIZE*BOX_HORIZ_SIZE)/float(size), 0.0, float(BOX_VERT_SIZE*BOX_VERT_SIZE)/float(size)};
    srand(time(NULL) + myid);

    list<pcord_t> particles, moved, comm_up, comm_down, comm_left, comm_right;

    // Will swap this with particles in time_step loop
    moved = generate_particles(4, 1);

    for(int i=0;i<time_steps;i++){
        particles.swap(moved);

        // While loops so we can remove elements on list as we iterate over it
        // Check for collisions, move collided particles to the moved list
        list<pcord_t>::iterator a = particles.begin();
        while(a != particles.end()){
            list<pcord_t>::iterator b = particles.begin();
            while(b != particles.end()){
                // collide handles the case when a == b
                collision_time = collide(&(*a),&(*b));
                if(collision_time != -1){
                    interact(&(*a), &(*b), collision_time);
                    moved.push_back(*a);
                    moved.push_back(*b);
                    particles.erase(a++);
                    if(a == b){
                        a++;
                    }
                    particles.erase(b);
                    break;
                } 
                b++;
            }
            if(collision_time == -1){
                a++;
            }
        }
        // Move all uncollided particles
        // move to the moved list
        a = particles.begin();
        while(a != particles.end()){
            feuler(&(*a), STEP_SIZE);
            moved.push_back(*a);
            particles.erase(a++);
        }

        // Check for wall collisions of border crossings
        a = moved.begin();
        while(a != moved.end()){
            dir = get_border(&(*a), wall);
            if(dir == INSIDE){
                a++;
            } else if(walls[dir]) {
                l_pressure += wall_collide(&(*a), wall);
                a++;
            } else {
                out_comm_buffers[dir].push_back(*a);
                moved.erase(a++);
            }
        }
        // Send and recv communication buffers to neighbours
        for(int i = UP; i<=LEFT;i++){
            // Send up
            MPI_Send(&(out_comm_buffers[i][0]),
                    out_comm_buffers[i].size()*sizeof(pcord_t), MPI_BYTE,
                    neighbours[i], i*10+1, grid); 
            cout << myid << ": " << i << " Neighbour: " << neighbours[i] << endl;
            // Probe down to get size of incoming buffer
            MPI_Probe(neighbours[(i+2)%4], i*10+1, grid, &status);
            MPI_Get_count(&status, MPI_BYTE, &in_comm_buffer_size);
            // Change size of incoming buffer
            in_comm_buffers[(i+2)%4].resize(in_comm_buffer_size/sizeof(pcord_t));
            // Recv down
            MPI_Recv(&(in_comm_buffers[(i+2)%4][0]), in_comm_buffer_size,
                    MPI_BYTE, neighbours[(i+2)%4], i*10+1, grid, &status);

        }
        cout << in_comm_buffers[0].size() << endl;
        cout << in_comm_buffers[1].size() << endl;
        cout << in_comm_buffers[2].size() << endl;
        cout << in_comm_buffers[3].size() << endl;
    }

    MPI_Reduce(&l_pressure, &g_pressure, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myid == 0){
        cout << "Pressure: " << g_pressure/time_steps/WALL_LENGTH << endl;
    }

    MPI_Finalize();

    return 0;
}
