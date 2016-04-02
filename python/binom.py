#!/usr/bin/python

import eegl

eegl.eeglinit(1000)
tally    = []
expected = []
chisq    = 0.0
diff     = 0.0
diffsq   = 0.0
# expected array is based on Pascal's triangle for 2^16
expected.append(1.0)
expected.append(16.0)
expected.append(120.0)
expected.append(560.0)
expected.append(1820.0)
expected.append(4368.0)
expected.append(8008.0)
expected.append(11440.0)
expected.append(12870.0)
expected.append(11440.0)
expected.append(8008.0)
expected.append(4368.0)
expected.append(1820.0)
expected.append(560.0)
expected.append(120.0)
expected.append(16.0)
expected.append(1.0)
for i in range(17):
	tally.append(0.0)
# 65536 samples
for i in range(65536):
	tothd = 0
	# number of heads in 16 flips
	# heads = 1 and tails = 0
	for j in range(16):
		tothd = tothd + eegl.eegl()
	# keep a count by number of heads in 16 flips
	tally[tothd] = tally[tothd] + 1.0
# calculate chi square
for i in range(17):
	diff = expected[i] - tally[i]
	diffsq = diff * diff
	chisq = chisq + (diffsq / expected[i])
print 'Total samples 65536'
print 'Chi square', chisq
print '16 degrees of freedom'
print '95% of the time, the chi square is between 6.908 and 28.845'
