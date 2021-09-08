// Play some notes BUT NOT ALL due to the sample rate limitation of pigpio
// see this link for more informations
//         https://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency 

#include <stdio.h>
#include <pigpio.h>
#include <string>
#include <unistd.h> // sleep

#define NUM_NOTES 8
#define GPIO_BUZZER 13

// Extra notes: Do# 277 Hz, Ré# 311 Hz, Fa# 370 Hz, Sol# 415 Hz, La# 466 Hz
uint NOTE_FREQ[NUM_NOTES] = { 261, 293, 330, 349, 392, 440, 494, 523 };
std::string NOTE_NAMES[NUM_NOTES] = {"Do", "Ré", "Mi", "Fa", "Sol", "La", "Si", "Do" };

int main(void){
	printf("Playing notes on Buzzer\n");
	gpioInitialise();
	gpioPWM( GPIO_BUZZER, 0 ); // PWM @ 0% = OFF

	for( int i=0; i<NUM_NOTES; i++ ){
		// Fix PWM Freq for note + Duty cycle at 50%
		printf( "Playing note %s at %d Hz\n", NOTE_NAMES[i].data(), NOTE_FREQ[i] );
		gpioSetPWMfrequency( GPIO_BUZZER, NOTE_FREQ[i]);
		gpioPWM( GPIO_BUZZER, 128 ); // 0-255
		sleep( 1 );
	}

	gpioPWM( GPIO_BUZZER, 0 ); // PWM @ 0% = OFF
	printf( "C est fini!\n" );
}
