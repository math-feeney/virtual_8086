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

// Macros for getting opcode
// note: these are just for internal
// use and unrelated to the 8086 ISA 

// MOV instructions: X & 0b11110000 == 0b00010000
#define MOV 0x01

#define REGMEM_TF_REG 0x0101
#define IM_T_REGMEM   0x0102
#define IM_T_REG      0x0103
#define MEM_T_ACC     0x0104
#define ACC_T_MEM     0x0105
#define REGMEM_T_SEG  0x0106
#define SEG_T_REGMEM  0x0107

// PUSH instructions:
#define PUSH 0x02

#define P_REGMEM 0x0201
// ADD MORE HERE ///////////

// Macros for MOD field
// NOTE: assumes bit shifted to 
// lowest two bits
#define MEM_MOD    0x00
#define MEM_MOD_8  0x01
#define MEM_MOD_16 0x02
#define REG_MOD    0x03

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

////////////////////////////////
// Macros for output formatting
////////////////////////////////
#define STR_STR 0x01
#define STR_INT 0x02
#define INT_STR 0x03

/////////////////////////////////
// Structs
/////////////////////////////////

// Possible struct for binary code values eg mod/reg/rm
struct bin_codes_t
{
  uint8_t d_bit;
  uint8_t w_bit;
  uint8_t mod_bits;
  uint8_t reg_bits;
  uint8_t rm_bits;
  uint8_t src_bits;
  uint8_t dest_bits;
  uint8_t data_lo;
  uint8_t data_hi;
};

// struct for asm instructions
struct asm_inst
{
  char instruct[5];
  char operand_1[17]; // 16 bytes plus NUL terminator
  char operand_2[17];
};

#endif