////////////////////////////////////////////////////////////////////////////////
// Main File:        (division.c)
// This File:        (division.c)
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
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

//global counter to count calculations
int counter = 0;

/*
* <sigfpe_handler>
* it handles sigfpe to alert dividing zero
*/
void sigfpe_handler(){
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);
}

/*
* <sigint_handler>
* it handles sigint signal
*/
void sigint_handler(){
    printf("\n");
    printf("Total number of operations completed successfully: %d\n", counter);
    printf("The program will be terminated.\n");
    exit(0);
}


int main(int argc, char** argv){

    struct sigaction fpe, sint;
    //initialize sigaction
    memset (&fpe, 0, sizeof(fpe));
    memset (&sint, 0, sizeof(sint));
    //register handler
    fpe.sa_handler = sigfpe_handler;
    sint.sa_handler = sigint_handler;

    //error handling: SIGFPE
    if(sigaction(SIGFPE, &fpe, NULL) != 0) {
	printf("Error: binding SIGFPE Handler\n");
	exit(1);
    }
    //error handling: SIGINT
    if(sigaction(SIGINT, &sint, NULL) != 0) {
	printf("Error: binding SIGINT Handler\n");
	exit(1);
    }

    //infinite loop to implement division
    while(1){
	printf("Enter first integer: ");
	char buf[100];
	fgets(buf, 100, stdin);
	int numerator = atoi(buf);

	printf("Enter second integer: ");
	fgets(buf, 100, stdin);
	int denominator = atoi(buf);

	int div = numerator/denominator;
	int remain = numerator%denominator;
	printf("%d / %d is %d with a remainder of %d\n", numerator, denominator, div, remain);
        counter++;
    }
    return 0;
}
