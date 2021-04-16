#!/usr/bin/env python 
#-*- coding: utf-8 -*-

# Lecture joystick analogique
# analog joystick read

import gpiozero as g
import time, math

vert = g.MCP3008( channel=1, device=0 )
horz = g.MCP3008( channel=0, device=0 )

while True:
	# vert.value entre 0 et  1
	# vert.value between 0 and 1
	v = math.trunc(vert.value * 1024)
	h = math.trunc(horz.value * 1024)
	print( "Joystick H=%4i, V=%4i" % (h,v) )
	time.sleep(0.200)

