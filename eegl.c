/* eegl.c - random number generator Version 1.0.0                    */
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

/********************************************************/
/* The result of the Bays-Durham shuffle is that the    */
/* period length of eegl is somewhat less than          */
/* 2639 digits, or the factorial of 1024.               */
/* This is a theoretical period length that is too      */
/* long to be tested in practice.                       */
/********************************************************/

#include <math.h>
#include "eegl.h"

#define MAXINT 4294967296.0

int eegl(eefmt *ee)
   {
   int tmp;                /* used by Bays-Durham shuffle  */
   double num;             /* uniform number 0-1           */
   unsigned int *stp;      /* state array pointer          */
   unsigned char *p;       /* bit array pointer            */
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
   /* back up the previous two results                     */
   /********************************************************/
   ee->pprev = ee->prev;   /* prev prev <== prev           */
   ee->prev  = ee->out;    /* prev <== out                 */
   /********************************************************/
   /* select one out of 1000 states                        */
   /* calculate offset using the taus algorithm            */
   /********************************************************/
   ee->s1 = (((ee->s1&0xfffffffe)<<12)
      ^(((ee->s1<<13)^ee->s1)>>19));
   ee->s2 = (((ee->s2&0xfffffff8)<< 4)
      ^(((ee->s2<< 2)^ee->s2)>>25));
   ee->s3 = (((ee->s3&0xfffffff0)<<17)
      ^(((ee->s3<< 3)^ee->s3)>>11));
   num = (double) (ee->s1 ^ ee->s2 ^ ee->s3) / MAXINT;
   ee->ofst = (int) floor(num * (double) ee->states);
   /* point to the state selected                          */
   stp = (unsigned int *) ee->state + ee->ofst;
   /* calculate a new LFSR by xor'ing the taps             */
   ee->out = ((*stp >> 31) ^ (*stp >> 30)
      ^ (*stp >> 10) ^ (*stp >> 0)) & 1;
   /* and rolling the LFSR right                           */
   *stp = ((*stp >> 1) | (ee->out << 31));
   /********************************************************/
   /* Bays-Durham shuffle                                  */
   /* calculate random offset into the bit array           */
   /********************************************************/
   ee->bitofst = (int) floor(num * 1024.0);
   /* point to random bit array element                    */
   p = (unsigned char *) ee->bit + ee->bitofst;
   /* swap current output with the random member of the    */
   /* bit array                                            */
   tmp = (int) *p;
   *p  = (unsigned char) ee->out;
   ee->out = tmp;
   /********************************************************/
   /* return the output of the Bays-Durham shuffle         */
   /********************************************************/
   return((int) ee->out);
   } /* eegl subroutine */
