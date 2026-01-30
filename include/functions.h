#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "header.h"

// Register to Resister functions //////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void assert(bool is_true);
void RR_GetReg(asm_inst* full_inst, bin_codes_t* bin_codes); 
void R_GetReg(asm_inst *full_inst, uint8_t reg_field, bool is_w, bool is_dest);
void GetReg_MOD00(asm_inst *full_inst, bin_codes_t *bin_codes);
void GetReg_IM_T_REGMEM(asm_inst *full_inst, bin_codes_t *bin_codes); 
uint16_t GetOpcode(uint8_t instruct);
uint16_t Uint16FromBytes(uint8_t lo_byte, uint8_t hi_byte);

void HandleInst(asm_inst *full_inst);
bool HandleByte_1(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_2(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_3(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_4(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_5(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_6(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);

#endif