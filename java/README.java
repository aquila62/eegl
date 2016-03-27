The java version of eegl is 1000 times slower than the C version.

I had to change the eegl generator somewhat in java because of java's
architecture.  The java version of eegl uses 2000 24-bit LFSR registers.
This change does not affect the performance, because the performance
isn't related to the number of registers.

The period length of the java version of eegl with 2000 registers
is 2^48000, or 2^(2000 * 24).

See TESTING for a description of the tests.

To read more about the eegl random number generator, read
README.eegl in the C repository of eegl.

The website for eegl is at https://aquila62.github.io.
