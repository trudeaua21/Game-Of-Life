/***********************************************************************
Filename: life.c

Contains implementations of functions to run a simulation of Conway's
Game of Life.

Author: Aaron Trudeau (except for code provided)
***********************************************************************/
#include "life.h"
#include <stdio.h>
#include <stdlib.h>


/***********************************************************************
get_grid creates new memory for a "grid". x is the height and y is the 
width.
@param x the number of rows in the grid
@param y the number of columns in the grid
@return the newly allocated 2D grid array
***********************************************************************/
char** get_grid(int x, int y){
    
    // Allocates the appropriate memory for a 2D array, and exits with
    // an appropriate error message if memory can't be allocated
    char** grid = (char**) malloc(x * sizeof(char*));
    if(grid == NULL){
        exit(12);
    }
    for (int i = 0; i < x; ++i){
        grid[i] = (char*) malloc(y * sizeof(char));
        if(grid[i] == NULL){
            exit(12);
        }
    }
    
    return grid;
}


/***********************************************************************
print_grid attempts to print an x height by y width grid stored at the 
location provided by grid
@param x the number of rows in the grid
@param y the number of columns in the grid
@param grid the 2D array representing the grid
***********************************************************************/
void print_grid(int x, int y, char** grid){
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < y; ++j){
            if(grid[i][j] == 1){
                printf("%c", '0');
            }
            else{
                printf("%c", '.');
            }
            printf("%c", ' ');
        }
        printf("%c", '\n');
    }
}


/***********************************************************************
mutate takes a grid and mutates that grid according to Conway's rules. 
A new grid is returned.
@param x the number of rows in the grid
@param y the number of columns in the grid
@param grid the 2D array representing the grid
@return the mutated grid state after one application of Conway's rules
to the grid
***********************************************************************/
char** mutate(int x, int y, char** grid){
    
    // Creates a copy of the grid to examine without interference
    char** copy = (char**) malloc(x * sizeof(char*));
    if(copy == NULL){
        exit(12);
    }
    for (int i = 0; i < x; ++i){
        copy[i] = (char*) malloc(y * sizeof(char));
        if(copy[i] == NULL){
            exit(12);
        }
    }
    
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < x; ++j){
            copy[i][j] = grid [i][j];
        }
    }
    
    int num_neighbors = 0;
    
    // Uses copy as a function to update grid
    // Note: state of copy does not change
    for(int i = 0; i < x; ++i){
        for(int j = 0; j < x; ++j){
            num_neighbors = get_neighbors(i, j, x, y, copy);
            if(copy[i][j] == 1){
                if(num_neighbors < 2 || num_neighbors > 3){
                    // cell dies
                    grid[i][j] = 0;
                }
                else{
                    // cell stays alive
                    grid[i][j] = 1;
                }
            }
            else if(copy[i][j] == 0){
                if(num_neighbors == 3){
                    // cell comes back to life
                    grid[i][j] = 1;
                }
            }
        }
    }
    free(copy);
    return grid;
}


/***********************************************************************
get_neighbors is a helper method that returns the number of live 
neighbors a cell has.
@param i the x coordinate of the cell
@param j the y coordinate of the cell
@param x the number of rows in the grid
@param y the number of columns in the grid
@param grid the 2D array representing the grid
@return the number of living neighbors the cell has
***********************************************************************/
int get_neighbors(int i, int j, int x, int y, char** grid){
    
    // Tests to ensure that no cell outside of the grid is called
    if(i < 0 || i > x - 1 || j < 0 || j > y - 1){
        return -1;
    }
    
    int num_neighbors = 0;
    
    // Since not all cells can have 8 neighbors due to the bounds of
    // the board, the cell given by i and j is tested to see which
    // of the 8 neighbors it can and cannot have
    if(i > 0 && j > 0)
        if(grid[i-1][j-1] == 1)
            num_neighbors++;
    if(i > 0)
        if(grid[i-1][j] == 1)
            num_neighbors++;
    if(i > 0 && j < y - 1)
        if(grid[i-1][j+1] == 1)
            num_neighbors++;
    if(j > 0)
        if(grid[i][j-1] == 1)
            num_neighbors++;
    if(j < y - 1)
        if(grid[i][j+1] == 1)
            num_neighbors++;
    if(i < x - 1 && j > 0)
        if(grid[i+1][j-1] == 1)
            num_neighbors++;
    if(i < x - 1)
        if(grid[i+1][j] == 1)
            num_neighbors++;
    if(i < x - 1 && j < y - 1)
        if(grid[i+1][j+1] == 1)
            num_neighbors++;
    
    
    return num_neighbors;
}
