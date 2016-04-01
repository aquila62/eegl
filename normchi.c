/* normchi.c - Normal distribution chi square test Version 1.0.0     */
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

#include <stdio.h>
#include <math.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include "eegl.h"

/* number of states in the generator */
#define STATES 1000

/* actual normal distribution sample structure */
typedef struct actstr {
   double n1;
   double n2;
   } actfmt;

/* print syntax */
void putstx(char *pgm)
   {
   fprintf(stderr,"Usage: %s mean stdev size\n", pgm);
   fprintf(stderr,"Where: mean is the expected "
      "mean of the random variable\n");
   fprintf(stderr,"Where: stdev is the expected "
      "standard deviation of the random variable\n");
   fprintf(stderr,"Where: size is the number "
      "of normal numbers generated\n");
   fprintf(stderr,"Example: %s 15.0 2.0 10000\n", pgm);
   exit(1);
   } /* putstx */

/* Box-Muller Transform in Wikipedia */
void boxmul(eefmt *ee, double mean,
   double stdev, actfmt *aa)
   {
   double u1;
   double u2;
   double x1;
   double x2;
   double twopi;
   double rootu1;
   u1 = eeglunif(ee);
   u2 = eeglunif(ee);
   twopi = 2.0 * M_PI;
   rootu1 = sqrt(-2.0 * log(u1));
   x1 = rootu1 * cos(twopi * u2);
   x2 = rootu1 * sin(twopi * u2);
   aa->n1 = mean + (stdev * x1);
   aa->n2 = mean + (stdev * x2);
   } /* boxmul */

int main(int argc, char **argv)
   {
   int i;                /* loop counter */
   int sz;               /* population size */
   double size;          /* double version of sz */
   double mean;          /* sample mean */ 
   double stdev;         /* sample standard deviation */
   double exx;           /* parameter in the pdf */
   double chisq;         /* chi square result */
   double minchi;        /* 95% lower limit */
   double maxchi;        /* 95% upper limit */
   double *p,*q,*r;      /* pointers to the table */
   double tbl[64];       /* table of actual tallies */
   double expected[64];  /* table of expected tallies */
   actfmt *aa;           /* actual sample structure */
   eefmt *ee;            /* eegl structure */
   if (argc != 4) putstx(*argv);       /* must have 3 arguments */
   mean = atof(*(argv+1));             /* sample mean */
   if (mean < -1000.0)
      {
      fprintf(stderr,"Mean parameter %s "
         "is too small\n", *(argv+1));
      putstx(*argv);
      exit(1);
      } /* mean too small */
   if (mean > 1000.0)
      {
      fprintf(stderr,"Mean parameter %s "
         "is too large\n", *(argv+1));
      putstx(*argv);
      exit(1);
      } /* mean too large */
   stdev = atof(*(argv+2));            /* standard deviation */
   if (stdev < 0)
      {
      fprintf(stderr,"Stdev parameter %s "
         "is too small\n", *(argv+2));
      putstx(*argv);
      exit(1);
      } /* stdev too small */
   if (stdev > 1000)
      {
      fprintf(stderr,"Stdev parameter %s "
         "is too large\n", *(argv+2));
      putstx(*argv);
      exit(1);
      } /* stdev too large */
   sz = atoi(*(argv+3));                 /* population size */
   if (sz < 36)
      {
      fprintf(stderr,"Size parameter %s "
         "is too small\n", *(argv+3));
      putstx(*argv);
      exit(1);
      } /* sz too small */
   if (sz > 100000000)
      {
      fprintf(stderr,"Size parameter %s "
         "is too large\n", *(argv+3));
      putstx(*argv);
      exit(1);
      } /* sz too large */
   ee =(eefmt *) eeglinit(STATES);         /* initialize eegl */
   /* allocate memory for the actual sample structure */
   aa = (actfmt *) malloc(sizeof(actfmt));
   if (aa == NULL)
      {
      fprintf(stderr,"main: out of memory "
         "allocating the aa structure\n");
      exit(1);
      } /* out of memory */
   size = (double) sz;                    /* convert sz to double */
   /**********************************/
   /* intitialize tables             */
   /**********************************/
   p = (double *) tbl;
   q = (double *) tbl + 64;
   while (p < q) *p++ = 0.0;
   p = (double *) expected;
   q = (double *) expected + 64;
   while (p < q) *p++ = 0.0;
   /***********************************/
   /* create table of expected counts */
   /***********************************/
   p = (double *) expected;
   for (exx=-15.0; exx <= 15.0001; exx += 1.0)
      {
      double pdf;
      /* gaussian probability density function */
      /* gaussian is another way of saying normal */
      pdf = gsl_ran_gaussian_pdf(exx, stdev);
      *p++ = pdf * size;            /* expected counts */
      } /* for exx = -15 to +15 */
   /**********************************/
   /* create n samples               */
   /**********************************/
   i = sz >> 1;
   while (i--)
      {
      boxmul(ee,mean,stdev,aa);        /* Box-Muller Transform */
      /* the Box-Muller Transform gives two numbers n1 and n2 */
      /* tally by number to create histogram */
      p = (double *) tbl + (int) (aa->n1 + 0.5);
      *p += 1.0;
      p = (double *) tbl + (int) (aa->n2 + 0.5);
      *p += 1.0;
      } /* for each sample */
   /**********************************/
   /* Chi square calculation         */
   /**********************************/
   chisq = 0.0;
   p = (double *) tbl;
   q = (double *) tbl + 31;       /* -15 to +15 including zero */
   r = (double *) expected;
   while (p < q)
      {
      double diff;                /* expected - actual */
      double diffsq;              /* difference squared */
      diff = *p - *r;
      diffsq = diff * diff;
      chisq += (diffsq / *r);     /* add to chi square total */
      p++;
      r++;
      } /* for each entry in the table */
   printf("Normal distribution chi square test\n");
   printf("Total population %d\n", sz);
   printf("Chi square %f\n", chisq);
   /* calculate min and max chi square at 95% */
   minchi = gsl_cdf_chisq_Pinv(0.025,30);
   maxchi = gsl_cdf_chisq_Pinv(0.975,30);
   printf("95%c of the time, the chi square is "
      "between %f and %f\n", '%', minchi, maxchi);
   return(0);
   } /* main */
