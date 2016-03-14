# msp430-music-mouse
A musical hack made with a MSP430 microcontroller and an empty computer mouse

My brother likes hacks and pranks, so I decided to build a computer mouse that would start playing a melody once exposed to sunlight.

The idea was to send it to him in a padded envelope, and as soon as he pulled out the computer mouse, bizarrely enough it would start playing a melody.

He lives far away (different continent), so I used the low-power features of the Texas Instruments MSP430 microcontroller to ensure that it could remain in a "waiting state" for months (probably years) on 2x AA batteries. Only when the package was opened, and the mouse would start playing, the battery would start depleting.

Totally pointless, yes. But I had fun building this.

Components needed:
* Photoresistor and a 1k resistor
* 2x 1.5V AA batteries
* Super cheap MSP430 microcontroller (MSP430F2012 to be exact, see http://www.ti.com/product/MSP430F2012)
* Buzzer for audio

<img src="https://github.com/tk512/msp430-music-mouse/blob/master/components.jpg?raw=true">
<img src="https://raw.githubusercontent.com/tk512/msp430-music-mouse/master/components-with-mouse.jpg">
I put this together in a rush, so it certainly didn't look too good.

Although it all technically worked, someone in Norwegian customs first cracked it open, probably thinking it was some kind of explosive device. I don't really blame them ;-)
