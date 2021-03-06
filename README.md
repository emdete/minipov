# Persistence of Vision

This is everything i found around minipov3. It seems
[Lady Ada](http://ladyada.net/make/minipov3/index.html) created this wonderful
peace of hardware.

Fine instructions can be found at
[Instructables](https://www.instructables.com/MiniPOV3-Kit/).

[Adafruit minipov3 design](https://learn.adafruit.com/minipov3/design)

[Adafruit minipov3 software](https://learn.adafruit.com/minipov3/software)

## Base

Base information can be found on the original wiki at
[adafruit](https://learn.adafruit.com/minipov3).

![Diagram](documentation/adafruit_products_minipov3schem.png)

The nice thing about the device is the fact that you can program the CPU with
just a RS232 provided by older PCs out of the box or with an USB converter. It
utilises just 3 diods, 3 resitors and a DB9 plug to make that work (be aware
that this doesnt really use the serial capabilities of the RS232 but pulls the
information over the status lines of the interface, a method called
bitbanging).

### POV

[pov](pov/)

### Animation

[animation](animation/)

### Laser

[laser](laser/)

## Mods

Mitch Altman from
[cornfieldelectronics](http://cornfieldelectronics.com/cfe/projects.php)
developed alot of mods on minipov3.

### LEDcube

[cube](cube/)

### RGBLight

[Mitch](mitch@CornfieldElectronics.com) from
[Cornfield Electronics](http://cornfieldelectronics.com/cfe/projects.php)
(scroll down to **"Project: Make your own Trippy RGB Light"**) had another mod
called RGBLight.

## Troubleshooting

### Bitbanging

It seems the Bitbanging timing depends on the speed of the host computer. If
you encounter this message:

```
avrdude: AVR device not responding
avrdude: initialization failed, rc=-1
	Double check connections and try again, or use -F to override
	this check.
```

it may be that (if everything else is in place, the cpu powered and connected)
the timing must be changed. I put the macro `AVRDUDE_TIMING` into the makefile
for that. Raise the value and check again.

