#include <stdio.h>
#include "func.h"

int main(void){
	printf("Hello2!\n");
	int r = add_int(45, OFFSET);
	printf( "Add = %i \n", r );
	return 0;
}
