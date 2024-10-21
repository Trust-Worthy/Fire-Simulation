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

/// @param dimensions the dimensions of the forest
void create_forest(int dimensions);


/// @param density the proportion of the trees in the grid. This will depend on the size of the grid
void fill_forest(float density)


/// @param forest is a pointer to a pointer to a 2d array
char **print_forest(char **forest);

/// @param forest is a pointer to a pointer to a 2d array
void update_forest(char **forest);




#endif
