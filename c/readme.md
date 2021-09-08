# Utilisation du Ludik-Hat en C

Cette section reprend l'utilisation du Ludik-Hat avec le langage C.

Les exemples utilise le compilateur G++. G++ est le compilateur C++ libre de la collection de compilateur GNU. Celui-ci est déjà installé sur le Raspberry-Pi.

![HAT Ludik avec G++](docs/_static/HAT-LUDIK-CPP.jpg)

La sérigraphie de la carte contient de nombreuses informations permettant d'identifier les GPIOs utilisés par les différents éléments.


# Installation

## Compilateur C++

Les [exemples](examples) utilisent le compilateur `g++` déjà présent sur RaspberryPi-OS. Le compilateur est utilisé conjointement à l'utilitaire `make` (voir [Makefile pour G++](https://earthly.dev/blog/g++-makefile/)) pour faciliter la compilation et génération de l'exécutable.

Vous pourrez trouver la [documentation de pigpio sur cette page](https://abyz.me.uk/rpi/pigpio/cif.html).

## pigpio - Contrôle des GPIOs
Etant donné que WiringPi n'est plus supporté, les codes d'exemples utilisent [pigpio](http://abyz.me.uk/rpi/pigpio/index.html) disposant d'un excellent support et par ailleurs super-rapide.

Avant d'utiliser `pigpio`, il faut démarrer le démon `pigpiod` qui gère les accès du GPIO.

``` bash
sudo pigpiod
```

Les programmes utilisateurs se connectent sur le démon pour manipuler les GPIOs.

Le petit script [gpiotest.sh](docs/gpiotest.sh) permet de tester rapidement le bon fonctionnement du démon `gpiod`. __Ne branchez pas le Ludik-Hat__ pendant l'exécution du script.

``` bash
$ ./gpiotest.sh
This program checks the Pi's (user) gpios.

The program reads and writes all the gpios.  Make sure NOTHING
is connected to the gpios during this test.

The program uses the pigpio daemon which must be running.

To start the daemon use the command sudo pigpiod.

Press the ENTER key to continue or ctrl-C to abort...

Testing...
Pull down on gpio 4 failed.
Pull up on gpio 5 failed.
Pull down on gpio 13 failed.
Skipped non-user gpios: 0 1 28 29 30 31
Tested user gpios: 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27
Failed user gpios: 4 5 13
```
## pigpio - sudo requis

Les programmes utilisateurs utilisant __pigpio__ doivent généralement être lancé avec un __sudo__.

Si vous __oubliez le sudo__ alors il y a de fortes chances que vous puissiez voir le message d'erreur suivant s'afficher à l'écran.

``` bash
$ ./relais
Activating relay once every second!
2021-09-03 17:11:05 initCheckPermitted:
+---------------------------------------------------------+
|Sorry, you don't have permission to run this program.    |
|Try running as root, e.g. precede the command with sudo. |
+---------------------------------------------------------+
```

Une fois __démarré avec sudo__, le programme n'affiche plus de message d'erreur

``` bash
$ sudo ./relais
Activating relay once every second!
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
...
```

## Installer rpi_ws281x - support NéoPixel

L'option la plus prometteuse pour utiliser des NeoPixel est le projet [rpi_ws281x](https://github.com/jgarff/rpi_ws281x) qu'il faut entièrement compiler sur votre Raspberry-Pi.

Cette compilation est longue et fastidieuse (testée sur un Pi400) et nécessite environ 2 heures.

__Il n'est pas nécessaire de compiler le support NeoPixel immédiatement__, vous poyvez déjà profiter des autres fonctionnalités de la carte.

### CMake
Le projet rpi_ws281x est compiler avec l'outil CMake. Ne pouvant être installé depuis les dépôt avec `sudo apt install cmake` suite à une erreur, il a été nécessaire d'installer les sources de CMake puis le compiler.

Installer les sources de cmake depuis et suivez les instructions d'installation [https://cmake.org/install/](https://cmake.org/install/) .

Lors de la compilation, il faut indiquer que l'on n'utilise le support OPENSSL avec CMake. La commande `./bootstrap` devient donc:

``` bash
./bootstrap -- -DCMAKE_USE_OPENSSL=OFF
```

Puis poursuivre les étapes d'installation comme indiqué.

### rpi_ws281x

Cloner le dépôt Github [https://github.com/jgarff/rpi_ws281x.git](https://github.com/jgarff/rpi_ws281x.git) avec:

``` bash
cd ~
git clone https://github.com/jgarff/rpi_ws281x.git
```

puis suivre les instructions d'installation détaillée dans le fichier [Readme](https://github.com/jgarff/rpi_ws281x.git)

La toute dernière phase de l'installation met en place les fichiers headers permettant la création de vos propres programmes.

``` bash
$ sudo make install
[ 77%] Built target ws2811
[100%] Built target test
Install the project...
-- Install configuration: ""
-- Up-to-date: /usr/local/lib/libws2811.a
-- Up-to-date: /usr/local/include/ws2811/ws2811.h
-- Up-to-date: /usr/local/include/ws2811/rpihw.h
-- Up-to-date: /usr/local/include/ws2811/pwm.h
-- Up-to-date: /usr/local/include/ws2811/clk.h
-- Up-to-date: /usr/local/include/ws2811/dma.h
-- Up-to-date: /usr/local/include/ws2811/gpio.h
-- Up-to-date: /usr/local/include/ws2811/mailbox.h
-- Up-to-date: /usr/local/include/ws2811/pcm.h
-- Up-to-date: /usr/local/lib/pkgconfig/libws2811.pc

$ ls /usr/local/include/
ws2811
```

Le programme `test` inclus dans le cycle de compilation de la bibliothèque permettant de tester le bon fonctionnement de l'ensemble.

``` bash
$ ./test
```

La lecture du code de l'exemple [main.c](https://github.com/jgarff/rpi_ws281x/blob/master/main.c) permet de se faire une idée de l'utilisation de la bibliothèque.

Ce qui produit le résultat suivant (voir aussi [cette video sur YouTube](https://youtu.be/4viMzmH2FeQ)):

![Résultat](docs/_static/rpi_281x.jpg)

# Tester

Tous les exemples sont disponibles dans le sous-répertoire [c/examples](examples) du dépôt.

## Hello

Hello est un programme élémentaire accompagné d'un `Makefile` permettant sa compilation.

Pour créer l'exécutable saisissez les commandes suivantes dans un terminal:

```
$ cd examples/hello
$ make
```

Ce qui crée le fichier exécutable `hello` .

Pour tester l'exécutable saisissez simplement la commande suivante dans le terminal.

```
$ ./hello
Hello World!
```

Une fois le programme testé et compilé, l'appel à `make clean` permet d'effacer
les fichiers de compilation et l'exécutable.

## Hello2

Hello2 est un programme élémentaire accompagné d'une dépendance et son `Makefile`.

Le but de cet exemple est plutôt de se familiariser avec un fichier Mafefile plus grand.

## LEDs

Cet exemple très condensé permet allume et éteint la LED verte. Il n'y a pas de source pour cet exemple concis... voyez le second exemple qui fait clignoter toutes les LEDs.

``` c++
#include <stdio.h>
#include <pigpio.h>
#include <unistd.h> // sleep

int main(void){
	gpioInitialise();

	// GPIO 12 = LED Verte / Green LED
	gpioSetMode( 12, PI_OUTPUT );

  // allume - Switch on
	gpioWrite( 12, 1 );
  sleep( 1 );

	// eteindre - Switch off
	gpioWrite( 12, 0 );
}
```

Le code ci-dessous, visible dans [leds.cpp](examples/leds/leds.cpp) active les LEDs une à une (puis les éteints une à une).

``` c++
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
	gpioSetMode( 12, PI_OUTPUT );

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
```

Une fois compilé et exécuté avec un __sudo__ les LEDs du LudikHat s'allume et s'éteignent a tour de rôle.

``` bash
$ make
g++ -c leds.cpp
g++ -Wall -o leds  -lpigpio -lrt -lpthread leds.o


$ sudo ./leds
Playing with LEDs!
ON  0 : Green
ON  1 : Orange
ON  2 : Red
ON  3 : Yellow
OFF 0 : Green
OFF 1 : Orange
OFF 2 : Red
OFF 3 : Yellow
ON  0 : Green
ON  1 : Orange
ON  2 : Red
ON  3 : Yellow
OFF 0 : Green
OFF 1 : Orange
OFF 2 : Red
OFF 3 : Yellow
ON  0 : Green
ON  1 : Orange
ON  2 : Red
ON  3 : Yellow
...
```

## Boutons

Le code ci-dessous, visible dans [buttons.cpp](examples/buttons/buttons.cpp) détecte l'état des boutons toutes les secondes.

``` c++
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
```

Une fois compilé et exécuté avec un __sudo__ les programme affiche l'état des boutons du LudikHat (une fois par seconde).

``` bash
$ make
g++ -c buttons.cpp
g++ -Wall -o buttons  -lpigpio -lrt -lpthread buttons.o
$ sudo ./buttons
Playing with Buttonss!
Bnt1 : release
Btn2 : PRESSED
Btn3 : release
Btn4 : release
---------------------
Bnt1 : release
Btn2 : PRESSED
Btn3 : release
Btn4 : release
---------------------
Bnt1 : PRESSED
Btn2 : release
Btn3 : release
Btn4 : release
---------------------
Bnt1 : release
Btn2 : release
Btn3 : PRESSED
Btn4 : PRESSED
---------------------
Bnt1 : release
Btn2 : release
Btn3 : release
Btn4 : release
...
```

## Potentiomètre et photo-résistance (analogique)

Les lectures analogiques se font par l'intermédiaire du composant MCP3008 présent sur la carte. Ce composant propose 8 entrées analogiques.

![entrées analogiques sur MCP3008](../python/docs/_static/mcp3008.jpg)

Le potentiomètre est branché sur le canal 3 (ch3), ce potentiomètre produit une tension entre 0 et 3.3V en fonction de la position de l'axe du potentiomètre.

La lecture analogique à l'aide de la classe `mcp3008Spi` retourne un nombre entier entre 0 (pour 0V) et 1023 (pour 3.3V).

Si la valeur retournée est 400 alors cela correspond à une tension de 3.3V * 400/1023 = 1.29V.


### Lecture du potentiomètre

L'exemple [analog.cpp](examples/analog/analog.cpp) permet de lire l'état du potentiomètre sur l'entrée 3 du MCP3008.

Le programme effectue 200 lectures puis s'arrête.

``` c++
#include <stdio.h>
#include <unistd.h> // usleep()
#include "mcp3008Spi.h"

using namespace std;

#define DELAY_MS 200
#define POT_ADC_INPUT 3
#define LDR_ADC_INPUT 2

// Entrée du MCP3008 à lire - entry to read on the MCP3008
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
```

La valeur retournée par la méthode `read()` est comprise entre 0 et 1023.

``` bash
$ make
g++ -c mcp3008Spi.cpp
g++ -c analog.cpp
g++ -Wall -o analog  -lpigpio -lrt -lpthread mcp3008Spi.o analog.o
$ ./analog
Read 0/200: ADC ch3 = 356
Read 1/200: ADC ch3 = 356
...
Read 23/200: ADC ch3 = 356
Read 24/200: ADC ch3 = 390
Read 25/200: ADC ch3 = 560
Read 26/200: ADC ch3 = 756
Read 27/200: ADC ch3 = 880
Read 28/200: ADC ch3 = 969
Read 29/200: ADC ch3 = 1023
Read 30/200: ADC ch3 = 1023
Read 31/200: ADC ch3 = 1023
Read 32/200: ADC ch3 = 1023
Read 33/200: ADC ch3 = 838
Read 34/200: ADC ch3 = 662
Read 35/200: ADC ch3 = 506
...
```

### Lecture de la Photo-Résistance

La photo-résistance peut être testé avec le programme d'exemple [analog.cpp](examples/analog/analog.cpp), il suffit de remplacer la ligne:

``` c++
// Entrée du MCP3008 à lire - entry to read on the MCP3008
#define ADC_CHANNEL POT_ADC_INPUT
```

avec

``` c++
// Entrée du MCP3008 à lire - entry to read on the MCP3008
#define ADC_CHANNEL LDR_ADC_INPUT
```

ce qui produit le résultat suivant:

``` c++
$ make
g++ -c analog.cpp
g++ -Wall -o analog  -lpigpio -lrt -lpthread mcp3008Spi.o analog.o
$ ./analog
Read 0/200: ADC ch2 = 803
Read 1/200: ADC ch2 = 804
Read 2/200: ADC ch2 = 803
Read 3/200: ADC ch2 = 803
Read 4/200: ADC ch2 = 803
Read 5/200: ADC ch2 = 803
Read 6/200: ADC ch2 = 802
Read 7/200: ADC ch2 = 803
Read 8/200: ADC ch2 = 802
Read 9/200: ADC ch2 = 800
Read 10/200: ADC ch2 = 800
Read 11/200: ADC ch2 = 800
Read 12/200: ADC ch2 = 798
Read 13/200: ADC ch2 = 796
Read 14/200: ADC ch2 = 788
Read 15/200: ADC ch2 = 742
Read 16/200: ADC ch2 = 621
Read 17/200: ADC ch2 = 611
Read 18/200: ADC ch2 = 564
Read 19/200: ADC ch2 = 385
Read 20/200: ADC ch2 = 293
Read 21/200: ADC ch2 = 255
...
Read 53/200: ADC ch2 = 235
Read 54/200: ADC ch2 = 225
Read 55/200: ADC ch2 = 213
Read 56/200: ADC ch2 = 203
Read 57/200: ADC ch2 = 206
...
```

Le cas de la photo-résistance (LDR) est un peu différent: sa résistance augmente lorsque la lumière diminue (et résistance diminue lorsque la lumière augmente).

Comme un MCP3008 n'est pas capable de lire une résistance, on constitue un pont diviseur de tension avec une résistance de 10 KOhms. Il y a donc un courant qui traverse la photo-résistance + R 10K. Ce courant n'est pas figé, il change puisque la résistance de la photo-résistance change en fonction des conditions lumineuses.

Le canal 2 permet de relever la tension aux bornes de la résistance de 10K qui dépend du courant qui la traverse, courant qui lui-même dépend de la résistance de la photo-résistance (qui dépend la lumière).

__La valeur sur l'ADC augmente si la lumière augmente -et- diminue si la lumière diminue__.

__Remarques__:
* Chaque photo-résistance est différente. Les tensions relevées sont donc sensiblement différentes pour chaque montage.
* Ne touchez pas la photo-résistance avec le doigt car cela modifie aussi sa résistance!

## Joystick

Les sorties analogiques du joystick sont branchés sur les entrées 0 et 1 du MCP3008.

Le joystick est à mi-parcours des résistance en position de repos.

La valeur des l'ADC pour le joystick au repos est de 512 (approximativement). Sinon, la valeur évolue de 0 à 1024 pour le parcours du joystick d'un côté de l'axe au côté opposé.

``` bash
$ make
g++ -c joy.cpp
g++ -c mcp3008Spi.cpp
g++ -Wall -o joystick  -lpigpio -lrt -lpthread joy.o mcp3008Spi.o
$ joystick
-bash: joystick : commande introuvable
$ ./joystick
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 506 : Horz 507
Vert 359 : Horz 507
Vert 0 : Horz 383
Vert 0 : Horz 384
Vert 0 : Horz 383
Vert 0 : Horz 384
Vert 0 : Horz 390
Vert 0 : Horz 398
Vert 0 : Horz 398
Vert 0 : Horz 399
Vert 300 : Horz 420
Vert 506 : Horz 507
Vert 505 : Horz 507
Vert 872 : Horz 507
Vert 1023 : Horz 480
Vert 1023 : Horz 476
Vert 1023 : Horz 477
Vert 1023 : Horz 476
Vert 1023 : Horz 476
Vert 1023 : Horz 476
Vert 972 : Horz 476
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 505 : Horz 507
Vert 579 : Horz 0
Vert 690 : Horz 0
Vert 749 : Horz 0
Vert 775 : Horz 57
Vert 775 : Horz 203
Vert 745 : Horz 507
Vert 676 : Horz 797
Vert 665 : Horz 863
Vert 665 : Horz 1023
Vert 665 : Horz 1023
Vert 667 : Horz 1023
Vert 662 : Horz 904
Vert 506 : Horz 507
Vert 506 : Horz 507
...
```

## Entrées analogiques supplémentaires

Les 4 entrées analogiques encore disponibles sur le MCP3008 restent à disposition et porte les numéros A4 à A7 (correspondant aux canaux 4 à 7).

![Entrées analogiques encore disponibles](../python/docs/_static/analog_inputs-00.jpg)

Celles-ci peuvent donc être utilisées avec du matériel analogique (comme des potentiomètres). __Attention à ne jamais dépasser 3.3V sur une entrée analogique.__

L'exemple ci-dessous permet de relever la tension analogique sur l'entrée A6 (canal 6 du MCP3008).

![Entrées analogiques encore disponibles](../python/docs/_static/analog_inputs-01.jpg)

L'entrée analogique A6 peut être testé avec le programme d'exemple [analog.cpp](examples/analog/analog.cpp), il suffit de remplacer la ligne:

``` c++
// Entrée du MCP3008 à lire - entry to read on the MCP3008
#define ADC_CHANNEL POT_ADC_INPUT
```

avec

``` c++
// Entrée du MCP3008 à lire - entry to read on the MCP3008
#define ADC_CHANNEL 6
```

Ce qui permettra de lire l'entrée analogique.

## Capteur de température DS18B20 (1-Wire)

Lorsque le support 1-Wire est activé dans le menu interface du Raspberry-Pi (voir utilitaire `raspi-config`) alors les périphériques 1-Wire sont accessibles par l'intermédiaire du système de fichiers à l'emplacement `/sys/bus/w1/devices/28-00*/w1_slave` .

Le programme [read_ds18b20.cpp](examples/ds18b20/read_ds18b20.cpp) :
1. liste les sondes DS18B20 connectées sur le bus 1Wire
2. sélectionne la première sonde trouvée
3. Lit la température 1 fois par seconde

Il s'agit principalement d'accès fichiers! La seule subtilité réside au niveau du pointer `w1_addr` (pointeur vers une chaîne de caractères).

`w1_addr` permet d'identifier l'adresse 1Wire (un nom de fichier) sélectionnée pour lire la température.

``` c++
#include <iostream>
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
```

Voici le résultat produit par le programme lorsque l'on place le doigts dessus.

``` bash
$ make
g++ -c ds18b20.cpp
g++ -c read_ds18b20.cpp
g++ -Wall -o read_ds18b20  -lpigpio -lrt -lpthread ds18b20.o read_ds18b20.o

$ ./read_ds18b20
Enumerate DS18B20 sensors!
   28-00000d19fe94 [SELECTED]
 Read temperature from 28-00000d19fe94
   temperature: 23.437000 degrees Celsius
   temperature: 23.437000 degrees Celsius
   temperature: 24.375000 degrees Celsius
   temperature: 25.375000 degrees Celsius
   temperature: 26.000000 degrees Celsius
   temperature: 26.375000 degrees Celsius

```

## Relais

Le petit script d'exemple ci-dessous active/désactive le relais toute les secondes.

``` c++
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
```

Une fois compilé, le programme peut être démarré avec un `sudo`.

``` bash
$ make
g++ -c relais.cpp
g++ -Wall -o relais  -lpigpio -lrt -lpthread relais.o

$ ls
Makefile  relais  relais.cpp  relais.o

$ sudo ./relais
Activating relay once every second!
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
Relay OFF
Relay ON
...
```

## Buzzer

L'utilisation du Piezo Buzzer passe par la manipulation PWM (Pulse Width Modulation) du gpio 13.

En utilisant un cycle utile à 50% et en faisant varier la fréquence du signal PWM, le buzzer produit alors les notes de musiques correspondant à la fréquence (La = 440 Hz).

La bibliothèque `pigpio` dispose de la fonction [gpioPWM()](https://abyz.me.uk/rpi/pigpio/cif.html#gpioPWM) permettant de contrôler le cycle utile d'un GPIO.

La fréquence est fixée à l'aide de [gpioSetPWMfrequency()](https://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency) dont __la résolution est limitée__. Les fréquences PWM possibles dépendent du `sample rate` fixé parmi l'une des valeurs 1, 2, 4, 5, 8, 10 uSec (5 par défaut). __Il ne sera donc pas possible de jouer toutes les notes__ voir [ici pour plus d'informations](https://abyz.me.uk/rpi/pigpio/cif.html#gpioSetPWMfrequency) .

``` c++
#include <stdio.h>
#include <pigpio.h>
#include <string>
#include <unistd.h> // sleep

#define NUM_NOTES 8
#define GPIO_BUZZER 13

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
```

## NeoPixel

Pour utiliser des NeoPixels sur Raspberry-Pi en C/C++ il faut absolument passer par la phase de compilation de la bibliothèque rpi_ws281x (décrite en début de document).

Le code ci-dessous provient de l'exemple [neopixel.cpp](examples/neopixel/neopixel.cpp) . Une fois le programme compilé avec `make`, il sera possible de lancer l'exécutable avec `sudo ./neotest` .

![programme neotest](docs/_static/neotest.jpg)

Les 4 LEDs présentes sur le Ludik-Hat sont déclarées à l'aide de la structure suivante:

``` c++
ws2811_t ledstring =
{
    .freq = WS2811_TARGET_FREQ,
    .dmanum = 10,
    .channel =
		{
        [0] =
				{
            .gpionum = 18,
            .invert = 0,
            .count = 4,
            .strip_type = WS2811_TARGET_FREQ,
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
```

Le bibliothèque fonctionne pour les les RGB+W (avec led Blanche), la LED RGB étant déclarée sur le `channel[0]` tandis que le contrôle de la LED blanche prend place sur le `channel[1]` de la structure.

Le Ludik-Hat n'utilise que des LEDs NeoPixel RGB (sans LED blanche), raison pour laquelle la définition de `channel[1]` est réduite à sa plus simple expression.

``` c++
int main(void){
		ws2811_return_t ret;

		// Initialiser la structure ledstring
		if ((ret = ws2811_init(&ledstring)) != WS2811_SUCCESS) {
        fprintf(stderr, "ws2811_init failed: %s\n", ws2811_get_return_t_str(ret));
        return ret;
    }

		// Fixer la couleur des 4 ière LEDs
		ledstring.channel[0].leds[0] = 0x00200000; // rouge - red
		ledstring.channel[0].leds[1] = 0x00002000; // vert - green
		ledstring.channel[0].leds[2] = 0x00000020; // bleu - blue
		ledstring.channel[0].leds[3] = 0x00201000; // orange

		if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
				fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
				return ret;
		}

		// attendre 10 seconds
		sleep( 10 );

		// Eteindre les LEDs
		for( int i=0; i<4; i++ )
			ledstring.channel[0].leds[i] = 0x00000000;

		if ((ret = ws2811_render(&ledstring)) != WS2811_SUCCESS) {
				fprintf(stderr, "ws2811_render failed: %s\n", ws2811_get_return_t_str(ret));
				return ret;
		}
```

Dans le code ci-dessus, il est possible de voir l'assignation de la première LED en rouge avec:

``` c++
ledstring.channel[0].leds[0] = 0x00200000;
```

La couleur se défini avec un entier 32bits (4 octets) codé en 4 éléments hexadécimaux (0x00 à 0xFF).

La codification est `0xWWRRGGBB` avec:
* __WW__: intensité de la LED blanche donc 0x00 (0) puisque nous n'en avons pas sur le Ludik-Hat
* __RR__: valeur de la composante __rouge__ de 0x00 à 0xFF (donc 0 à 255).
* __GG__: valeur de la composante __verte__ de 0x00 à 0xFF (donc 0 à 255).
* __BB__: valeur de la composante __bleue__ de 0x00 à 0xFF (donc 0 à 255).


# Ressources
* [Ludik-Hat](https://shop.mchobby.be/fr/pi-hats/2114-ludik-hat-un-hat-pour-decouvrir-l-electronique-et-la-programmation-sur-raspberry-pi-3232100021143.html) @ MCHobby
* [pigpio](http://abyz.me.uk/rpi/pigpio/index.html)
* [create Makefile for G++](https://earthly.dev/blog/g++-makefile/)
* [CMake install](https://cmake.org/install/)
* [rpi_ws281x](https://github.com/jgarff/rpi_ws281x)
