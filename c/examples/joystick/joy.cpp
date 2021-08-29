#include <stdio.h>
#include <unistd.h> // usleep()
#include "mcp3008Spi.h"

using namespace std;

#define DELAY_MS 100
#define VERT_ADC_INPUT 1
#define HORZ_ADC_INPUT 0

int main(void) {
		mcp3008Spi adc("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

		while( 1 ) {
			int vert = adc.read( VERT_ADC_INPUT ); // vertical
			int horz = adc.read( HORZ_ADC_INPUT ); // Horizontal
			printf( "Vert %i : Horz %i\n", vert, horz );
			usleep( DELAY_MS * 1000 );
		}
		return 0;
}
