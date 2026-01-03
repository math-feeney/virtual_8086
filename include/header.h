#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <endian.h> // TODO: is this standard or only glibc?

// define type to store each byte
typedef uint8_t BYTE;

// define a struct that can hold up to the maximum number of needed bytes
struct inst_full
{
  uint8_t byte_1;
  uint8_t byte_2;
  uint8_t byte_3;
  uint8_t byte_4;
  uint8_t byte_5;
  uint8_t byte_6;
};

// NOTE EVERYTHING BELOW NEEDS TO BE REDONE FOR MY ONE-BIT at a time strat
/*
// Includes key for 8086 instruction set

    
      enum {
          MOV = 0b0000000010001000,
          OTH = 0b0000000000000000

      };

      // ENUM for the REG field encoding key
      // NOTE: This includes the W-bit (bit-8)
      enum {
        AL = 0b0000000000000000,
        CL = 0b0000100000000000,
        DL = 0b0001000000000000,
        BL = 0b0001100000000000,
        AH = 0b0010000000000000,
        CH = 0b0010100000000000,
        DH = 0b0011000000000000,
        BH = 0b0011100000000000,
        AX = 0b0000000000000001,
        CX = 0b0000100000000001,
        DX = 0b0001000000000001,
        BX = 0b0001100000000001,
        SP = 0b0010000000000001,
        BP = 0b0010100000000001,
        SI = 0b0011000000000001,
        DI = 0b0011100000000001,
      };
*/
  #endif