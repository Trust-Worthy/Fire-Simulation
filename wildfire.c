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
const char *tree_chars[] = {" ", "Y", "*", "." };


/// call update function --> must check current state of neighbors
/// 


int main(int argc, char * argv[]){
    CMD_LN_ARGS cmd_args = {10,30,50,25,0,10}; // initializing struct to defaul values
    CMD_LN_ARGS *cmd_args_ptr = &cmd_args;

    if(process_args(argc, argv, cmd_args_ptr) == EXIT_FAILURE){
        return EXIT_FAILURE;
    };

    
    fprintf(stdout,"BN: %d\n",cmd_args.BN);
    fprintf(stdout,"CN: %d\n",cmd_args.CN);
    fprintf(stdout,"DN: %d\n",cmd_args.DN);
    fprintf(stdout,"NN: %d\n",cmd_args.NN);
    fprintf(stdout,"PN: %d\n",cmd_args.PN);
    fprintf(stdout,"SN: %d\n",cmd_args.SN);
    



    
    
    float density = ((float)cmd_args.DN / 100);
    float percent_trees_on_fire = ((float)cmd_args.BN / 100);
    float neighbor_influence = ((float)cmd_args.NN / 100);
    float prob_tree_catching_fire = ((float)cmd_args.CN / 100);
    int dimensions = cmd_args.SN;
    Cell cell_forest[dimensions][dimensions];


    printf("density: %f\n",density);
    printf("percent trees on fire: %f\n",percent_trees_on_fire);
    printf("neighbor influence: %f\n",neighbor_influence);
    printf("prob catching fire: %f\n",prob_tree_catching_fire);
    printf("dimensions: %d\n",dimensions);
    printf("\n");
    fill_forest(dimensions,density,percent_trees_on_fire,cell_forest,cmd_args_ptr); /// will fill the forest will cells and insert trees
    
    
    for(int z  = 0; z<5;z++){
        printf("ROUND %d\n",z);
        for(int i = 0; i<dimensions; i++){
                for(int j = 0; j<dimensions;j++){
                    printf("%s", tree_chars[cell_forest[i][j].current_state]);
                    
                        
                }
                printf("\n");
                
            }
        ///print_forest(density,Print_Mode,dimensions,cell_forest,cmd_args_ptr);
        for(int i = 0; i < dimensions; i++){ ///< for the number of cells, call the spread function on every cell
            for(int j = 0; j < dimensions; j++){
                if(cell_forest[i][j].current_state == EMPTY){///<if this cell is EMPTY don't call the spread function
                    continue;
                }else{
                    spread_function(neighbor_influence,prob_tree_catching_fire,&cell_forest[i][j]); ///<identify the specific cell in the 2d array
                }
                
            }       
        }
        for(int i = 0; i<dimensions; i++){
                for(int j = 0; j<dimensions;j++){
                    if(cell_forest[i][j].next_state != EMPTY){
                    change_cell_state(&cell_forest[i][j]);  
                }
                        
                }
                
            }
    }
    
    
    
    
    
    ///print_forest(density, Print_Mode,dimensions, &cell_forest,cmd_args_ptr);
    
    ///update_forest(Print_Mode,density,prob_tree_catching_fire,neighbor_influence,dimensions,cell_forest,cmd_args_ptr);
    
    /*
    for(int i = 0; i<dimensions; i++){
            for(int j = 0; j<dimensions;j++){
                printf("%s", tree_chars[cell_forest[i][j].current_state]);
            }
            printf("\n");
        }
    */
    ///usleep(1000000);
        
    /*
    if(cmd_args.PN > 0){ /// print mode was selected
        Print_Mode = true;
        while(Cycle_Count <= cmd_args.PN && Fires_Burning){
            update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);

            Fires_Burning = false; /// setting this to false to break me out of outer while loop
            break; 
            ///usleep(750000);
        }
        
    }else{
        while(Fires_Burning){
        update_forest(Print_Mode, density,prob_tree_catching_fire, neighbor_influence, dimensions, cell_forest,cmd_args_ptr);
        ///usleep(750000);
        }
    }

    
    

    cmd_args_ptr = NULL;
    */
    

} 
