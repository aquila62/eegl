/* eegl.c - random number generator Version 1.0.0 */
/* Copyright (C) 2016 aquila at github.com */

/* This program is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU General Public License as */
/* published by the Free Software Foundation; either version 2 of */
/* the License, or (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program; if not, write to: */

   /* Free Software Foundation, Inc. */
   /* 59 Temple Place - Suite 330 */
   /* Boston, MA 02111-1307, USA. */

/********************************************************/
/* The LFSR in this generator comes from the following  */
/* website http://www.xilinx.com/support/documentation/ */
/* application_notes/xapp052.pdf                        */
/********************************************************/

#include <gsl/gsl_rng.h>
#include "eegl.h"
int eegl(eefmt *ee)
   {
   unsigned int *stp; /* state pointer */
   /********************************************************/
   /* this LFSR is 32 bits                                 */
   /* this is 32 22 2 1 counting from the left at one      */
   /* or 31 21 1 0 counting from the left at zero          */
   /* in the reverse direction,                            */
   /* the bits are counted from the right at zero          */
   /* 31 30 10 0                                           */
   /* the period length is 4 billion, or 2^32-1, cycles    */
   /* for this 32-bit single LFSR register                 */
   /* It uses a random 32 bit number (non-zero) for a seed */
   /* When combined with 1000 states, the period length    */
   /* is 2^32000                                           */
   /********************************************************/
   /* select one out of 1000 states                        */
   ee->ofst = gsl_rng_uniform_int(ee->r, ee->states);
   /* point to the state selected                          */
   stp = (unsigned int *) ee->state + ee->ofst;
   /* calculate LFSR step                                  */
   ee->out = ((*stp >> 31) ^ (*stp >> 30)
      ^ (*stp >> 10) ^ (*stp >> 0)) & 1;
   /* roll the LFSR right                                  */
   *stp = ((*stp >> 1) | (ee->out << 31));
   /* return the output of the LFSR step                   */
   return((int) ee->out);
   } /* eegl subroutine */
