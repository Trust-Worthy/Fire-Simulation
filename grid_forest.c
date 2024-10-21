///
/// @file grid_forest.c initializes the grid based on cmd line inputs from the user, fills in the grid, and updates the grid
/// @author Jonathan Bateman jmb7342@rit.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "grid_forest.h"
#include "process_cmdln_args.h"


static float DENSITY = 72.0;
static float BURN = 23.0;


///
///
/// @note the Cell being passed in has already been initialized
void add_cell_neighbors(Cell *source_cell){
    if (source_cell != NULL){
        //acessing the EightWay struct field of the Cell
        if(source_cell->my_neighbors != NULL){
        
        }
    }

}




///
/// @param dimensions --> dimensions of the forest as specified by user
/// @param density --> the percentage of cells of the forest that will be filled with trees
/// @param burning_trees --> the percentage of the existing trees in the forest that are burning
/// @param forest --> 2d array 
void fill_forest(int dimensions, float density, float burning_trees, CellState  forest[dimensions][dimensions]){
   
    // change of plan: Cell forest[dimension][dimension] --> a 2d array of Cell Structs
    // fill every item of 2d array with a new Cell struct. Set all fields of that struct to zero or NULL;
    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < dimensions; j++){
            forest[i][j]->x_position = i; // x_position
            forest[i][j]->y_position = j; // y_position
            forest[i][j]->current_state = EMPTY; // enum CellState is EMPTY for time being
            forest[i][j]->next_state = EMPTY; // next state is EMPTY until the update forest function is called
    //fill forest with EMPTY values from the enum  
    for(int i = 0; i <dimensions; i++){
        for(int j = 0; j <dimensions; j++){
            forest[i][j] = EMPTY; // fill with the EMPTY option of the Enum 
        }
    }

    // caluculations --> floor function to get integer num of trees
    int num_trees = floor(density  * (dimensions * dimensions)) ; // ex: 4x4 matrix means 4**2 --> 16 positions.= 
    int num_burn_trees = floor(((burning_trees / 100.0) * num_trees)); // of the x% of cells filled with trees,  burn / (divided) density will determine 
    int live_trees = num_trees - num_burn_trees; 
    
    printf("num_trees: %d\n",num_trees);
    printf("burning trees: %d\n",num_burn_trees);
    printf("living trees: %d\n", live_trees);
    //generate random (x,y) pairs to place the live and burning trees
    int used[dimensions][dimensions];
    // Initialize all elements to 0 bc it's a variable length array;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            used[i][j] = 0;
        }
    }
    int temp_live = live_trees;
    for(int i = 0; i < num_trees; i++){
        int x,y;
        
        do {
            x = rand() % dimensions; // rand x coor
            y = rand() % dimensions; // rand y coor
        } while(used[x][y]); // repeat until unique pair is found

        // mark as used 
        used[x][y] = 1;

        //place live_trees in forest until live trees run out  
        if(temp_live > 0){
            forest[x][y] = TREE;   
            --temp_live;
        }else{
            forest[x][y] = BURNING;
            }       
    }

}

/// @brief print_forest prints out the forest to the terminal. It converts the enum values to chars.
/// @param dimensions the dimensions of the forest
/// @param forest the 2d forest array
void print_forest(int dimensions, CellState forest[dimensions][dimensions]) {
    const char *tree_chars[] = {" ", "Y", "*", "." };

    for (int i = 0; i < dimensions; i++) { // Print every row
        for (int j = 0; j < dimensions; j++) { // Print each cell in the row
            printf("%s ", tree_chars[forest[i][j]]); // Use the enum value to index into tree_chars
        }
        printf("\n"); // Newline after each row
    }
}
int main(int argc, char *argv[]){
    //randomness
    srand(time(NULL));


    // making up values for cmd ln args
    
    float density = DENSITY / 100.0; // 10x10 grid so 100 cells. 38% of these cells will be filled with trees
    
    float burn_trees = BURN;
    int dimension = atoi(argv[1]);
    int total_cells = dimension * dimension;
    CellState forest[dimension][dimension];

    fill_forest(dimensions, density, burn_trees, forest); 

    // create linked Cell data structure
    Cell cells[total_cells] = {0}; // initialize x,y posi & state to 0 and my_neighbors to NULL
    // print values of the forest grid / matrix
    print_forest(dimension, forest);
    
    return EXIT_SUCCESS;    
}
