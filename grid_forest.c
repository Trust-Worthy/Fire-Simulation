///
/// @file grid_forest.c initializes the grid based on cmd line inputs from the user, fills in the grid, and updates the grid
/// @author Jonathan Bateman jmb7342@rit.edu

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include "grid_forest.h"
#include "process_cmdln_args.h"


static float DENSITY = 72.0;
static float BURN = 23.0;


/// @brief func sets pointers to potential neighbors to NULL because this cell is in the corner position
/// @param cell 
/// @param source_x 
/// @param source_y 
void set_corner_cell_neighbors(Cell *cell,int dimensions,Cell cell_forest[dimensions][dimensions]){
    int source_x = cell->x_position;
    int source_y = cell->y_position;
    if(source_x == 0 && source_y == 0){ ///< upper left corner
        cell->my_neighbors.n_cell = NULL;
        cell->my_neighbors.ne_cell = NULL;
        cell->my_neighbors.nw_cell = NULL;
        cell->my_neighbors.w_cell = NULL;
        cell->my_neighbors.sw_cell = NULL;
        /// existing neighbors
        
        cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
        cell->my_neighbors.se_cell = &cell_forest[get_south_east_x_coor(source_x)][get_south_east_y_coor(source_y)];
        cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
    }else if(source_x == 0 && source_y == dimensions-1) {///<upper right corer
        cell->my_neighbors.n_cell = NULL;
        cell->my_neighbors.ne_cell = NULL;
        cell->my_neighbors.nw_cell = NULL;
        cell->my_neighbors.e_cell = NULL;
        cell->my_neighbors.se_cell = NULL;
        /// existing neighbors
        cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_west_y_coor(source_y)];
        cell->my_neighbors.sw_cell = &cell_forest[get_south_west_x_coor(source_x)][get_south_west_y_coor(source_y)];
        cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
    }else if(source_x == dimensions-1 && source_y == 0){///< bottom left corner
        cell->my_neighbors.s_cell = NULL;
        cell->my_neighbors.se_cell = NULL;
        cell->my_neighbors.sw_cell = NULL;
        cell->my_neighbors.w_cell = NULL;
        cell->my_neighbors.nw_cell = NULL;
        /// existing neighbors
        cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        cell->my_neighbors.ne_cell = &cell_forest[get_north_east_x_coor(source_x)][get_north_east_y_coor(source_y)];
        cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
    }else{///< bottom right corner
        cell->my_neighbors.s_cell = NULL;
        cell->my_neighbors.se_cell = NULL;
        cell->my_neighbors.sw_cell = NULL;
        cell->my_neighbors.e_cell = NULL;
        cell->my_neighbors.ne_cell = NULL;
        /// existing neighbors
        cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        cell->my_neighbors.nw_cell = &cell_forest[get_north_west_x_coor(source_x)][get_north_west_y_coor(source_y)];
        cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_west_y_coor(source_y)];
    }
    
    
}
void set_first_col_cell_neighbors(Cell *cell,int dimensions,Cell cell_forest[dimensions][dimensions]){
        int source_x = cell->x_position;
        int source_y = cell->y_position;
        
        ///<non existing neighbors
        
        cell->my_neighbors.nw_cell = NULL;
        cell->my_neighbors.w_cell = NULL;
        cell->my_neighbors.sw_cell = NULL;
        /// existing neighbors
        cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
        cell->my_neighbors.se_cell = &cell_forest[get_south_east_x_coor(source_x)][get_south_east_y_coor(source_y)];
        cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
        cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        cell->my_neighbors.ne_cell = &cell_forest[get_north_east_x_coor(source_x)][get_north_east_y_coor(source_y)];

}
void set_last_col_cell_neighbors(Cell *cell,int dimensions, Cell cell_forest[dimensions][dimensions]){
        int source_x = cell->x_position;
        int source_y = cell->y_position;
        ///<non existing neighbors
        cell->my_neighbors.e_cell = NULL;
        cell->my_neighbors.se_cell = NULL;
        cell->my_neighbors.ne_cell = NULL;
        
        /// existing neighbors
        cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        cell->my_neighbors.nw_cell = &cell_forest[get_north_west_x_coor(source_x)][get_north_west_y_coor(source_y)];
        cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_west_y_coor(source_y)];
        cell->my_neighbors.sw_cell = &cell_forest[get_south_west_x_coor(source_x)][get_south_west_y_coor(source_y)];
        cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
}
void set_first_row_cell_neighbors(Cell *cell,int dimensions, Cell cell_forest[dimensions][dimensions]){
    int source_x = cell->x_position;
    int source_y = cell->y_position;

    ///<non existing neighbors
        
        cell->my_neighbors.ne_cell = NULL;
        cell->my_neighbors.n_cell = NULL;
        cell->my_neighbors.nw_cell = NULL;
        
        /// existing neighbors
        cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
        cell->my_neighbors.se_cell = &cell_forest[get_south_east_x_coor(source_x)][get_south_east_y_coor(source_y)];
        cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_west_y_coor(source_y)];
        cell->my_neighbors.sw_cell = &cell_forest[get_south_west_x_coor(source_x)][get_south_west_y_coor(source_y)];
        cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
}
void set_last_row_cell_neighbors(Cell *cell,int dimensions, Cell cell_forest[dimensions][dimensions]){
    int source_x = cell->x_position;
    int source_y = cell->y_position;

    ///<non existing neighbors
        cell->my_neighbors.sw_cell = NULL;
        cell->my_neighbors.s_cell = NULL;
        cell->my_neighbors.se_cell = NULL;
        
        
        /// existing neighbors
        cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
        cell->my_neighbors.ne_cell = &cell_forest[get_north_east_x_coor(source_x)][get_north_east_y_coor(source_y)];
        cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        cell->my_neighbors.nw_cell = &cell_forest[get_north_west_x_coor(source_x)][get_north_west_y_coor(source_y)];
        cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_west_y_coor(source_y)];
        
}

