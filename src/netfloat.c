#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t htonf(float f) {
  // WARNING: f should be in range [0, 32767]

  uint32_t p;
  uint32_t sign;

  if (f < 0) {
    sign = 1;
    f = -f; // We already know the sign and wish to deal with the float as a
            // positive

  } else {
    sign = 0;
  }

  p = (uint32_t)f;   // Get whole part
  p &= 0x7FFF;       // Clear all bits except lower 15
  p <<= 16;          // Move lower 15 bits to upper half
  p |= (sign << 31); // Write the sign bit at the highest bit

  // p = ((((uint32_t)f) & 0x7FFF) << 16) | (sign << 31);

  uint32_t frac =
      (uint32_t)((f - (int)f) *
                 65536.0F); // Get fractional part as int mapped to 65536

  frac &= 0xFFFF; // Retain only lower 16 bits

  p |= frac; // Write fractional part to encoded value

  // p |= (uint32_t)(((f - (int)f) * 65536.0F)) & 0xFFFF;

  return p;
}

float ntohf(uint32_t p) {
  // Get whole part
  float f = ((p >> 16) & 0x7FFF);

  // Get fractional part
  f += (p & 0xFFFF) / 65536.0F;

  // Check if sign bit is set
  if (((p >> 31) & 0x1) == 0x1) {
    f = -f;
  }

  return f;
}

int main(void) {
  float x = -3.1415926F;
  uint32_t nx = htonf(x);
  float hx = ntohf(nx);

  printf("Original:\t %f\n", x);
  printf("Encoded:\t 0x%08x\n", nx);
  printf("Decoded:\t %f\n", hx);

  exit(EXIT_SUCCESS);
}
