#include"physics.h"
#include"coordinate.h"
#include"definitions.h"
#include<mpi.h>
#include<list>
#include<cstdlib>
#include<iostream>

using namespace std;

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
        if(argc != 3){
                fprintf(stderr, "Usage: lab4 num_processes time_steps\n");
                exit(1);
        }

        int time_steps = atoi(argv[2]);
        float collision_time, g_pressure = 0.0;
        cord_t wall = {0.0, BOX_HORIZ_SIZE, 0.0, BOX_VERT_SIZE};
        /* srand(time(NULL)); */

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
                        g_pressure += wall_collide(&(*a), wall);
                }
        }

        cout << "Pressure: " << g_pressure/time_steps/WALL_LENGTH << endl;

        return 0;
}
