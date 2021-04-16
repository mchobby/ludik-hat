#!/usr/bin/env python 
#-*- coding: utf-8 -*-

# Lecture PhotoRésistance et Potentiomètre
# LDR & pot reading

import gpiozero as g
import time, math

ldr = g.MCP3008( channel=2, device=0 )
pot = g.MCP3008( channel=3, device=0 )

while True:
	# ldr.value entre 0 et  1
	# lcd.value between 0 and 1
	ldr_value = math.trunc(ldr.value * 1024)
	pot_value = math.trunc(pot.value * 1024)
	print( "ldr=%4i, pot=%4i" % (ldr_value,pot_value) )
	time.sleep(0.200)

