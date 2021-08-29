#include <stdio.h>
#include <pigpio.h>
#include <string>
#include <unistd.h> // sleep

#define NUM_LEDS 4

int GPIO_LEDS[4] = { 12, 26, 27, 6 };
std::string GPIO_NAMES[4] = {"Green", "Orange", "Red", "Yellow" };

int main(void){
	printf("Playing with LEDs!\n");
	gpioInitialise();
	for( int i=0; i<NUM_LEDS; i++ )
		gpioSetMode( GPIO_LEDS[i], PI_OUTPUT );

	while( 1 ){
		// Allume les LEDs 1 à 1
		for( int i=0; i<NUM_LEDS; i++ ){
			printf("ON  %d : %s\n", i, GPIO_NAMES[i].data() );
			gpioWrite( GPIO_LEDS[i], 1 );
			sleep( 1 );
		}
		// Eteind les LEDs 1 à 1
		for( int i=0; i<NUM_LEDS; i++ ){
			printf("OFF %d : %s\n", i, GPIO_NAMES[i].data() );
			gpioWrite( GPIO_LEDS[i], 0 );
			sleep( 1 );
		}
	}
}
