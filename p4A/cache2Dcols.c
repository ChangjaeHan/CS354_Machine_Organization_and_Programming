////////////////////////////////////////////////////////////////////////////////
// This File:        (cache2Dcols.c)
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

int arr2D[3000][500];

int main() {

    for(int i=0; i<500; i++){
        for(int j=0; j<3000; j++){
            arr2D[j][i] = i+j;
        }
    }

}
