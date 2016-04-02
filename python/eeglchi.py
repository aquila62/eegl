#!/usr/bin/python

import eegl

eegl.eeglinit(1000)
tally    = []
chisq    = 0.0
diff     = 0.0
diffsq   = 0.0
expected = 1024.0
for i in range(16):
	tally.append(0.0)
# 16384 4-bit samples
for i in range(16384):
	indx = eegl.eeglpwr(4)
	tally[indx] = tally[indx] + 1.0
# calculate chi square
for i in range(16):
	diff = expected - tally[i]
	diffsq = diff * diff
	chisq = chisq + (diffsq / expected)
print 'Total samples 16384'
print 'Chi square', chisq
print '15 degrees of freedom'
print '95% of the time, the chi square is between 6.262 and 27.488'
