#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "header.h"

// Register to Resister functions //////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void RR_GetReg(asm_inst* full_inst, uint8_t src_field, uint8_t dest_field, bool is_w); 
uint16_t GetOpcode(uint8_t instruct);

#endif