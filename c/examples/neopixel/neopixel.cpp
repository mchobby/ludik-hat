// are stpred in /usr/local/include/ws2811/ use -I with g++
#include "clk.h"
#include "gpio.h"
#include "dma.h"
#include "pwm.h"
// #include "version.h"

#include "ws2811.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

// defaults options
#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     10
#define STRIP_TYPE              WS2811_STRIP_GRB // GBR, RGB, BGR  WS2812/SK6812RGB integrated chip+leds

#define LED_COUNT   4

// [0] for RGB component
// [1] for W composant for RGBW (if applicable)
ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
		{
        [0] =
				{
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 255,
        },
        [1] =
				{
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .brightness = 0,
        },
    },
};

// Definition of colors 8bit for White + 24 bits for RGB
ws2811_led_t dotcolors[] = {
    0x00200000,  // red
    0x00201000,  // orange
    0x00202000,  // yellow
    0x00002000,  // green
    0x00002020,  // lightblue
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
};

int main(void){
		printf("Light up the NeoPixels\n");

		ws2811_return_t ret;
		if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

		ledstring.channel[0].leds[0] = 0x00200000; // red
		ledstring.channel[0].leds[1] = 0x00002000; // green
		ledstring.channel[0].leds[2] = 0x00000020; // blue
		ledstring.channel[0].leds[3] = 0x00201000; // orange

		if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
				fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
				return ret;
		}

		printf("wait 10 seconds\n");
		sleep( 10 );
		printf("clear LEDs\n");
		for( int i=0; i<4; i++ )
			ledstring.channel[0].leds[i] = 0x00000000;

		if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
				fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
				return ret;
		}
		printf("That s all folks!\n");
}
