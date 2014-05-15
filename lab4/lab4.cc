#include"physics.h"
#include"coordinate.h"
#include"definitions.h"
#include<mpi.h>
#include<list>
#include<cstdlib>
#include<iostream>
#include<cmath>

using namespace std;

struct wall {
    bool up{false};
    bool right{false};
    bool down{false};
    bool left{false};
};

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
        wall walls;

        // My coordinates in grid
        int coords[2];

        // Grid is not circular
        int period[2] = {0,0};

        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &size);

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

        if(coords[0] == 0){
            walls.left = true;
        }
        if(coords[0] == side-1){
            walls.right = true;
        }
        if(coords[1] == 0){
            walls.up = true;
        }
        if(coords[1] == side-1){
            walls.down = true;
        }

        float collision_time, l_pressure = 0.0;
        float g_pressure = 0.0;
        // Set walls for each process
        cord_t wall = {0.0, float(BOX_HORIZ_SIZE*BOX_HORIZ_SIZE)/float(size), 0.0, float(BOX_VERT_SIZE*BOX_VERT_SIZE)/float(size)};
        srand(time(NULL) + myid);

        list<pcord_t> particles, moved, comm_up, comm_down, comm_left, comm_right;

        // Will swap this with particles in time_step loop
        moved = generate_particles(10000, 1);

        for(int i=0;i<time_steps;i++){
                particles.swap(moved);

                // While loops so we can remove elements on list as we iterate over it
                list<pcord_t>::iterator a = particles.begin();
                while(a != particles.end()){
                        list<pcord_t>::iterator b = particles.begin();
                        while(b != particles.end()){
                                if(a == b){
                                        b++;
                                        continue;
                                }
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
                a = particles.begin();
                while(a != particles.end()){
                        feuler(&(*a), STEP_SIZE);
                        moved.push_back(*a);
                        particles.erase(a++);
                }
                for(list<pcord_t>::iterator a = moved.begin();a != moved.end(); ++a){
                        l_pressure += wall_collide(&(*a), wall);
                }
        }

        MPI_Reduce(&g_pressure, &l_pressure, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

        if(myid == 0){
            cout << "Pressure: " << g_pressure/time_steps/WALL_LENGTH << endl;
        }

        MPI_Finalize();

        return 0;
}
