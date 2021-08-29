#include <stdio.h>
#include <pigpio.h>
#include <string>
#include <unistd.h> // sleep

#define NUM_BTNS 4

int GPIO_BTNS[NUM_BTNS] = { 22, 23, 24, 25 };
std::string GPIO_NAMES[NUM_BTNS] = {"Bnt1", "Btn2", "Btn3", "Btn4" };

int main(void){
	printf("Playing with Buttonss!\n");
	gpioInitialise();
	for( int i=0; i<NUM_BTNS; i++ ) {
		gpioSetMode( GPIO_BTNS[i], PI_INPUT );
		gpioSetPullUpDown( GPIO_BTNS[i],  PI_PUD_UP ); // Set PullUp
	}

	while( 1 ){
		// Allume les LEDs 1 à 1
		for( int i=0; i<NUM_BTNS; i++ ){
			int val = gpioRead( GPIO_BTNS[i] );
			printf("%s : %s\n", GPIO_NAMES[i].data(), val==1 ? "release" : "PRESSED" );
		}
		sleep( 1 );
		printf( "---------------------\n" );
	}
}
