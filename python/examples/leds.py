#!/usr/bin/env python 
#-*- coding: utf-8 -*-

import gpiozero as g
import time

GPIO_RED    = 12 # LED red/rouge
GPIO_ORANGE = 26 # LED orange
GPIO_GREEN  = 27 # LED green/verte
GPIO_YELLOW = 6  # LED yellow/jaune

red    = g.LED( GPIO_RED ) 
orange = g.LED( GPIO_ORANGE )
green  = g.LED( GPIO_GREEN )
yellow = g.LED( GPIO_YELLOW )

while True:
	red.on()
	time.sleep(1)
	red.off()
	orange.on()
	time.sleep(1)
	orange.off()
	green.on()
	time.sleep(1)
	green.off()
	yellow.on()
	time.sleep(1)
	yellow.off()


