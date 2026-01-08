#include "header.h"
#include "functions.h"

// NOTE: high order byte in return value indicates instruction category
// full two bytes indicates specific opcode
// SEE: internal lookup table in "header.h"

// e.g.:
// 0x0102 -> 01 indicates "MOV", 0102 indicates REGMEM_TF_REG

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
////////////////////////////////////////////
// functions to handle each subsequent byte
////////////////////////////////////////////

bool HandleByte_1(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    // return value defaults to false, so we only need to switch to 
    // true if we determine we are on the last byte of the 
    // instruction
    bool is_last_byte = false;

    switch(opcode)
    {
        case REGMEM_TF_REG:
        {
            bin_codes->d_bit = (byte & 0b00000010) >> 1;
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case IM_T_REGMEM:
        {
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case IM_T_REG:
        {
            bin_codes->w_bit = (byte & 0b00001000) >> 3;
            bin_codes->reg_bits = (byte & 0b00000111);                    
        } break;
/*
        case XXX:
        {

        } break;

        case XXX:
        {

        } break;
*/
    }
    return is_last_byte;
}

bool HandleByte_2(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    bool is_last_byte = false;

    switch(opcode)
    {
        case REGMEM_TF_REG:
        {
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->reg_bits = (byte & 0b00111000) >> 3;
            // d == 0: source is specified in REG field
            // d == 1: dest is specified in REG field
            if(bin_codes->mod_bits == REG_MOD)
            {
                if(bin_codes->d_bit)
                {
                    bin_codes->dest_bits = (byte & 0b00111000) >> 3;
                    bin_codes->src_bits = (byte & 0b00000111);
                }
                else
                {
                    bin_codes->dest_bits = (byte & 0b00000111);
                    bin_codes->src_bits = (byte & 0b00111000) >> 3;
                }

                // TODO: this might actually be more generalizable
                // to other instructions types
                uint8_t src_field = bin_codes->src_bits;
                uint8_t dest_field = bin_codes->dest_bits;

                RR_GetReg(full_inst, src_field, dest_field, bin_codes->w_bit); 

                // Register mode tells us this is the last byte
                // TODO: will want to move this to an outside function 
                // so we can handle in other ways besides just printing to 
                // console
                printf("%s %s, %s\n", full_inst->instruct, full_inst->operand_1, full_inst->operand_2);
                is_last_byte = true;
            }
            else if(bin_codes->reg_bits == MEM_MOD)
            {
                //something
                printf("should not hit this yet\n");
            }



        } break;

        case IM_T_REGMEM:
        {
        } break;

        case IM_T_REG:
        {
        } break;
    }
    return is_last_byte;
}
