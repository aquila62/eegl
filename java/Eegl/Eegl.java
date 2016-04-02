// The Eegl random number generator in java is based on a linear
// feedback shift register of 24 bits
// The reference for this LFSR is at:
// http://www.xilinx.com/support/documentation/
// application_notes/xapp052.pdf
// The 24 bit LFSR is defined as 24,23,22,17
// reading from left to right going from 24 to 1.
// Going from right to left, 0 to 23,
// the LFSR is 0,1,2,7

package Eegl;

import java.util.Random;

public class Eegl {
   private int states;
   private int ofst;
   private int out;
   private int maxint = 0xffffff;
   private int state[] = new int [2048];
   private Random rand = new Random();

   public Eegl(int startState)
      {
      int i;
      states = startState;
      if (states < 1 || states > 2000)
         {
	 System.out.println("Eegl constructor: "
	    + "invalid number of states " + states);
	 System.exit(1);
	 } // invalid # states
      for (i = 0; i < states; i++)
         {
	 state[i] = (int) rand.nextInt() & maxint;
	 } // for each state
      } // constructor

   public int getBit()
      {
      int tmp;
      ofst = (int) rand.nextInt(states);
      tmp = state[ofst];
      out = ((tmp >> 7) ^ (tmp >> 2)
         ^ (tmp >> 1) ^ (tmp >> 0)) & 1;
      tmp = ((tmp >> 1) | (out << 23));
      state[ofst] = tmp;
      return((int) out);
      } // getBit

   public double getUnif()
      {
      int i;
      double num;
      num = 0.0;
      i = 53;
      while (i-- > 0)
         {
	 if (getBit() == 1)
	    {
	    num = (num * 0.5) + 0.5;
	    } // if one bit
	 else
	    {
	    num = num * 0.5;
	    } // else zero bit
	 } /* for each bit in mantissa */
      return(num);
      } // getUnif

   public int getInt(int limit)
      {
      int intgr;
      double num;
      num = getUnif();
      intgr = (int) Math.floor(num * (double) limit);
      return(intgr);
      } // getInt

   public long getPwr(int bits)
      {
      int i;
      long intgr;
      intgr = 0;
      i = bits;
      while (i-- > 0)
         {
	 intgr = (intgr << 1) + getBit();
	 } // for each bit
      return(intgr);
      } // getPwr
   } // public class Eegl
