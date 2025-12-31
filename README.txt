Some notes/scratchpad-ish writeups on stuff that puzzled me a bit...

=========================================================================================
EXAMPLE HEX TO BINARY
=========================================================================================

0x7FFF
------
0111 7 
1111 F (digit F is 16)
1111 F
1111 F

-> 0111 1111 1111 1111

=========================================================================================
HOW 32-BIT FLOATS WORK
=========================================================================================

HIGH _ ________ _______________________ LOW
     S EXP      SIGNIFICAND

1 bit to store S (sign); 0 for positive, 1 negative

8 bits to store EXP (exponent)
  Stored exponent is biased by 127
    Effective exponent E = exponent bits - 127

23 bits to store significand
  These are sig digits of number
  Is always led by a 1
  Then we compute as follows:

  If the significand's first 4 digits are 1011, and the remaining bits are 0,
  we compute the value as follows:

  1 * 2^0    = 1.0
  0 * 2^(-1) = 0.0
  1 * 2^(-2) = 0.25
  1 * 2^(-3) = 0.125
  ...(followed by all 0's)

  Add up to get 1.375

  Significand will always be 1.xxx

To compute the final value:

V = (-1)^sign * significand * 2^effective exp.

=========================================================================================
REPRESENTING FLOAT VALUE WITH INTEGERS
=========================================================================================

To get whole part, cast to int
To get fractional part, subtract whole part from float number

e.g.

n = 10.75
whole = int(n)
fractional = n - whole

Multiplying by 65536 scales the fractional portion up to represent it with an integer
  The fractional part will always be 0-1
  If we * by 65536:
    0 maps to 0
    1 maps to 65536

    Therefore, 0.5 would map to 65536 * 0.5 = 32768

Don't understand why 65536 very well but it's got to do with it being 2^16

THE WHOLE POINT IS TO REPRESENT THE FRACTIONAL PART AS AN INTEGER

=========================================================================================
UNDERSTANDING HTONF CODE
=========================================================================================

It basically encodes the whole part, fractional part and sign into a 32-bit integer
It uses the above techniques/concepts to do so
