#include "header.h"

// NOTE: high order byte in return value indicates instruction category
// full two bytes indicates specific opcode
// SEE: internal lookup table in "header.h"

// e.g.:
// 0x0102 -> 01 indicates "MOV", 0102 indicates

uint16_t GetOpcode(uint8_t instruct)
{
    if((instruct & 0b11111100) == 0b10001000)
    {
        return REGMEM_TF_REG;
    }
    if((instruct & 0b11111110) == 0b11000110)
    {
        return IM_T_REGMEM;
    }
    if((instruct & 0b11110000) == 0b10110000)
    {
        return IM_T_REG;
    }
    // TODO: add more opcodes

    else
    {
        //return 0 if can't find opcode
        return 0;
    }
}