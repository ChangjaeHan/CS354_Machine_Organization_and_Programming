////////////////////////////////////////////////////////////////////////////////
//
// Main File:        (myMagicSquare.c)
// This File:        (myMagicSquare.c)
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

// Structure that represents a magic square
typedef struct {
    int size;           // dimension of the square
    int **magic_square; // pointer to heap allocated magic square
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, reads it,
 * checks if it's an odd number >= 3 (if not display the requi>
 * error message and exit), and returns the valid number.
 */
int getSize() {
    //get size with some error conditions: must be bigger than or equal to 3 and odd.
    printf("Enter magic square's size (odd integer >=3)\n");
    int inp;
    scanf("%d", &inp);
    if(inp % 2 == 1 && inp >= 3) {
        return inp;
    } else if(inp % 2 == 1 && inp < 3){
        printf("Magic square size must be >= 3.\n");
        exit(1);
    } else if(inp % 2 != 1) {
        printf("Magic square size must be odd.\n");
        exit(1);
    } else {
        printf("Magic square size must be >= 3 and odd.\n");
        exit(1);
    }
}
   
/* TODO:
 * Makes a magic square of size n using the alternate
 * Siamese magic square algorithm from assignment and
 * returns a pointer to the completed MagicSquare struct.
 *
 * n the number of rows and columns
 */
MagicSquare *generateMagicSquare(int n) {

    //dynamic allocated struct: board
    MagicSquare* board = malloc(sizeof(MagicSquare));
    board->size = n;
    board->magic_square = malloc(sizeof(int*)*n);
    for(int i=0; i<n; i++) {
        *(board->magic_square+i) = malloc(sizeof(int)*n);
    }
    //initialize to 0 to check whether it is empty or not
    for(int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            *(*(board->magic_square+i)+j) = 0;
        }
    }
    
    //possible numbers = n X n
    int numbers = n*n;
    int midIdx = (n-1)/2;
    //put 1
    *(*(board->magic_square+midIdx)+n-1) = 1;

    /*Main algorithm: divide into 4 cases to cover all situations visible
     *  If row or col is going to be over 3, then consider cases, and deduct
     *  1. if row or col >=3, -> check value of temporary index, move 2.
     *  2. if there is a number existed -> move to left one col
     *              not                 -> move to right one row and col
     */
    int row = midIdx;
    int col = n-1;
    for(int i=2; i<numbers+1; i++) {
        row++;
        col++;
        if (row == n && col != n) {
            if (*(*(board->magic_square+0)+col) != 0) {
                row--;
                col = col-2;
                *(*(board->magic_square+row)+col) = i;
            } else {
                row = 0;
                *(*(board->magic_square+row)+col) = i;
            }
        }else if (row != n && col == n) {
            if (*(*(board->magic_square+row)+0) != 0) {
                row--;
                col = col-2;
                *(*(board->magic_square+row)+col) = i;
            } else {
                col = 0;
                *(*(board->magic_square+row)+col) = i;
            }
        }else if (row == n && col == n) {
            if (*(*(board->magic_square+0)+0) != 0) {
                row--;
                col = col-2;
                *(*(board->magic_square+row)+col) = i;
            } else {
                row = 0;
                col = 0;
                *(*(board->magic_square+row)+col) = i;
            }
        }else {
            if (*(*(board->magic_square+row)+col) != 0) {
                row--;
                col = col-2;
                *(*(board->magic_square+row)+col) = i;
            }else {
                *(*(board->magic_square+row)+col) = i;
            }
        }
    }
    return board;
}

/* TODO:
 * Opens a new file (or overwrites the existing file)
 * and writes the square in the specified format.
 *
 * magic_square the magic square to write to a file
 * filename the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {

    FILE* fp = fopen(filename, "w");
    fprintf(fp,"%d\n", magic_square->size);
    //write each row, col
    for(int i=0; i<magic_square->size; i++){
        for(int j=0; j<magic_square->size; j++) {
            if(j == magic_square->size-1) {
                fprintf(fp, "%d", *(*(magic_square->magic_square+i)+j));
            }else {
                fprintf(fp, "%d,", *(*(magic_square->magic_square+i)+j));
            }
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/* TODO:
 * Generates a magic square of the user specified size and
 * output the quare to the output filename
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
    // TODO: Check input arguments to get output filename
    FILE* fp = fopen(*(argv+1),"w");
    if(argc != 2) {
        printf("Usage: ./myMagicSquare <output_filename>\n");
        exit(1);
    }
    if(fp == NULL) {
        printf("This is an invalid file\n");
        exit(1);
    }
    fclose(fp);
    
    // TODO: Get magic square's size from user
    int numSize = getSize();
    
    // TODO: Generate the magic square
    MagicSquare* square = generateMagicSquare(numSize);
    
    // TODO: Output the magic square
    fileOutputMagicSquare(square,*(argv+1));
    
    //free all allocated memory
    for(int i=0; i<numSize; i++) {
        free(*(square->magic_square+i));
    }
    free(square->magic_square);
    free(square);
    
    return 0;
 }


 //     F22 deppeler myMagicSquare.c

