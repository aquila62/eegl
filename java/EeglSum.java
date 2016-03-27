// EeglSum.java - Eegl Sum Test  Version 1.0.0
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

public class EeglSum { 
   public static void main(String[] args) { 
      Eegl ee = new Eegl(2000);
      int totzeros = 0;
      int totones  = 0;
      int bit = 0;
      int i;
      for (i=0; i<1000000; i++)
         {
         bit = ee.getBit();
         if (bit == 1) totones++;
	 else totzeros++;
         } // for each random bit
      System.out.println("Total ones  " + totones);
      System.out.println("Total zeros " + totzeros);
   } // main
} // public class EeglSum
