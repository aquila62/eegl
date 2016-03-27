/*******************************************************************/
/* bit2txt.c  Version 1.0.0                                             */
/* Convert ASCII binary input to text output                            */
/* Copyright (C) 2016  Russell Stevens                                  */

/* This program is free software; you can redistribute it and/or        */
/* modify it under the terms of the GNU General Public License as       */
/* published by the Free Software Foundation; either version 2 of       */
/* the License, or (at your option) any later version.                  */

/* This program is distributed in the hope that it will be useful,      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        */
/* GNU General Public License for more details.                         */

/* You should have received a copy of the GNU General Public License    */
/* along with this program; if not, write to:                           */

	/* Free Software Foundation, Inc.         */
	/* 59 Temple Place - Suite 330            */
	/* Boston, MA  02111-1307, USA.           */
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/************************* #define MEG 1048576 ************************/
#define MEG 1024

int getbyte(void)
   {
   int len;
   unsigned char buf[8];
   len = read(0,buf,1);
   if (!len) return(EOF);
   if (len != 1)
      {
      fprintf(stderr,"getbyte: read error\n");
      exit(1);
      } /* read error */
   return(buf[0]);
   } /* getbyte */

int getbit(void)
   {
   int ch;
   while (1)
      {
      ch = getbyte();
      if (ch == EOF) return(EOF);
      if (ch == '0' || ch == '1') break;
      } /* bypass white space */
   return(ch);
   } /* getbit */

void putblk(unsigned char *blk, int blklen)
   {
   int len;
   len = write(1,blk,blklen);
   if (len != blklen)
      {
      fprintf(stderr,"putblk: write error\n");
      exit(1);
      } /* read error */
   } /* putblk */

int main()
   {
   int i;
   unsigned char *p;
   unsigned char *buf;
   buf = (unsigned char *) malloc(1048700);    /* > 1 megabyte */
   if (buf == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating buf\n");
      exit(1);
      } /* out of mem */
   i = 0;
   p = (unsigned char *) buf;
   while (1)
      {
      int j;
      int k;
      int ch;
      k = 0;
      j = 8;
      while (j--)
         {
         ch = getbit();
         if (ch == EOF) break;
	 k <<= 1;
	 k |= (ch - 0x30);
	 } /* for each bit in a byte */
      if (ch == EOF) break;
      *p++ = (unsigned char) k;
      i++;
      if (i >= MEG)
         {
	 putblk(buf, i);
	 i = 0;
	 p = (unsigned char *) buf;
	 } /* every mega bit */
      } /* for each byte read */
   if (i < MEG)
      {
      putblk(buf, i);
      } /* if partial block at end */
   return(0);
   } /* main */
