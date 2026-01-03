#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// Macros for machine code fields
#define OPCODE    0b11111100
#define D_BIT     0b00000010
#define W_BIT     0b00000001
#define MOD_FIELD 0b11000000
#define REG_FIELD 0b00111000
#define RM_FIELD  0b00000111

// Macros for OPCODE field
////////////////////////////
#define REGMEM_TF_REG 0b10001000
// TODO: add more as needed

// Macros for MOD field
#define MEM_MOD    0b00000000
#define MEM_MOD_8  0b01000000
#define MEM_MOD_16 0b10000000
#define REG_MOD    0b11000000

// Macros for Registers
#define AL 0b000
#define AX 0b000
#define CL 0b001
#define CX 0b001
#define DL 0b010
#define DX 0b010
#define BL 0b011
#define BX 0b011
#define AH 0b100
#define SP 0b100
#define CH 0b101
#define BP 0b101
#define DH 0b110
#define SI 0b110
#define BH 0b111
#define DI 0b111


// define type to store each byte
typedef uint8_t BYTE;

// struct for asm instructions
struct asm_inst
{
  char instruct[4];
  char operand_1[17]; // 16 bytes plus NUL terminator
  char operand_2[17];
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