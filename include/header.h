#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// define type to store each byte
typedef uint8_t BYTE;

////////////////////////////
// Bit Masks
/////////////////////////////

// Macros for machine code fields
#define OPCODE    0b11111100
#define D_BIT     0b00000010
#define W_BIT     0b00000001
#define MOD_FIELD 0b11000000
#define REG_FIELD 0b00111000
#define RM_FIELD  0b00000111

// Macros for OPCODE field
#define REGMEM_TF_REG 0b10001000
// TODO: add more as needed

// Macros for MOD field
#define MEM_MOD    0b00000000
#define MEM_MOD_8  0b01000000
#define MEM_MOD_16 0b10000000
#define REG_MOD    0b11000000

////////////////////////
// Macros for Registers
////////////////////////
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

/////////////////////////////////
// Structs
/////////////////////////////////

// struct for asm instructions
struct asm_inst
{
  char instruct[4];
  char operand_1[17]; // 16 bytes plus NUL terminator
  char operand_2[17];
};


#endif