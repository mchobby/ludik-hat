# Utilisation du Ludik-Hat avec Python

blabla

# Installation

## Activation du bus SPI et I2C
1. Démarrer raspi config avec `sudo-raspi-config`
2. Sélectionner l'option __5 "interfacing options"__
 a. Sélectionner l'option __P4 SPI__ et activer le bus SPI
 b. Sélectionner l'option __P6 I2C__ et activer le bus I2C
 c. Sélectionner l'option __P7 1-Wire__ et activer le bus 1-Wire

## Redémarrer votre Raspberry-Pi

Utiliser la commande `sudo reboot`dans un terminal pour redémarrer le Raspberry-Pi

## Capteur de température 1Wire

Les capteurs 1-Wire DS18B20 sont supportés par Raspberry-Pi OS lui-même.
Si vous connectez un capteur et indiquez à Raspberry-Pi OS qu'il est là alors la température est 
lue par les tâches du système d'exploitation (comme lorsqu'une clé USB est connectée sur le système).

Si le pilote 1-Wire est bien actif et que la carte Ludik-HAT est branchée sur le GPIO alors le répertoire `/sys/bus/w1/devices/` doit 
contenir un sous répertoire commencant par '28-'

Saisir la commande `ls /sys/bus/w1/devices/ | grep 28-*` devrait retourner un résultat similaire à celui-ci:

```
$ ls /sys/bus/w1/devices/ | grep 28-*
28-00000d19eaab
```

## Bibliothèque GpioZero

La bibliothèque `gpiozero`est déjà installée avec le système d'exploitation Raspberry-Pi OS.


## Redémarrer votre Raspberry-pi 

Utiliser un `sudo reboot` pour redémarrer le Raspberry-Pi



# Tester


## test_ds18b20.py

Ce test lit la température depuis le capteur DS18B20 présent sur la carte.

Si plusieurs capteurs sont présents sur le bus 1-Wire alors il est également possible de lire tous les capteurs présents. Ceux-cis sont alors identifiable par leur ROM.

Le fichier d'exemple `[test_ds18b20.py](examples\test_ds18b20.py)` contient une classe `DS18B20` facilitant l'accès aux capteurs.

```
--- Read onboard DS1820 temperature ---
Iteration 0: 25.000 Celcius
Iteration 1: 25.062 Celcius
Iteration 2: 25.000 Celcius
Iteration 3: 25.000 Celcius
Iteration 4: 24.937 Celcius
--- Read all DS1820 sensors on the 1-Wire bus ---
Iteration: 0
    >>> ROM: 8e 01 55 05 7f a5 a5 66 59, Temp: 24.875 Celsius
    >>> ROM: 6e 01 4b 46 7f ff 02 10 71, Temp: 22.875 Celsius
Iteration: 1
    >>> ROM: 8d 01 55 05 7f a5 a5 66 9c, Temp: 24.812 Celsius
    >>> ROM: 6e 01 4b 46 7f ff 02 10 71, Temp: 22.875 Celsius
Iteration: 2
    >>> ROM: 8b 01 55 05 7f a5 a5 66 0f, Temp: 24.687 Celsius
    >>> ROM: 6e 01 4b 46 7f ff 02 10 71, Temp: 22.875 Celsius
Iteration: 3
    >>> ROM: 8b 01 55 05 7f a5 a5 66 0f, Temp: 24.687 Celsius
    >>> ROM: 6d 01 4b 46 7f ff 03 10 70, Temp: 22.812 Celsius
Iteration: 4
    >>> ROM: 89 01 55 05 7f a5 a5 66 89, Temp: 24.562 Celsius
    >>> ROM: 6e 01 4b 46 7f ff 02 10 71, Temp: 22.875 Celsius
```

