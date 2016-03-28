#!/usr/bin/python

#  eegl.py - python eegl methods Version 1.0.0
#  Copyright (C) 2016 aquila62 at github.com

#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.

#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.

#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to:

   #  Free Software Foundation, Inc.
   #  59 Temple Place - Suite 330
   #  Boston, MA 02111-1307, USA.

#--------------------------------------------------------
#  The LFSR in this generator comes from the following
#  website http://www.xilinx.com/support/documentation/
#  application_notes/xapp052.pdf
#--------------------------------------------------------

import random

states = 1000
state  = []
maxint = (2**32) - 1

def eeglinit(states):
	i = states
	while i > 0:
		i = i - 1
		num = random.randrange(0,maxint)
		state.append(num)

def eegl():
	i = random.randrange(0,states)
	reg = state[i]
	b1 = reg >> 31 & 1
	b2 = reg >> 30 & 1
	b3 = reg >> 10 & 1
	b4 = reg & 1
	out = b1 ^ b2 ^ b3 ^ b4
	reg = (reg >> 1) | (out << 31)
	state[i] = reg
	return(out)

def eeglunif():
	num = 0.0
	i = 53
	while (i > 0):
		i = i - 1
		bit = eegl()
		if bit == 1:
			num = (num * 0.5) + 0.5
		else:
			num = num * 0.5
	return(num)

def eeglint(limit):
	num = eeglunif()
	intgr = int(num * limit)
	return(intgr)

def eeglpwr(bits):
	intgr = 0
	i = bits
	while (i > 0):
		i = i - 1
		intgr = (intgr << 1) + eegl()
	return(intgr)
