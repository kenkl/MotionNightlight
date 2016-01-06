##MotionNightlight
======
An Arduino-based motion-activated nightlight

Going to the bathroom at 2am doesn't have to be a retina-searing affair. With lighting in the red-end of the visible spectrum, night-vision is preserved (for the trip back to bed), and sleep-cycle is less disturbed (I consistently fall back to sleep within five minutes). This is an Arduino-based solution that uses a passive infrared sensor to detect motion and turn on a bank of LEDs to light the bathroom for a period of time. The "lights on" period is extended while the lights are on and additional motion is detected. The lights will go out if no motion is detected after an adjustible (in code) period.

The 1.0.0 version of this project utilizes an [Adafruit DC Boarduino](https://www.adafruit.com/products/72) mounted on a [perfboard](https://www.adafruit.com/products/1609). It "listens" for motion via [PIR](https://www.adafruit.com/products/189) to switch on a [bank of LEDs](http://i.imgur.com/6uAZnqK.jpg) connnected via a [TIP120 Darlington transistor](https://www.adafruit.com/products/976). [This](http://i.imgur.com/70N5cCH.jpg) is what the current version of the project looks like. The PIR is connected via the CAT6 cable shown, and effectively [lights up the entire bathroom](http://i.imgur.com/RgfqifA.jpg) when activated.

A Fritzing diagram of the circuit is included. There isn't a Fritzing part for the DC Boarduino, so I used the USB Boarduino (same layout) instead. Of note there is that Collector on the TP120 *must* be connected to a source with sufficient current to light the LEDs connected to the Emitter. For this version, I'm using 25 [bright red LEDs](https://www.adafruit.com/products/297) which are rated for 20mA of current draw - 500mA for the LEDs alone. The output of the 7805 regulator is exposed on the DC Boarduino at Vin, providing 1-1.5A, which is sufficient. 

Inspired by [this thread](https://www.reddit.com/r/arduino/comments/3znyer/bathroom_laser_light_when_turning_the_light_on_is/), the next version of MotionNightlight may/will include:

* Ambient light sensor. Why switch on the LEDs if the room is already lit?
* Red laser illuminating the toilet bowl. Target acquired!

======

