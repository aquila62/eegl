/* Eegl.cpp - C++ random number generator Version 1.0.0              */
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

#include <time.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "Eegl.hpp"

Eegl::Eegl(int initStates)
   {
   SetEegl(initStates);
   } /* constructor */

void Eegl::SetEegl(int initStates)
   {
   int i;
   states = initStates;
   if (states < 1 || states > 1000)
      {
      fprintf(stderr,"Eegl::SetEegl - Invalid "
         "number of states %d\n", states);
      exit(1);
      } /* invalid states */
   /* declare the GSL random number generator as taus  */
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   /* allocate the GSL taus random number generator    */
   r = (gsl_rng *) gsl_rng_alloc(gsl_rng_taus);
   /* initialize the GSL taus random number generator  */
   srand(time(0));
   gsl_rng_set(r, rand());
   for (i=0;i<states;i++)
      {
      state[i] = gsl_rng_get(r);    /* set to random UINT */
      } /* for each state */
   } /* SetEegl */

int Eegl::eegl(void)
   {
   int i;
   unsigned int tmpState;
   /* select one out of 1000 states                        */
   ofst = i = gsl_rng_uniform_int(r, states);
   tmpState = state[i];
   /* calculate LFSR step                                  */
   out = ((tmpState >> 31) ^ (tmpState >> 30)
      ^ (tmpState >> 10) ^ (tmpState >> 0)) & 1;
   /* roll the LFSR right                                  */
   state[i] = ((tmpState >> 1) | (out << 31));
   /* return the output of the LFSR step                   */
   return((int) out);
   } /* Eegl::eegl */

double Eegl::eeglunif(void)
   {
   int i;
   double num;
   num = 0.0;
   i = 53;
   while (i--)
      {
      if (Eegl::eegl())
         {
	 num = (num * 0.5) + 0.5;
	 } /* if one bit */
      else
         {
	 num = num * 0.5;
	 } /* else zero bit */
      } /* for each bit in the mantissa */
   return(num);
   } /* Eegl::eeglunif */

unsigned int Eegl::eeglpwr(int bits)
   {
   int i;
   unsigned int num;
   num = 0;
   i = bits;
   while (i--)
      {
      num = (num << 1) + Eegl::eegl();
      } /* for each bit in the unsigned integer */
   return(num);
   } /* Eegl::eeglpwr */

int Eegl::eeglint(int limit)
   {
   double unif;
   double dblLimit;
   double rslt;
   unif = Eegl::eeglunif();
   dblLimit = (double) limit;
   rslt = unif * dblLimit;
   return((int) rslt);
   } /* Eegl::eeglint */
