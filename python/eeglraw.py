#!/usr/bin/python

# this program generates raw random output
# and may serve as input to dieharder and TestU01

import sys
import eegl

eegl.eeglinit(eegl.states)    # default is 1000 states
while (1):
	num = eegl.eeglpwr(8)
	sys.stdout.write(chr(num))
