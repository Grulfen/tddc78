#include"physics.h"
#include"coordinate.h"
#include"definitions.h"
#include<mpi.h>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

enum direction {
    UP,RIGHT,DOWN,LEFT,INSIDE
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

vector<pcord_t> generate_particles(int n, int num_processes)
{
    vector<pcord_t> particles; 
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
    int num_particles;

    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Size of the side of the box
    int side = round(sqrt(size));

    // Dimensions of grid
    int dims[2] = {side, side};

    if(myid == 0){
        if(argc != 3){
            cerr << "Usage: lab4 time_steps num_particles" << endl;
            exit(1);
        } 
        if(side*side != size){
            cerr << "Number of processes must be a square" << endl;
            exit(2);
        }

        time_steps = atoi(argv[1]);
        num_particles = atoi(argv[2]);
    }

    // Broadcast time steps
    MPI_Bcast(&time_steps, 1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, period, 0, &grid);
    MPI_Cart_coords(grid, myid, 2, coords);

    // Get ranks of neighbours
    MPI_Cart_shift(grid, 0, 1, &src, &(neighbours[DOWN]));
    MPI_Cart_shift(grid, 1, 1, &src, &(neighbours[RIGHT]));
    MPI_Cart_shift(grid, 0, -1, &src, &(neighbours[UP]));
    MPI_Cart_shift(grid, 1, -1, &src, &(neighbours[LEFT]));

    if(coords[1] == 0){
        walls[LEFT] = true;
    } 
    if(coords[1] == side-1){
        walls[RIGHT] = true;
    }
    if(coords[0] == 0){
        walls[UP] = true;
    }
    if(coords[0] == side-1){
        walls[DOWN]= true;
    }

    float collision_time, l_pressure = 0.0;
    float g_pressure = 0.0;
    direction dir;
    // Set walls for each process
    cord_t wall = {0.0, float(BOX_HORIZ_SIZE*BOX_HORIZ_SIZE)/float(size), 0.0, float(BOX_VERT_SIZE*BOX_VERT_SIZE)/float(size)};
    /* srand(time(NULL) + myid); */

    vector<pcord_t> particles;

    particles = generate_particles(10000, 1);

    for(int time_step=0;time_step<time_steps;time_step++){

        // Check for collisions and move particles
        for(vector<pcord_t>::iterator a = particles.begin(); a != particles.end() - 1; a++){
            for(vector<pcord_t>::iterator b = a+1; b != particles.end(); b++){
                collision_time = collide(&(*a),&(*b));
                // Collision
                if(collision_time != -1){
                    interact(&(*a), &(*b), collision_time);
                    swap(*(a+1), *(b));
                    a++;
                    break;
                }
            }
            if(collision_time != -1){
                if(a == particles.end())
                    break;
            } else {
                feuler(&(*a), STEP_SIZE);
            }
        }

        /* for(int i = 0;i<size;i++){ */
        /*     if(myid == i && time_step == 1){ */
        /*         cout << myid << ": Before border check: " << particles.size() << endl; */
        /*         cout << "Sized comm down: " << out_comm_buffers[DOWN].size() << endl; */
        /*         cout << "Sized comm up: " << out_comm_buffers[UP].size() << endl; */
        /*         cout << "Sized comm left: " << out_comm_buffers[LEFT].size() << endl; */
        /*         cout << "Sized comm right: " << out_comm_buffers[RIGHT].size() << endl; */
        /*     } */
        /* } */

        MPI_Barrier(grid);
        // Check for wall collisions or border crossings
        vector<pcord_t>::iterator a = particles.begin();
        while(a != particles.end()){
            dir = get_border(&(*a), wall);

            if(dir == INSIDE){
                a++;
            } else if(walls[dir]) {
                l_pressure += wall_collide(&(*a), wall);
                a++;
            } else {
                out_comm_buffers[dir].push_back(*a);
                particles.erase(a++);
            }
        }

        for(int i = 0;i<size;i++){
            if(myid == i && time_step == 1){
                cout << myid << ": After border check: " << particles.size() << endl;
                cout << "Sized comm down: " << out_comm_buffers[DOWN].size() << endl;
                cout << "Sized comm up: " << out_comm_buffers[UP].size() << endl;
                cout << "Sized comm left: " << out_comm_buffers[LEFT].size() << endl;
                cout << "Sized comm right: " << out_comm_buffers[RIGHT].size() << endl;
            }
            MPI_Barrier(grid);
        }


        // Send and recv communication buffers to neighbours
        for(int i = UP; i<=LEFT;i++){
            // Send up
            MPI_Send(&(out_comm_buffers[i][0]),
                    out_comm_buffers[i].size()*sizeof(pcord_t), MPI_BYTE,
                    neighbours[i], i*10+1, grid); 

            /* if(time_step == 1) */
            /*     cout << "After: " << myid << ": timestep: " << time_step << " Direction: " << i << " Neighbour: " << neighbours[i] << endl; */
            // Probe down to get size of incoming buffer
            MPI_Probe(neighbours[(i+2)%4], i*10+1, grid, &status);
            MPI_Get_count(&status, MPI_BYTE, &in_comm_buffer_size);
            // Change size of incoming buffer
            in_comm_buffers[(i+2)%4].resize(in_comm_buffer_size/sizeof(pcord_t));
            // Recv down
            MPI_Recv(&(in_comm_buffers[(i+2)%4][0]), in_comm_buffer_size,
                    MPI_BYTE, neighbours[(i+2)%4], i*10+1, grid, &status);

        }

        MPI_Barrier(grid);
        for(int i=0;i<4;i++){
            /* out_comm_buffers[i].clear(); */
            for(vector<pcord_t>::iterator it = in_comm_buffers[i].begin(); it != in_comm_buffers[i].end(); it++){
                particles.push_back(*it);
            }
        }
    }

    for(int i=0;i<size;i++){
        if(myid == i){
            cout << myid << ": Sized moved: " << particles.size() << endl;
            cout << myid << ": Sized comm down: " << in_comm_buffers[DOWN].size() << endl;
            cout << myid << ": Sized comm up: " << in_comm_buffers[UP].size() << endl;
            cout << myid << ": Sized comm left: " << in_comm_buffers[LEFT].size() << endl;
            cout << myid << ": Sized comm right: " << in_comm_buffers[RIGHT].size() << endl;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Reduce(&l_pressure, &g_pressure, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(myid == 0){
        cout << "Pressure: " << g_pressure/time_steps/WALL_LENGTH << endl;
    }

    MPI_Finalize();

    return 0;
}
