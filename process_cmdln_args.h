#include <stdlib.h>
#include <stdio.h>

#ifndef 

/// function that prints the program header for Wildfire Simulation
/// @param states is the number of times that simulation will run
int print_wildfire_header(int states){

    printf(
      "===========================\n"
      "======== Wildfire =========\n"
      "===========================\n"
      "=== Print %d Time Steps ===\n"
      "===========================", states);
      return EXIT_SUCCESS;
}
// general help message is printed to stdout when -H option is a cmd ln arg
// general help message is also printed to stdout
int print_general_help_message(){
    
    fprintf(stderr,
    "usage: wildfire [options]
By default, the simulation runs in overlay display mode.
The -pN option makes the simulation run in print mode for up to N states.

Simulation Configuration Options:
 -H  # View simulation options and quit.
 -bN # proportion that a tree is already burning. 0 < N < 101.
 -cN # probability that a tree will catch fire. 0 < N < 101.
 -dN # density: the proportion of trees in the grid. 0 < N < 101.
 -nN # proportion of neighbors that influence a tree catching fire. -1 < N < 101.
 -pN # number of states to print before quitting. -1 < N < ...
 -sN # simulation grid size. 4 < N < 41.


