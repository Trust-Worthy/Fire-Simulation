///
/// @file grid_forest.c initializes the grid based on cmd line inputs from the user, fills in the grid, and updates the grid
/// @author Jonathan Bateman jmb7342@rit.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grid_forest.h"
#include "process_cmdln_args.h"


static float DENSITY = 38.0;
static float BURN = 14.0;

///
/// @param dimensions --> dimensions of the forest as specified by user
/// @param density --> the percentage of cells of the forest that will be filled with trees
/// @param burning_trees --> the percentage of the existing trees in the forest that are burning
/// @param forest --> 2d array 
void fill_forest(int dimensions, float density, float burning_trees,char forest[dimensions][dimensions]){
    
    // caluculations --> floor function to get integer num of trees
    int num_trees = floor(density  * (dimensions **2)) ; // ex: 4x4 matrix means 4**2 --> 16 positions.= 
    int num_burn_trees = floor(((burning_trees / 100.0) * density)); // of the x% of cells filled with trees,  burn / (divided) density will determine 
    

    // implementation of fisher-yates shuffle
    


    for(int i = 0; i <dimensions; i++){
        for(int j =0; j<dimensions; j++){
           forest[i][j] = 'A';
        }
    }
}

void print_forest(int dimensions, char forest[dimensions][dimensions]){ 
    for(int i = 0; i <dimensions; i++){
        for(int j =0; j<dimensions; j++){
           printf(" row: %d col: %d, value: %c\n", i,j, forest[i][j]);
        }
    } 
}

int main(int argc, char *argv[]){
    // making up values for cmd ln args
    
    float density = DENSITY / 100.0; // 10x10 grid so 100 cells. 38% of these cells will be filled with trees
    
    float burn_trees = BURN;
    int dimension = atoi(argv[1]); 
    char forest[dimension][dimension];
    for(int i = 0; i <dimension; i++){
        for(int j = 0; j <dimension; j++){
            forest[i][j] = ' '; 
        }
    }

    fill_forest(dimension, density, burn_trees, forest); 


    // print values of the forest grid / matrix
    print_forest(dimension, forest);
    
    
}
