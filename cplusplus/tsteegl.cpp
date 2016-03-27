/* tsteegl.cpp - test random number generator Version 1.0.0          */
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

#include <iostream>
#include "Eegl.hpp"

using namespace std;

#define STATES 1000

int main()
   {
   int i;
   int bits;
   unsigned int maxpwr;;
   unsigned int pwr;
   double num;
   Eegl ee(STATES);
   i = ee.eegl();
   cout << "eegl " << i << endl;
   num = ee.eeglunif();
   cout << "unif " << num << endl;
   bits = ee.eeglint(16) + 1;
   cout << "bits " << bits << endl;
   pwr = ee.eeglpwr(bits);
   maxpwr = 1 << bits;
   cout << "powerof2 " << pwr 
      << " out of " << maxpwr << endl;
   return(0);
   } /* main */
