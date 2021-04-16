#!/usr/bin/env python 
#-*- coding: utf-8 -*-

import gpiozero as g
import time

RELAYS_GPIO = 5

rel = g.DigitalOutputDevice( RELAYS_GPIO )

while True:
	rel.on()
	time.sleep( 1 )
	rel.off()
	time.sleep( 1 )

