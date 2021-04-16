#!/usr/bin/env python 
#-*- coding: utf-8 -*-

# Lecture entrees analogique A4 a A7
# Read analog input from A4 to A7

import gpiozero as g
import time, math

inputs = [ g.MCP3008( channel=ch, device=0 ) for ch in (4,5,6,7) ]

while True:
	# entree analogique retourne une valeur entre 0 et 1
	# analog input returns a value between 0 and 1

	# Augmenter l echelle de valeur entre 0 et 1024
	# Just scale them up from 0 to 1024
	values = list( [math.trunc( input.value*1024 ) for input in inputs] )
	print( "A4=%4i, A5=%4i, A6=%4i, A7=%i" % (values[0],values[1],values[2],values[3]) )
	time.sleep(0.200)

