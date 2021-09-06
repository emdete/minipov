#!/usr/bin/env python3

# WGM12 3 /* Waveform Generation Mode */

# TIMER1_PRESCALE_1 1
# TIMER1_PRESCALE_8 2
# TIMER1_PRESCALE_64 3
# TIMER1_PRESCALE_256 4
# TIMER1_PRESCALE_1024 5

# the frequency of the interrupt overflow is determined by the
# prescaler and overflow value.
# freq = clock_frequency / ( 2 * prescaler * overflow_val)
# where prescaler can be 1, 8, 64, 256, or 1024
# clock_freq is 8MHz
# and overflow_val is 16bit

# the overflow value is placed in OCR1A, the prescale is set in TCCR1B
# so for example:
# A good POV frequency is around 400Hz
# desired freq = 400Hz
# clock freq = 8MHz
# 8MHz / (400Hz * 2) = 10000
# since 10000 is less than 655536 (largest 16 bit number)
# OCR1A = 10000 and the prescale is 1

# TCCR1B = (1 << WGM12) | TIMER1_PRESCALE_1;
# OCR1A = (uint16_t)10000;

prescaler = 1
overflow_val = 10000
clock_frequency = 8 * 10**6
print('freq', clock_frequency / ( 2 * prescaler * overflow_val))
