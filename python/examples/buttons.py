#!/usr/bin/env python 
#-*- coding: utf-8 -*-

import gpiozero as g
import time

GPIO_BTN1 = 22
GPIO_BTN2 = 23
GPIO_BTN3 = 24
GPIO_BTN4 = 25


btn1 = g.Button( GPIO_BTN1 )
btn2 = g.Button( GPIO_BTN2 )
btn3 = g.Button( GPIO_BTN3 )
btn4 = g.Button( GPIO_BTN4 )

while True:
	for btn,name  in ((btn1,'btn1'),(btn2,'btn2'),(btn3,'btn3'),(btn4,'btn4') ):
		if btn.is_pressed:
			print( "%s pressed" % name )
	time.sleep(0.100)

