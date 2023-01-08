////////////////////////////////////////////////////////////////////////////////
// Main File:        (sendsig.c)
// This File:        (sendsig.c)
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
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, char **argv){
    //case when invalid number of arguments
    if(argc != 3){
	printf("Usage: sendsig <signal type> <pid>\n");
	exit(1);
    }

    if(strcmp(argv[1],"-u") == 0){
	//error handling: SIGUSR1
	if(kill(atoi(argv[2]),SIGUSR1) == -1){
	    printf("Error: trouble with signalling SIGUSR1\n");
	    exit(1);
	}
    } else if(strcmp(argv[1],"-i") == 0){
	//error handling: SIGINT
	if(kill(atoi(argv[2]),SIGINT) == -1){
	    printf("Error: trouble with signalling SIGINT\n");
	    exit(1);
	}
    } else {
	//error handling: wrong type
        printf("Error: signal type is invalid\n");
	exit(1);
    }

    return 0;
}
