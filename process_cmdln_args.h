///
///
/// @file process_cmdln_args
/// @author Jonathan Bateman jmb7342@rit.edu
/// This header file defines funtions for process_cmdln_args.c


#include <stdlib.h>
#include <stdio.h>

#ifndef PROCESS_CMDLN_ARGS_H
#define PROCESS_CMDLN_ARGS_H

// struct for cmd line arguemnts: 
// -bN # proportion of trees that are already burning. 0 < N < 101.
// -cN # probability that a tree will catch fire. 0 < N < 101.
// -dN # density: the proportion of trees in the grid. 0 < N < 101.
// -nN # proportion of neighbors that influence a tree catching fire. -1 < N < 101.
// -pN # number of states to print before quitting. -1 < N < ...
// -sN # simulation grid size. 4 < N < 41.

typedef struct {
     int BN;
     int CN;// all of these values are taken as integers from the user.
     int DN;
     int NN;
     int PN;
     int PN;
} CMD_LN_ARGS;

/// function: print_struct prints out all the values of the struct
/// @param args --> this a pointer to a struct
void print_struct(CMD_LN_ARGS *args);


/// function: -pN is entered --> prints the program header for Wildfire Simulation
/// @param states is the number of times that simulation will run
void  print_header(int states);


/// general help message is printed to stdout when -H option is a cmd ln arg
/// general help message is printed when there is an unknown flag
/// general help message is also printed to stdout
void print_help_message();

    
#endif //PROCESS_CMDLN_ARGS_H 
