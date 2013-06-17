#LightMusicHat
© 2013 by Gottfried Mayer http://www.gma.name

##Overview
Arduino project with three LED Strips, each 38 pixels, each with a built-in WS2811 controller chip.
Sound input with a ADMP401 microphone connected to a MSGEQ7 equalizer chip for frequency analysis.

##Schematic
copied top part of https://hackadaycom.files.wordpress.com/2012/09/discoplanetschematic.png

##Hardware
3 x 5050 LED Strips with WS2811 controller chip built in
The strips are mounted around a hat, because the strips are removable they are wired in an "S" form
row 2: ==>  76 77 78 . . . 111 112 113
row 1: <==  75 74 73 . . .  40  39  38
row 0: ==>   0  1  2 . . .  35  36  37
scrolling horizontally poses a problem in this configuration because in rows 0 and 2 the index increases, but in row 1 the index decreases.

##Prerequisites
Uses FastSPI_LED2 (rc1) for controlling the LEDs
https://code.google.com/p/fastspi/downloads/detail?name=FastSPI_LED2.RC1.zip&can=2&q=

##Credits
Inspiration from
http://www.macetech.com/blog/node/118

Mic/MSGEQ7 schematic and code partially copied and modified from
http://hackaday.com/2012/09/11/disco-planet-a-massive-rgbw-led-array-in-a-6-globe/