/// @brief 
/// @param dimensions 
/// @param source_cell 
/// @param cell_forest 
void add_cell_neighbors(int dimensions, Cell *source_cell, Cell cell_forest[dimensions][dimensions]){
    if(source_cell == NULL){
        fprintf(stderr,"source cell ptr is null\n"); //something is up with the pointer I'm passing in
        return;
    }
    
    int source_x = source_cell->x_position;
    int source_y = source_cell->y_position;

    if(source_x < 0 || source_x > dimensions -1 || source_y < 0 || source_y > dimensions-1){
        fprintf(stderr,"X coor: %d & Y coor: %d are out of bounds\n",source_x,source_y);
        return; // Exit the function if out of bounds
    }

    /// @note cells that are in corner positions def won't have neighbors in certain directions
    /// so set those empty spots to null
        
    if(is_corner_cell(source_x,source_y,dimensions)){
        set_corner_cell_neighbors(source_cell,dimensions,cell_forest);
    }else if(is_in_first_col(source_y)){
        /// set neighbors for first col cells
        set_first_col_cell_neighbors(source_cell,dimensions,cell_forest);
    }else if(is_in_first_row(source_x)){
        /// set neighbors for first row neighbors
        set_first_row_cell_neighbors(source_cell,dimensions, cell_forest);
    }else if(is_in_last_col(source_y,dimensions)){
        /// set neighbors for last col cells
        set_last_col_cell_neighbors(source_cell,dimensions, cell_forest);
    }else if(is_in_last_row(source_x,dimensions)){
        /// set neighbors for last row cells
        set_first_row_cell_neighbors(source_cell,dimensions, cell_forest);
    }else{

        /// @note this is every other type of cell that isn't either a corner cell

        /// @note this is the cell to the north of the source cell 
        ///wow the & operator changed everything
        source_cell->my_neighbors.n_cell = &cell_forest[get_north_x_coor(source_x)][get_north_y_coor(source_y)];
        /// @note this is the cell to the north east of the source cell
        source_cell->my_neighbors.ne_cell = &cell_forest[get_north_east_y_coor(source_x)][get_north_east_y_coor(source_y)];
        /// @note this is the cell to the northwest of the source cell
        source_cell->my_neighbors.nw_cell = &cell_forest[get_north_west_x_coor(source_x)][get_north_west_y_coor(source_y)];
        /// @note this is the cell to the south of the source cell
        source_cell->my_neighbors.s_cell = &cell_forest[get_south_x_coor(source_x)][get_south_y_coor(source_y)];
        /// @note this is the cell to the southeast of the source cell
        source_cell->my_neighbors.se_cell = &cell_forest[get_south_east_x_coor(source_x)][get_south_east_y_coor(source_y)];
        /// @note this is the cell to the southwest of the source cell
        source_cell->my_neighbors.sw_cell = &cell_forest[get_south_west_x_coor(source_x)][get_south_west_y_coor(source_y)];
        /// @note this is the cell to the east of the source cell
        source_cell->my_neighbors.e_cell = &cell_forest[get_east_x_coor(source_x)][get_east_y_coor(source_y)];
        /// @note this is the cell to the west of the source cell
        source_cell->my_neighbors.w_cell = &cell_forest[get_west_x_coor(source_x)][get_south_y_coor(source_y)];


        /// how do I tell if a cell doesn't have neighbors in a certain direction??
    }
    

}



