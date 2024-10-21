///
///
/// @file header file that defines functions for the forest_grid.c file
/// @author Jonathan Bateman jmb7342@rit.edu
/// This file creates the grid based on cmd line inputs, fills in the grid with the appropriate amount of trees, and updates the grid
///
/// @note the 2d array of CellStates, the forest, reads its values from the Cell array (data structure) to update, the Cell array data


#include <stdio.h>
#include <math.h>
#include <strings.h>

#ifndef FOREST_GRID_H
#define FOREST_GRID_H

///
/// @brief an enum to keep track of the state of a cell
typedef enum {
    EMPTY,
    TREE,
    BURNING,
    BURNED
} CellState;

typedef struct EightWay EightWay; // forward declaration

///
/// @brief this struct defines each individual cells' position in the context of the entire grid
typedef struct CellPoint{
    unsigned int x_position;
    unsigned int y_position;
    CellState current_state;
    CellState next_state; // this is the game changer. It makes it easy to keep the board and datastructure up to date
    EightWay *my_neighbors;
}Cell;

///
/// @brief struct to model the 8-way connectivity between cells
typedef struct EightWay{
     Cell n_cell; // cell that's directly above: (row -1, col)
     Cell nw_cell; // cell that's above and to the left: (row - 1, col -1)
     Cell ne_cell; // cell that's above and to the right: (row - 1, col +1)
     Cell s_cell; // cell that's directly below: (row + 1, col)
     Cell sw_cell; // cell that's below and to the left: (row + 1, col - 1)
     Cell se_cell; // cell that's below and to the right: (row + 1, col + 1)
     Cell e_cell; // cell that's directly to the right: (row, col + 1)
     Cell w_cell; // cell that's directly to the left: (row, col - 1)
}EightWay;


/// @brief this function fills in all the coordinates values for the neighbors of an individual cell
///
/// @param neighbors is a pointer to an EightWay struct
void add_cell_neighbors(Cell *cell_forest);




/// @brief this function fills a 2d array previously declared  with a value from the CellState enum. 
/// The ENUM values will be changed to their char representation  when printed to terminal
///
/// @param density the proportion of the trees in the grid. This will depend on the size of the grid
/// @param burning_trees the proportion of trees that are already burning at the beginnng of the simulation
/// @param forest is pointer to an array of chars where the cols are the dimensions
///
/// @note density determines the total number of trees, burning_trees determines the number of burning trees
/// density - burning is the number of live trees
/// lastly, the # of cells in the forest (dimensions (row times col)) - density is the number of non-trees
/// @note fill_forest only has to be called once every time the program runs
void fill_forest(int dimensions, float density, float burning_trees, Cell cell_forest[dimensions][dimensions]);

/// @brief printing out a 2d array that represents the forest
/// @param forest is a pointer to a pointer to a 2d array
void print_forest(int dimensions, Cell cell_forest[dimensions][dimensions]);


/// @brief update forest updates the forest based on the current cycle configuration
/// @param dimensions is the dimensions of the grid as specified by the user 
/// @param forest is a pointer to a pointer to a 2d array
/// 
///
/// @note the update_forest function will call the spread function to determine what cells need to be updated on each cycle
///
void update_forest(int dimensions, Cell cell_forest[dimensions][dimensions]);

/// @brief  The spread function uses eight-way connectivity of neighbors to decide upon a state change for a single tree cell.
/// The spread function first must check that the proportion of neighbors 
/// that are burning is above the level at which a tree becomes susceptible to catching fire.
///
/// @param neighbor_proportion is the -nN cmd line argument that determines what proportion of neighbors must be burning for 
/// the current cell to catch fire.
/// @param forest_cell is an individual cell. The cell is either empty, live tree, burning tree, or burnt tree
void spread_function(int row, int col, float neighbor_proportion, Cell specific_forest_cell[row][col]);


#endif
