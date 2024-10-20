///
///
/// @file process_cmdln_args.c
/// @author Jonathan Bateman jmb7342@rit.edu
/// This program processes the cmd line arguments and initializes the state of the wildfire simulation



#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>  // processing for "-fN" command line args
#include "process_cmdln_args.h" // processing specific flags once they are parsed

#define DEFAULT_SIZE   10            ///< used if no override on command line


static size_t the_size = DEFAULT_SIZE; ///< a program setting.

static size_t the_count = 0;         ///< another program setting. default is 0.

/// usage function gives instructions.

static void usage() {
    fprintf( stderr, "\nusage: use_getopt [-H -pNUM -s pos_num]\n" );
    fprintf( stderr, "\t-H is for getting help\n" ); 
    fprintf( stderr, "\t-pN overrides the default count\n" ); 
    fprintf( stderr, "\t-sN overrides the default size\n" ); 
    fprintf( stderr, "\nAn argument pair of \"-p 5\" is same as \"-p5\"\n" ); 
}

/// @param int states is the number of times the simulation will print before quitting. There is no default value.
int print_header(int states){
     printf(
       "===========================\n"
       "======== Wildfire =========\n"
       "===========================\n"
       "=== Print %d Time Steps ===\n"
       "===========================", states);
        
        return EXIT_SUCCESS;
}

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


/// This demonstrates the use of the getopt() function.
/// main : [-H] [-p num] [-s pos_num] [-- ... ] -> int
/// To terminate option flag processing enter the "--" as an argument.
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
            tmpsize = (int)strtol( optarg, NULL, 10 ); // tmp var is used to ensure that the value is not negative
            if ( tmpsize > 0 ) {
                cmds_struct.PN = (size_t)tmpsize; // assigning to struct
                print_header(cmds_struct.PN); 
            } else {
                fprintf( stderr, "The -p got no value; should be an error.\n" );
            }
            break;
            
        case 'H':
            print_help_message(); 
            return EXIT_FAILURE;
            break;

        case 's':
            tmpsize = (int)strtol( optarg, NULL, 10 );
            if ( tmpsize > 0 ) {
                the_size = (size_t)tmpsize;
                printf( "Option %c got the value %d\n", opt, tmpsize );
                break;
            } else {
                fprintf( stderr, "The -s option requires positive value\n" );
                return EXIT_FAILURE;
            }

        default:
            // some unknown, possibly unacceptable option flag
            fprintf( stderr, "Bad option causes failure; ignored.\n" );
            break;
        }
    }

    printf( "\nsettings: " );
    printf( "the_size == %zu;\n", the_size );
    printf( "the_count == %zu;\n", the_count );
    printf( "\n" );

    // // // // // // // // // // // // // // // // // // // // // // // // 
    // this example shows the remaining command line arguments.
    // At this point, optind should equal index of next argument.
    // if there are additional arguments, optind is index of the first one.
    // // // // // // // // // // // // // // // // // // // // // // // // 

    printf( "\n\tREMAINING COMMAND LINE ARGUMENTS: (index: argv[index])\n" );
    for ( int j = optind; j < argc; ++j ) {
        printf( "\t(%d: %s)\n", j, argv[j] );
    }
    printf( "\n" );

    return EXIT_SUCCESS;
}

