# POV

## POV with dump pattern loop

The original kit came with a sensor connection bu no sensor. The pattern was
just fired in a loop and with some luck you can see the whole word or sentence.

All code using this original functionality of the minipov are named `pov_*.c`.

To generate an textline for `pov__.c` the programm `../gen_pov.c` is provided.

- `*.h` contains the text as pattern like "digg", "eyebeam", "i love make",
  "sxsw", "make" or "minipov"
- `text.c` prints text from the header, use `../gen_pov.c` to generate new texts

## POV with sensor

To know when to start the writing the minipov utilizes a sensor port. We
experimented alot with different switches and weights to trigger the switch
with no success.

Finally we used a reed contact and a small magnet in a tube.
This works incredible fine.

- `sensor.c` prints text from `../text.h` on sensor open, i use a reed contact
  and a magnet as a sensor
- `various.c` prints directly from a char[] utilizing a font in rom, it puts
  the texts into eeprom and has different lines to output

![IMG](../media/2021-09-05-22-16-34-0007.sized.jpg)

## Remarks

The orignal code snippets had various methods implementing the animation.

- It utilized a macro `B8` because older compilers did not support the
  `0b`-prefix.
- It either used `_delay_ms(1);` in a loop to output the pattern or used a
  timer interrupt to do so

