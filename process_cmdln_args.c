///
///
/// @file process_cmdln_args.c
/// @author Jonathan Bateman jmb7342@rit.edu
/// This program processes the cmd line arguments and initializes the state of the wildfire simulation



#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>  // processing for "-fN" command line args
#include "process_cmdln_args.h" // processing specific flags once they are parsed

#define BASE_10 10 // will be used for converting string to integers in base 10

// -H option is selected by user
void print_help_message(){
    printf("$ wildfire -H\n"
    "usage: wildfire [options]\n"
    "By default, the simulation runs in overlay display mode.\n"
    "The -pN option makes the simulation run in print mode for up to N states.\n"
    "\n"
    "\n"
    "Simulation Configuration Options:\n"
    "-H  # View simulation options and quit.\n"
    "-bN # proportion of trees that are already burning. 0 < N < 101.\n"
    " -cN # probability that a tree will catch fire. 0 < N < 101.\n"
    " -dN # density: the proportion of trees in the grid. 0 < N < 101.\n"
    "-nN # proportion of neighbors that influence a tree catching fire. -1 < N < 101.\n"
    "-pN # number of states to print before quitting. -1 < N < ...\n"
    "-sN # simulation grid size. 4 < N < 41.\n")
}


///
/// @param args is a pointer to a struct
void print_struct(CMD_LN_ARGS *args){
    
    printf("Values of the struct are below\n");
    printf("-bN: %d\n", args->BN);
    printf("-cN: %d\n", args->CN);
    printf("-dN: %d\n", args->DN);
    printf("-nN: %d\n", args->NN);
    printf("-pN: %d\n", args->PN);
    printf("-sN: %d\n", args->SN);
}
    



/// @param argc the length of the command line arguments array
/// @param argv the array of command line argument strings

int parse_args( int argc, char * argv[] ) {

    int opt; //the option returned from getopt()
    int tmpsize = 0; // a temporary variable for type safety purposes
    CMD_LN_ARGS cmds_struct = {0}; // struct that holds all cmd ln arg vals

    const char *arg_string = "Hb:c:d:n:p:s:"; /// cmd line option requirements 

    while ( (opt = getopt( argc, argv, arg_string) ) != -1 ) { // getopt() returns -1 if there are not more options to process 

        switch ( opt ) {
        case 'p':
            tmpsize = (int)strtol( optarg, NULL, BASE_10); // tmp var is used to ensure that the value is not negative
            if ( tmpsize > 0 ) {
                cmds_struct.PN = (int)tmpsize; // assigning to struct
                print_header(cmds_struct.PN);
                // do some other funtions to make the program run

                return EXIT_SUCCESS;

            } else {
                fprintf( stderr, "(-pN) number of states to print must be an integer in [0...10000].\n" );
                return EXIT_FAILURE; // immediately terminate program
            }
            break;
            
        case 'H':
            print_help_message(); 
            return EXIT_FAILURE;
            break;

        case 's':
            tmpsize = (int)strtol( optarg, NULL, BASE_10);
            if ( tmpsize >= 5 || tmpsize <= 40) { // min size of grid is 5x5 and max size is 40x40
                cmds_struct.SN  = (int)tmpsize;
                break;
            } else {
                fprintf( stderr, "(-sN)  ) simulation grid size must be an integer in [5...40].\n" );
                return EXIT_FAILURE;
            } 
            break;
        case 'b': 
            tmpsize = (int)strtol(optarg,NULL,BASE_10);
            if (tmpsize > 0 || tmpsize < 101){ // 0 < N < 101
                cmds_struct.BN = (int)tmpsize;
            }else { 
                fprintf("(-bN) proportion already burning must be an integer in [1...100].\n")
                return EXIT_FAILURE;
            }
            break;
        case 'c':
            tmpsize = (int)strtol(optarg,NULL,BASE_10);
            if (tmpsize > 0 || tmpsize < 101){ // 0 < N < 101
                cmds_struct.CN = (int)tmpsize;
            }else { 
                fprintf("(-cN) probability a tree will catch fire must be an integer in [1...100].\n")
                return EXIT_FAILURE;
            }
            break;
        case 'd': 
            tmpsize = (int)strtol(optarg,NULL,BASE_10);
            if (tmpsize > 0 || tmpsize < 101){ // 0 < N < 101
                cmds_struct.DN = (int)tmpsize;
            }else { 
                fprintf("(-DN) density of trees in the grid must be an integer in [1...100].\n")
                return EXIT_FAILURE;
            }
            break;
        case 'n':
            tmpsize = (int)strtol(optarg,NULL,BASE_10);
            if (tmpsize > -1 || tmpsize < 101){ // 0 < N < 101
                cmds_struct.NN = (int)tmpsize;
            }else { 
                fprintf("(-nN) %%neighbors influence catching fire must be an integer in[1...100].\n")
                return EXIT_FAILURE;
            }
            break;
        default:
            // some unknown, possibly unacceptable option flag
            fprintf( stderr, "Unknown flag: please try a define flag as listed in the Configuration Options\n" );
            print_help_message();
            break;
        }
    }

    // use cmd ln struct to initialize the simulation
    

    //print out struct for testing purposes
    print_sturct(&cmds_struct);
    
    return EXIT_SUCCESS;
}

