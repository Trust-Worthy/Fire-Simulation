#include <stdlib.h>
#include <stdio.h>



/// function that prints the program header
/// @param states is the number of times that simulation will run
/// @return EXIT_SUCCESS
int print_wildfire_header(int states){
    
    printf(
    "===========================\n"
    "======== Wildfire =========\n"
    "===========================\n"
    "=== Print %d Time Steps ===\n"
    "===========================", states);
    return EXIT_SUCCESS;
}



