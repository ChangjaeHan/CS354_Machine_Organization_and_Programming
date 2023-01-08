////////////////////////////////////////////////////////////////////////////////
// Main File:        (check_board.c)
// This File:        (check_board.c)
// Other Files:      (name of all other files if any)
// Semester:         CS 354 Fall 2022
// Instructor:       deppeler
//
// Author:           (Changjae Han)
// Email:            (chan82@wisc.edu)
// CS Login:         (changjae)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including Peer Mentors, Instructors, and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of
//                   of any information you find.
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data str>
     
/* COMPLETED (DO NOT EDIT):
 * Read the first line of input file to get the size of that board.
 *
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 */
void get_board_size(FILE *fptr, int *size) {
    char *line1 = NULL;
    size_t len = 0;

    if ( getline(&line1, &len, fptr) == -1 ) {
        printf("Error reading the input file.\n");
                free(line1);
        exit(1);
    }

    char *size_chars = NULL;
    size_chars = strtok(line1, DELIM);
    *size = atoi(size_chars);
    // free memory allocated for reading first link of file
      free(line1);
      line1 = NULL;
}

/* TODO:
 * Returns 1 if and only if the board is in a valid Sudoku board state.
 * Otherwise returns 0.
 *
 * A valid row or column contains only blanks or the digits 1-size,
 * with no duplicate digits, where size is the value 1 to 9.
 *
 * Note: p2A requires only that each row and each column are valid.
 *
 * board: heap allocated 2D array of integers
 * size:  number of rows and columns in the board
 */
int valid_board(int **board, int size) {

    // <checkDup>
    // SAA array which saves digits to check whether it has duplicate numbers
    // each index(starting from 1) > 1  means it appears more than 1 -> return 0 (invalid)
    int checkDup[size];
    for (int t=0; t<size; t++) {
        //initialize
        *(checkDup+t) = 0;
    }
    
    //row check
    for (int i=0; i<size; i++) {
        for (int j=0; j<size; j++) {
            // case when a number is bigger than size or invalid(negative)
            if ( *(*(board+i)+j) > size || *(*(board+i)+j) < 0) {
                return 0;
            }
            // ignore 0 and save the number of times of digits in checkDup
            if (*(*(board+i)+j) !=0) {
                *(checkDup+(*(*(board+i)+j)-1)) = *(checkDup+(*(*(board+i)+j)-1)) + 1;
                //if index value is more than 1, means invalid
                if (*(checkDup+(*(*(board+i)+j)-1)) > 1){
                    return 0;
                }
            }
        }
        //initialize
        for (int t=0; t<size; t++) {
            *(checkDup+t) = 0;
        }
    }

    //col check (same principle with row check)
    for (int j=0; j<size; j++) {
        for (int i=0; i<size; i++) {
            if ( *(*(board+i)+j) > size || *(*(board+i)+j) < 0) {
                return 0;
            }
            if (*(*(board+i)+j) !=0) {
                *(checkDup+(*(*(board+i)+j)-1)) = *(checkDup+(*(*(board+i)+j)-1)) + 1;
                if (*(checkDup+(*(*(board+i)+j)-1)) > 1){
                    return 0;
                }
            }
        }
        //initialize
        for (int t=0; t<size; t++) {
            *(checkDup+t) = 0;
        }
    }

    return 1; //valid
}

/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 *
 * A single CLA which is the name of the file that contains board data
 * is required.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 */
int main( int argc, char **argv ) {
     
    // TODO: Check if number of command-line arguments is correct.
    if (argc != 2) {
        printf("Invalid number of command-line arguments.\n");
        exit(1);
    }
    // Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    // Declare local variables.
    int size;
    
    // TODO: Call get_board_size to read first line of file as the board size.
    get_board_size(fp, &size);
    
    // TODO: Dynamically allocate a 2D array for given board size.
    int **board = malloc(sizeof(int *)*size);
    for(int i=0; i<size; i++){
        *(board+i) = malloc(sizeof(int)*size);
    }
    
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading line %i of the file.\n", i+2);
            exit(1);
        }
        token = strtok(line, DELIM);
                for (int j = 0; j < size; j++) {
                    // TODO: Complete the line of code below
                    // to initialize your 2D array.
                    *(*(board+i)+j) = atoi(token);
                    token = strtok(NULL, DELIM);
                }
    }

    // TODO: Call the function valid_board and print the appropriate
    //       output depending on the function's return value.
    //printf("boardstate: %d\n",valid_board(board, size));
    if (valid_board(board, size) == 1){
        printf("valid\n");
    } else {
        printf("invalid\n");
    }
    // TODO: Free all dynamically allocated memory.
    for(int i=0; i<size; i++){
        free(*(board+i));
        *(board+i) = NULL;
    }
    free(board);
    board = NULL;
    free(token);
    token = NULL;
    free(line);
    line = NULL;
                
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    }
       
    return 0;
  }

// s22
