#include <stdio.h>
#include <stdlib.h>

int adding(int x, int y){

    int ret = x + y;

    return ret;
}


int main(){

    int x = 1;
    int y = 5;

    int result = 0;
    while (result < 20){

	result = adding(x,y);
	printf("result is %d", result);
	x++;
	y++;

    }

}
