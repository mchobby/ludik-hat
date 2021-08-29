#include <stdio.h>
#include <unistd.h> // usleep()
#include "mcp3008Spi.h"

using namespace std;

#define DELAY_MS 200
#define POT_ADC_INPUT 3
#define LDR_ADC_INPUT 2

// Which entry to read on the MCP3008
#define ADC_CHANNEL POT_ADC_INPUT

int main(void) {
		mcp3008Spi adc("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
		int i = 200;

		while(i > 0) {
			int val = adc.read( ADC_CHANNEL ); // read channel 3 -- Potentiometer
			printf( "Read %i/200: ADC ch%d = %d\n", (200-i), ADC_CHANNEL, val );
			usleep( DELAY_MS * 1000 );
			i--;
		}
		return 0;
}
