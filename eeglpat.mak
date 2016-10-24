#!/usr/bin/make

# eeglpat.mak - Compile Program eeglpat.c  Version 1.0.0
# Copyright (C) 2016   aquila62 at github.com

# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to:

# 	Free Software Foundation, Inc.
# 	59 Temple Place - Suite 330
# 	Boston, MA  02111-1307, USA.

# Usage: eeglpat
# Example: eeglpat

# Commands when running eeglpat:
# r = reset
# q = quit

OBJ=eeglpat.o \
	eeglinit.o \
	eegl.o \
	eeglunif.o \
	eeglint.o

CC=gcc

CFLAGS=-c -Wall -O2

LDFLAGS=-lncurses

eeglpat:			$(OBJ)
		$(CC) -Wall -O2 $(OBJ) -o eeglpat $(LDFLAGS)

eeglpat.o:			eeglpat.c
		$(CC) $(CFLAGS) eeglpat.c

eeglinit.o:			eeglinit.c
		$(CC) $(CFLAGS) eeglinit.c

eegl.o:				eegl.c
		$(CC) $(CFLAGS) eegl.c

eeglunif.o:			eeglunif.c
		$(CC) $(CFLAGS) eeglunif.c

eeglint.o:			eeglint.c
		$(CC) $(CFLAGS) eeglint.c

clean:
	rm -f $(OBJ) eeglpat
