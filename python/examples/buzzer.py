#!/usr/bin/env python 
#-*- coding: utf-8 -*-

import gpiozero as g
import time

BUZZER_GPIO = 13

buz = g.TonalBuzzer( BUZZER_GPIO )

buz.play('C4') # Do

time.sleep( 1 )

buz.play('D4') # Re

time.sleep( 1 )

buz.play('E4') # Mi

time.sleep( 1 )

buz.play('F4') # Fa

time.sleep(1)

buz.play('G4') # Sol

time.sleep(1)

buz.play('A4') # La

time.sleep(1)

buz.play('B4' ) # Si

time.sleep(1)

buz.stop()
