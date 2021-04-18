#!/usr/bin/env python3 
#-*- coding: utf-8 -*-

import Adafruit_SSD1306
from PIL import Image, ImageDraw, ImageFont
disp = Adafruit_SSD1306.SSD1306_128_64(rst=None)

# Initialise l'écran - init display
disp.begin()

# Efface l'écran - Clear display.
disp.clear()
disp.display()


width = disp.width
height = disp.height
image = Image.new('1', (width, height))

# On créé un objet sur lequel on va dessiner
draw = ImageDraw.Draw(image)

# Charge la font par défaut
font = ImageFont.load_default()

# On écrit du texte dans le coin de l'écran en blanc- Draw some text
draw.text((0,0), 'Hello World', font=font, fill=255)

# Actualise l'affichage
disp.image(image)
disp.display()
