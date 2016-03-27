// EeglChi.java - Eegl Chi Square Test  Version 1.0.0
// Copyright (C) 2016 aquila62 at github.com

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to:

   // Free Software Foundation, Inc.
   // 59 Temple Place - Suite 330
   // Boston, MA 02111-1307, USA.

//*******************************************************
// The LFSR in this generator comes from the following  *
// website http://www.xilinx.com/support/documentation/ *
// application_notes/xapp052.pdf                        *
//*******************************************************

import Eegl.Eegl;

public class EeglChi { 
   public static void main(String[] args) { 
      Eegl ee = new Eegl(2000);
      int i;
      double tally[] = new double [32];
      for (i=0; i<32; i++)
         {
	 tally[i] = 0.0;
	 } // initialize each tally
      for (i=0; i<16384; i++)
         {
	 int smpl;
	 smpl = (int) ee.getPwr(4);
	 tally[smpl] += 1.0;
	 } // for each sample
      double chisq    =    0.0;
      double expected = 1024.0;
      for (i=0; i<16; i++)
         {
	 double diff;
	 double diffsq;
	 diff = expected - tally[i];
	 diffsq = diff * diff;
	 chisq += (diffsq / expected);
	 } // for each of the tallies
      System.out.println("Total samples 16384");
      System.out.println("Chi square       " + chisq);
      System.out.println("15 degrees of freedom");
      System.out.println("Chi square at  5% is  7.261");
      System.out.println("Chi square at 95% is 24.996");
   } // main
} // public class EeglChi
