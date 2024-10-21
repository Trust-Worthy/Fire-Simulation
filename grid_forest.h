///
///
/// @file header file that defines functions for the forest_grid.c file
/// @author Jonathan Bateman jmb7342@rit.edu
/// This file creates the grid based on cmd line inputs, fills in the grid with the appropriate amount of trees, and updates the grid

#include <stdio.h>
#include <math.h>
#include <strings.h>

#ifndef FOREST_GRID_H
#define FOREST_GRID_H

///
/// @brief an enum to keep track of the state of a cell
typedef enum CellState {
    EMPTY,
    TREE,
    BURNING,
    BURNED
} CellState;

///
/// @brief this struct defines each individual cells' position in the context of the entire grid
typedef struct point{
    unsigned int x_position = 0;
    unsigned int y_position = 0;
}Cell;

///
/// @brief struct to model the 8-way connectivity between cells
typedef struct EightWay{
     Cell source_cell; // cell that's directly in the middle
     Cell n_cell; // cell that's directly above: (row -1, col)
     Cell nw_cell; // cell that's above and to the left: (row - 1, col -1)
     Cell ne_cell; // cell that's above and to the right: (row - 1, col +1)
     Cell s_cell; // cell that's directly below: (row + 1, col)
     Cell sw_cell; // cell that's below and to the left: (row + 1, col - 1)
     Cell se_cell; // cell that's below and to the right: (row + 1, col + 1)
     Cell e_cell; // cell that's directly to the right: (row, col + 1)
     Cell w_cell; // cell that's directly to the left: (row, col - 1)
}EightWay;

/// @param dimensions the dimensions of the forest
void create_forest(int dimensions);

/// @brief this function fills a 2d array with either a space (non-tree), Y  (living tree)
/// * (burning tree) based on the ENUM! The char values will be changed to chars when printed to terminal
///
/// @param density the proportion of the trees in the grid. This will depend on the size of the grid
/// @param burning_trees the proportion of trees that are already burning at the beginning of the simulation
/// 
/// @note density determines the total number of trees, burning_trees determines the number of burning trees
/// density - burning is the number of live trees
/// lastly, the # of cells in the forest (dimensions (row times col)) - density is the number of non-trees
void fill_forest(float density, float burning_trees);


/// @param forest is a pointer to a pointer to a 2d array
char **print_forest(char **forest);


/// @brief update forest updates the forest based on the current cycle configuration
/// @param forest is a pointer to a pointer to a 2d array
/// @note the update_forest function will call the spread function to determine what cells need to be updated on each cycle
///
void update_forest(char **forest);

/// @brief  The spread function uses eight-way connectivity of neighbors to decide upon a state change for a single tree cell.
/// The spread function first must check that the proportion of neighbors 
/// that are burning is above the level at which a tree becomes susceptible to catching fire.
///
/// @param neighbor_proportion is the -nN cmd line argument that determines what proportion of neighbors must be burning for 
/// the current cell to catch fire.
/// @param forest_cell is a pointer to an individual cell. The cell is either empty, live tree, burning tree, or burnt tree
void spread_function(float neighbor_proportion, char *forest_cell);


#endif
