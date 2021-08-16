minipov3
==

This is everything i found around minipov. It seems
[ladyada](http://ladyada.net/make/minipov3/index.html) created this wonderful
peace of hardware.

Fine instructions can be found at [instructables](https://www.instructables.com/MiniPOV3-Kit/).

Base
--

Base information can be found on the original wiki at [adafruit](https://learn.adafruit.com/minipov3).

All code using the original function of the minipov are named `pov_*.c`.

You can use the device for just linear LED animations as well. This is not only nice for testing.

All code providing such animations of the minipov are named `ani_*.c`.

Mods
--

The nice thing about the device is the fact that you can program the CPU with
just a RS232 provided by older PCs out of the box or with an USB converter. You
just need 3 diods and 3 resitors to make the work.

![Diagram](adafruit_products_minipov3schem.png)

Mitch Altman from
[cornfieldelectronics](http://cornfieldelectronics.com/cfe/projects.php)
developed alot of mods on minipov3.

### LEDcube

I bought the minipov3 with a kit for the
[LEDcube](http://cornfieldelectronics.com/cfe/projects/ledcube/LEDcube_instructions.php)
which i wasn able to finish yet.

All code using the LEDCube function of the minipov are named `cube_*.c`.

### RGBLight

