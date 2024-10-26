#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "process_cmdln_args.h"
#include "grid_forest.h"
#include "display.h"
#include "globals.h"


int Cycle_Count = 0;
int Cumulative_Changes = 0;
int  Time_Step_Changes = 0;
bool Fires_Burning = true;
bool Print_Mode = false;


/// call update function --> must check current state of neighbors
/// 


int main(int argc, char * argv[]){
    CMD_LN_ARGS cmd_args = {10,30,50,25,0,10}; // initializing struct to defaul values
    CMD_LN_ARGS *cmd_args_ptr = &cmd_args;

    process_args(argc, argv, &cmd_args);
        

    float density = (cmd_args.DN / 100);
    float percent_trees_on_fire = (cmd_args.BN / 100);
    float neighbor_influence = (cmd_args.NN / 100);
    float prob_tree_catching_fire = (cmd_args.CN / 100);
    int dimensions = cmd_args.SN;
    Cell cell_forest[dimensions][dimensions];


    fill_forest(dimensions,density,percent_trees_on_fire,cell_forest,cmd_args_ptr);
    insert_trees_in_forest(dimensions,cell_forest,density,percent_trees_on_fire);
    print_forest(density,Print_Mode,dimensions,cell_forest,cmd_args_ptr);
    
    if(cmd_args.PN > 0){ /// print mode was selected
        Print_Mode = true;
        while(Cycle_Count <= cmd_args.PN && Fires_Burning){
            update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);

            Fires_Burning = false; /// setting this to false to break me out of outer while loop
            break; 
            
        }
        
    }else{
        while(Fires_Burning){
        update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);
        }
    }


    cmd_args_ptr = NULL;

    

} 
