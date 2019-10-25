/***********************************************************************
Filename: file_library.c

Contains implementations of reading/writing functions for saving a state
in Conway's Game of Life.

Author: Aaron Trudeau (except for code provided and when cited)
***********************************************************************/
#include "file_library.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>


/***********************************************************************
read_file reads a string of bytes into memory at the location provided 
by contents.
@param file_name the name of the file to be read
@param contents the pointer to the array which will contain the contents
of the file
@return the size in bytes of the contents read from the file
***********************************************************************/
size_t read_file(char* file_name, char** contents){
	struct stat st;
	stat(file_name, &st);
	FILE* file = fopen(file_name, "r");
	*contents = (char*) malloc(st.st_size * sizeof(char));
	size_t num_bytes = fread(*contents, st.st_size, 1, file);
	fclose(file);
	return st.st_size;
}


/***********************************************************************
write_file writes a string of bytes to disk.
@param file_name the name of the file to be written
@param contents the array holding the contents to be written to the file
@param size the size of the contents array
@return the size in bytes of the contents written to the file
***********************************************************************/
size_t write_file(char* file_name, char* contents, size_t size){
    // From Luke4211 on the class discord
    // Cleans up filename input
    char *rmv = strchr(file_name, '\n');
    if(rmv){
        *rmv = 0;
    }
    
    FILE* file = fopen(file_name, "w");
    size_t num_bytes = fwrite(contents, size, 1, file);
    fclose(file);
    
    return num_bytes;
}
