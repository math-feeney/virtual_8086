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

// get a 16-bite unsigend integer from 2 separate bytes
uint16_t Uint16FromBytes(uint8_t lo_byte, uint8_t hi_byte)
{
    return (uint16_t)lo_byte | ((uint16_t)hi_byte << 8);
}

//////////////////////////////////////////
// Function to handle fill inst 
// (if it's done)
// assumes the instruction is complete
//////////////////////////////////////////
// TODO: at some point we're probably going to want to change
// this from a printf to something else
void HandleInst(asm_inst *full_inst, uint8_t format, int int_value)
{
    switch(format)
    {
        case STR_STR:
        {
            printf("%s %s, %s\n", full_inst->instruct, full_inst->operand_1, full_inst->operand_2);
        } break;
        case STR_INT:
        {
            printf("%s %s, %u\n", full_inst->instruct, full_inst->operand_1, int_value);
        } break;
        case INT_STR:
        {
            printf("%s %u, %s\n", full_inst->instruct, int_value, full_inst->operand_2);
        } break;
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
                HandleInst(full_inst, STR_STR, 0);
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
            bool reg_is_dest = true;
            bin_codes->dest_bits = bin_codes->reg_bits;
            bin_codes->data_lo = byte;
            R_GetReg(full_inst, bin_codes->reg_bits, (bool)bin_codes->w_bit, reg_is_dest);
            if(!bin_codes->w_bit)
            {
                HandleInst(full_inst, STR_INT, (int)byte);
                is_last_byte = true;
            }
            // In this else case, there is a 16-bit disp
            // so this byte and the next byte are the data
            else
            {
                // Nothing to be done
                // we have data_lo and still
                // need to read in next byte for data_hi
                // is_last_byte is already false
            }
        } break;
    }
    return is_last_byte;
}

bool HandleByte_3(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    bool is_last_byte = false;
    switch(opcode)
    {
        case IM_T_REG:
        {
            bin_codes->data_hi = byte;
            uint16_t output_value;
            output_value = Uint16FromBytes(bin_codes->data_lo, bin_codes->data_hi);
            HandleInst(full_inst, STR_INT, (int)output_value);
            is_last_byte = true;
        } break;
    }
    return is_last_byte;
}