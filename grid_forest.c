///
/// @file grid_forest.c initializes the grid based on cmd line inputs from the user, fills in the grid, and updates the grid
/// @author Jonathan Bateman jmb7342@rit.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grid_forest.h"
#include "process_cmdln_args.h"


static const int DIMENSION = 10;
static char FOREST[DIMENSION][DIMENSION]; //
static float DENSITY = 38.0;
static float BURN = 14.0;

///
/// @param dimensions --> dimensions of the forest as specified by user
/// @param density --> the percentage of cells of the forest that will be filled with trees
/// @param burning_trees --> the percentage of the existing trees in the forest that are burning
/// @param forest --> 2d array 
void fill_forest(int dimensions, float density, float burning_trees,char forest[dimensions][dimensions]){
    // implementation of fisher-yates shuffle

    for(int i = 0; i <dimensions; i++){
        for(int j =0; j<dimensions; j++){
           forest[i][j] += 1;
        }
    }
}

void print_forest(int dimensions, char forest[dimensions][dimensions]){ 
    for(int i = 0; i <dimensions; i++){
        for(int j =0; j<dimensions; j++){
           printf(" row: %d col: %d\n", forest[i][j]);
        }
    } 
}

int main(void){
    // making up values for cmd ln args
    float density = DENSITY / 100.0; // 10x10 grid so 100 cells. 38% of these cells will be filled with trees
    float burning_trees = BURN / DENSITY; // of the x% of cells filled with trees,  burn / (divided) density will determine 
                                        // what percentage start off burning 
   // forest global array is already initialized to 0's in every place 
    fill_forest(DIMENSIONS, density, burning_trees, FOREST); 


    // print values of the forest grid / matrix
    print_forest(DIMENSIONS, FOREST);


}
