#include <stdio.h>
#include <string>
#include <unistd.h> // sleep
#include "ds18b20.h"

#include <glob.h>

using namespace std;

char sys_path[] = "/sys/bus/w1/devices/28-00*";

char *w1_addr = NULL; // The DS18B20 1Wire address in 16 char len

int main(void){
	printf("Enumerate DS18B20 sensors!\n");
	glob_t glob_result;
	glob(sys_path ,GLOB_TILDE,NULL,&glob_result);
	for(unsigned int i=0; i<glob_result.gl_pathc; ++i){
		if( w1_addr==NULL ){
			printf( "   %s [SELECTED]\n", basename( glob_result.gl_pathv[i] ) );
			w1_addr =  basename(glob_result.gl_pathv[i]);
		} else {
			printf( "   %s \n", basename( glob_result.gl_pathv[i] ) );
		}
	}

	if( w1_addr == NULL ){
		printf("Oups! no DS18B20 detected!");
		return 0;
	}

	printf(" ");
	printf("Read temperature from %s\n", w1_addr);
	double tempNow;
	DS18B20 w1Device1( w1_addr );
	while(1){
		tempNow = w1Device1.getTemp();
		printf( "   temperature: %f degrees Celsius\n", tempNow );
		sleep(1);
	}

	return 0;
}
