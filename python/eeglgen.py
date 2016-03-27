#!/usr/bin/python

import eegl

eegl.eeglinit(eegl.states)
i = 1000000          # print 1 million zeros or ones                  
while i > 0:
	i = i - 1
	bit = eegl.eegl() + 48;    # ASCII 0 or 1
	print chr(bit)
