/* eeglchi.cpp - eegl chi square test Version 1.0.0                  */
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

// number of LFSR states
#define STATES 1000

int main()
   {
   int i;                         // loop counter
   double *p,*q;                  // pointers to tally array
   double tally[32];              // chi square counts
   double expected = 1024.0;      // expected chi square count
   double diff;                   // expected - actual count
   double diffsq;                 // difference squared
   double chisq = 0.0;            // chi square total
   Eegl ee(STATES);               // Eegl class instance
   //
   // initialize tally array to zero
   //
   p = (double *) tally;
   q = (double *) tally + 32;
   while (p < q) *p++ = 0.0;
   //
   // tally 16384 4-bit samples in 16 counters
   //
   i = 16384;
   while (i--)
      {
      int indx;
      indx = ee.eeglpwr(4);      // 4 bit sample 0-15
      tally[indx] += 1.0;        // tally the sample
      } /* for each sample */
   //
   // add up the chi square from 16 counters
   //
   p = (double *) tally;
   q = (double *) tally + 16;
   i = 16;
   while (i--)
      {
      diff = expected - *p++;           // expected - actual
      diffsq = diff * diff;             // square the difference
      chisq += (diffsq / expected);     // add to chi square total
      } /* for each tally */
   //
   // print report
   //
   cout << "Total samples 16384" << endl; 
   cout << "Chi square " << chisq << endl; 
   cout << "15 degrees of freedom" << endl; 
   cout << "Chi square at  5% is  7.261" << endl; 
   cout << "Chi square at 95% is 24.996" << endl; 
   return(0);            // normal eoj
   } /* main */