///
/// @param dimensions --> dimensions of the forest as specified by user
/// @param density --> the percentage of cells of the forest that will be filled with trees
/// @param burning_trees --> the percentage of the existing trees in the forest that are burning
/// @param forest --> 2d array 
void fill_forest(int dimensions, float density, float burning_trees, Cell cell_forest[dimensions][dimensions]){
    Cell *cell_ptr = NULL;
    
    // change of plan: Cell forest[dimension][dimension] --> a 2d array of Cell Structs
    // fill every item of 2d array with a new Cell struct. Set all fields of that struct to zero or NULL;
    for(int i = 0; i < dimensions; i++){
        for(int j = 0; j < dimensions; j++){
            cell_ptr = &cell_forest[i][j]; 
            cell_forest[i][j].x_position = i; /// x_position
            cell_forest[i][j].y_position = j; ///y_position
            cell_forest[i][j].current_state = EMPTY; // enum CellState is EMPTY for time being
            cell_forest[i][j].next_state = EMPTY; // next state is EMPTY until the update forest function is called
            
            /// Initialize my_neighbors to NULL for all directions
            cell_forest[i][j].my_neighbors.n_cell = NULL;
            cell_forest[i][j].my_neighbors.ne_cell = NULL;
            cell_forest[i][j].my_neighbors.e_cell = NULL;
            cell_forest[i][j].my_neighbors.se_cell = NULL;
            cell_forest[i][j].my_neighbors.s_cell = NULL;
            cell_forest[i][j].my_neighbors.sw_cell = NULL;
            cell_forest[i][j].my_neighbors.w_cell = NULL;
            cell_forest[i][j].my_neighbors.nw_cell = NULL;
            
            add_cell_neighbors(dimensions,cell_ptr,cell_forest);///< This is the game changer line
            
            ///cell_forest[i][j].my_neighbors = NULL; // setting all neighbors to zero for the time being
            // when it comes time to populate my_neighbors, I have to point this pointer to the correct Cell in the cell_forest
        }
    }

    cell_ptr == NULL; // setting pointer back to NULL. Don't want no dangling pointers now
    
    
    /// cell_forest already is pointer
    insert_trees_in_forest(dimensions,cell_forest,density,burning_trees);

}

void insert_trees_in_forest(int dimensions, Cell *cell_forest[dimensions][dimensions],float density,float burning_trees){
    // caluculations --> floor function to get integer num of trees
    int num_trees = floor(density  * (dimensions * dimensions)) ; // ex: 4x4 matrix means 4**2 --> 16 positions.= 
    int num_burn_trees = floor(((burning_trees / 100.0) * num_trees)); // of the x% of cells filled with trees,  burn / (divided) density will determine 
    int live_trees = num_trees - num_burn_trees; 
    
    printf("num_trees: %d\n",num_trees);
    printf("burning trees: %d\n",num_burn_trees);
    printf("living trees: %d\n", live_trees);

    //generate random (x,y) pairs to place the live and burning trees
    int used[dimensions][dimensions];
    // Initialize all elements to 0 bc it's a variable length array;
    for (int i = 0; i < dimensions; i++) {
        for (int j = 0; j < dimensions; j++) {
            used[i][j] = 0;
        }
    }
    int temp_live = live_trees;
    for(int i = 0; i < num_trees; i++){
        int x,y;
        
        do {
            x = rand() % dimensions; // rand x coor
            y = rand() % dimensions; // rand y coor
        } while(used[x][y]); // repeat until unique pair is found

        // mark as used 
        used[x][y] = 1;

        //place live_trees in forest until live trees run out  
        if(temp_live > 0){
            (*cell_forest)[x][y].current_state = TREE; // field of Cell struct
            --temp_live;
        }else{
            (*cell_forest)[x][y].current_state =  BURNING; //field of Cell struct
            }       
    }
}

/// @brief print_forest prints out the forest to the terminal. It converts the enum values to chars.
/// @param dimensions the dimensions of the forest
/// @param forest the 2d forest array
void print_forest(int dimensions, Cell cell_forest[dimensions][dimensions]) {
    const char *tree_chars[] = {" ", "Y", "*", "." };

    for (int i = 0; i < dimensions; i++) { // Print every row
        for (int j = 0; j < dimensions; j++) { // Print each cell in the row
            printf("%s ", tree_chars[cell_forest[i][j].current_state]); // current_state field from the Cell struct being used to index tree_chars
        }
        printf("\n"); // Newline after each row
    }
}
int main(int argc, char *argv[]){

    if(argc < 2){
        return EXIT_FAILURE;
    }
    //randomness
    srand(time(NULL));


    // making up values for cmd ln args
    
    float density = DENSITY / 100.0; // 10x10 grid so 100 cells. 38% of these cells will be filled with trees
    
    float burn_trees = BURN;
    int dimension = atoi(argv[1]);
    //int total_cells = dimension * dimension;
    //CellState forest[dimension][dimension]; // changed to Cell Struct 2d array on line 133 


    // create 2d array Cell data structure
    Cell cell_forest[dimension][dimension];  // initialize x,y posi & state to 0 and my_neighbors to NULL
    fprintf(stdout,"Created the cell forest\n");
    fill_forest(dimension, density, burn_trees, cell_forest); 

    // print values of the forest grid / matrix
    print_forest(dimension, cell_forest);
    
    return EXIT_SUCCESS;    
}
