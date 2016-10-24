/* eeglunif.c - uniform random number generator 0-1 Version 1.0.0    */
/* Copyright (C) 2016 aquila62 at github.com                         */

/* This program is free software; you can redistribute it and/or     */
/* modify it under the terms of the GNU General Public License as    */
/* published by the Free Software Foundation; either version 2 of    */
/* the License, or (at your option) any later version.               */

/* This program is distributed in the hope that it will be useful,   */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of    */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the      */
/* GNU General Public License for more details.                      */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to:                        */

   /* Free Software Foundation, Inc.                                 */
   /* 59 Temple Place - Suite 330                                    */
   /* Boston, MA 02111-1307, USA.                                    */

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* website http://www.xilinx.com/support/documentation/ */
/* application_notes/xapp052.pdf                        */
/********************************************************/

/* this subroutine produces a uniform random number     */
/* from zero to one                                     */

#define MAXINT (4294967296.0)

#include "eegl.h"

double eeglunif(eefmt *ee)
   {
   double num;             /* random number from 0 up to 2^32 */
   double frac;            /* random number from 0-1     */
   num  = (double) eegl(ee);
   frac = num / MAXINT;
   return(frac);           /* return uniform random number */
   } /* eeglunif */
