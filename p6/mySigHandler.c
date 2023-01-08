///////////////////////////////////////////////////////////////////////////////
// Main File:        (mySigHandler.c)
// This File:        (mySigHandler.c)
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
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

//global time alarm
int sec = 4;

//global counter to count signal
int counter = 0;


/*
* <sig_handler()>
* it shows PID and current time every 4 sec
*/
void sig_handler(){
    time_t curTime;
    if (time(&curTime) != -1){
        printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&curTime));
    } else{
	printf("Error: time is invalid\n");
	exit(1);
    }
    alarm(sec);
}

/*
* <sig_user()>
* it handles user's signal
*/
void sig_user(){
    printf("SIGUSR1 handled and counted!\n");
    counter++;
}

/*
* <sig_int()>
* it handles user's ctrl-c signal
*/
void sig_int(){
    printf("\n");
    printf("SIGINT handled\n");
    printf("SIGUSR1 was handled %d times. Exiting now\n", counter); 
    exit(0);
}

int main(int argc, char **argv){

    printf("PID and time print every 4 seconds.\n");
    printf("Type Ctrl-C to end the program.\n");

    //three sigaction : 1) alarm 2) user-defined signal 3) ctrl-c signal
    struct sigaction act1,act2,act3;
    //initialize
    memset (&act1, 0, sizeof(act1));
    memset (&act2, 0, sizeof(act2));
    memset (&act3, 0, sizeof(act3));
    act1.sa_handler = sig_handler;
    act2.sa_handler = sig_user;
    act3.sa_handler = sig_int;

    //error handling with the help of lecture notes
    if (sigaction(SIGALRM, &act1, NULL) !=0){
	printf("Error: binding SIGALRM Handler\n");
	exit(1);
    }
    if (sigaction(SIGUSR1, &act2, NULL) !=0){
	printf("Error: binding SIGUSR1 Handler\n");
	exit(1);
    }
    if (sigaction(SIGINT, &act3, NULL) !=0){
	printf("Error: binding SIGINT Handler\n");
	exit(1);
    }

    alarm(sec);
    while(1){
    }
    return 0;
}
