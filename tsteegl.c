/* tsteegl.c - Test eegl random number generator Version 1.0.0 */
/* Copyright (C) 2016 aquila62 at github.com */

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

#include <stdio.h>
#include "eegl.h"

/* number of LFSR registers */

/***************************************************/
/* test the eegl random number generator with 1024 */
/* LFSR registers                                  */
/* generate 1000 random bits 0 or 1                */
/***************************************************/

int main(void)
   {
   int i;             /* loop counter */
   eefmt *ee;         /* eegl structure */
   ee = (eefmt *) eeglinit();       /* initialize eegl */
   i = 1000;          /* set loop counter */
   while (i--)        /* for each iteration of loop */
      {
      int j;          /* declare random bit */
      j = eeglbit(ee);     /* generate random bit 0 or 1 */
      printf("%d", j);     /* print random bit */
      } /* for each bit generated */
   printf("\n");      /* end of line at end of loop */
   return(0);         /* normal eoj */
   } /* main */
