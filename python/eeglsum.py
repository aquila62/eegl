#!/usr/bin/python

import sys

lst = sys.stdin.readlines()   # read output of eeglgen.py
totones  = 0
totzeros = 0
for ln in lst:
	ln = ln[0:-1]    # drop end of line character
	if ln == '1':
		totones = totones + 1
	elif ln == '0':
		totzeros = totzeros + 1
print 'total ones', totones, 'total zeros', totzeros
