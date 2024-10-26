#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "process_cmdln_args.c"
#include "grid_forest.h"
#include "display.h"


static int Cycle_Count = 1;
static int Cumulative_Changes = 0;
static int  Time_Step_Changes = 0;
static bool Fires_Burning = true;
static bool Print_Mode = false;


/// call update function --> must check current state of neighbors
/// 


int main(int argc, char * argv[]){
    CMD_LN_ARGS cmd_args = {10,30,50,25,0,10}; // initializing struct to defaul values
    

    parse_args(argc, argv, &cmd_args); ///<processes cmd line args and overrides cmd_args struct if necessary

    float density = (cmd_args.DN / 100);
    float percent_trees_on_fire = (cmd_args.BN / 100);
    float neighbor_influence = (cmd_args.NN / 100);
    float prob_tree_catching_fire = (cmd_args.CN / 100);
    int dimensions = cmd_args.SN;
    Cell cell_forest[dimensions][dimensions];


    fill_forest(dimensions,density,percent_trees_on_fire,cell_forest);
    insert_trees_in_forest(dimensions,cell_forest,density,percent_trees_on_fire);

    while(Fires_Burning){

        if(cmd_args.PN > 0){ /// print mode was selected
            Print_Mode = true;
            while(Cycle_Count <= cmd_args.PN){
                update_forest(neighbor_influence,prob_tree_catching_fire,dimensions,cell_forest);

                Fires_Burning = false; /// setting this to false to break me out of outer while loop
                break; 
                
            }
        }
        update_forest(neighbor_influence,prob_tree_catching_fire,dimensions,cell_forest);
    }

    myfunt();



} 
