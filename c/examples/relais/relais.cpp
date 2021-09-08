#include <stdio.h>
#include <pigpio.h>
#include <string>
#include <unistd.h> // sleep

#define GPIO_RELAIS  5

int main(void){
	printf("Activating relay once every second!\n");
	gpioInitialise();

	gpioSetMode( GPIO_RELAIS, PI_OUTPUT );

	while( 1 ){
		printf("Relay ON \n" );
		gpioWrite( GPIO_RELAIS, 1 );
		sleep( 1 );
		printf("Relay OFF \n" );
		gpioWrite( GPIO_RELAIS, 0 );
		sleep( 1 );
	}
}
