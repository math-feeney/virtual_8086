#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "header.h"

// Register to Resister functions //////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void RR_GetReg(asm_inst* full_inst, uint8_t src_field, uint8_t dest_field, bool is_w); 
uint16_t GetOpcode(uint8_t instruct);

bool HandleByte_1(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_2(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_3(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_4(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_5(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);
bool HandleByte_6(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte);

#endif