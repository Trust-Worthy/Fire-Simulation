#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "process_cmdln_args.h"
#include "grid_forest.h"
#include "display.h"
#include "globals.h"


int Cycle_Count = 0;
int Cumulative_Changes = 0;
int Time_Step_Changes = 0;
bool Fires_Burning = true;
bool Print_Mode = false;
const char *tree_chars[] = {" ", "Y", "*", "." };
int Num_Fires;

/// call update function --> must check current state of neighbors
/// 


int main(int argc, char * argv[]){
    CMD_LN_ARGS cmd_args = {10,30,50,25,0,10}; // initializing struct to defaul values
    CMD_LN_ARGS *cmd_args_ptr = &cmd_args;

    if(process_args(argc, argv, cmd_args_ptr) == EXIT_FAILURE){
        return EXIT_FAILURE;
    };

    

    
    
    float density = ((float)cmd_args.DN / 100);
    float percent_trees_on_fire = ((float)cmd_args.BN / 100);
    float neighbor_influence = ((float)cmd_args.NN / 100);
    float prob_tree_catching_fire = ((float)cmd_args.CN / 100);
    int dimensions = cmd_args.SN;
    Cell cell_forest[dimensions][dimensions];


    fill_forest(dimensions,density,percent_trees_on_fire,cell_forest,cmd_args_ptr); /// will fill the forest will cells and insert trees

    

   
    ///usleep(1000000);
        
    if(cmd_args.PN > 0){ /// print mode was selected
        ///printf("round %d" ,Cycle_Count);
        while(Cycle_Count <= cmd_args.PN && Fires_Burning){
            ///printf("round %d" ,Cycle_Count);
            
            update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);
            print_stats(dimensions,prob_tree_catching_fire,density,percent_trees_on_fire,neighbor_influence);
            Time_Step_Changes = 0;
            Cycle_Count+=1;
        }
        
    }else{
        clear();
        while(Fires_Burning){

            update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);
            print_stats(dimensions,prob_tree_catching_fire,density,percent_trees_on_fire,neighbor_influence);
            
            usleep(750000);
            
            Time_Step_Changes = 0;// reset time step changes to zero bc the cycle is coming to an end
            Cycle_Count+=1;
        }
    }

    
    

    cmd_args_ptr = NULL;
    

} 
