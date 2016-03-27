#!/usr/bin/python

import eegl

eegl.eeglinit(eegl.states)    # default states = 1000

bit = eegl.eegl()             # generate 0 or 1

num = eegl.eeglunif()         # generate uniform number 0-1

pwr = eegl.eeglint(16) + 1    # generate number of bits in lmt

lmt = eegl.eeglpwr(pwr)       # lmt = 0 to 2**pwr

intgr = eegl.eeglint(lmt)     # intgr = 0 up to lmt

pwroftwo = 2 ** pwr           # upper limit for lmt

print 'random bit', bit
print 'random uniform number', num
print 'random', pwr, 'bit integer', lmt, 'out of', pwroftwo
print 'random integer', intgr, 'out of', lmt
