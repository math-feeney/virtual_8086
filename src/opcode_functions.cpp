#include "header.h"
#include "functions.h"

// assert function
void assert(bool is_true)
{
    if(!is_true)
    {
        printf("\nassert failed\n");
        char *bad_val = nullptr;
        char bad_deref = *bad_val; 
        printf("%c\n", bad_deref);
    }
}

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
    if((instruct & 0b11111110) == 0b10100000)
    {
        return MEM_T_ACC;
    }
    if((instruct & 0b11111110) == 0b10100010)
    {
        return ACC_T_MEM;
    }
    if((instruct & 0b11111100) == 0b00000000)
    {
        return REGMEM_W_REG_ADD;
    }
    if((instruct & 0b11111100) == 0b00101000)
    {
        return REGMEM_A_REG_SUB;
    }
    if((instruct & 0b11111100) == 0b00111000)
    {
        return REGMEM_A_REG_CMP;
    }

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
    printf("\n");
    switch(format)
    {
        case STR_STR:
        {
            printf("%s %s, %s\n", full_inst->instruct, full_inst->operand_1, full_inst->operand_2);
        } break;
        case STR_INT:
        {
            printf("%s %s, %d\n", full_inst->instruct, full_inst->operand_1, int_value);
        } break;
        case INT_STR:
        {
            printf("%s %u, %s\n", full_inst->instruct, int_value, full_inst->operand_2);
        } break;
        case SRC_00:
        {
            printf("%s %s, [%s]\n", full_inst->instruct, full_inst->operand_1, full_inst->operand_2);
        } break;
        case DES_00:
        {
            printf("%s [%s], %s\n", full_inst->instruct, full_inst->operand_1, full_inst->operand_2);
        } break;
        case SRC_DIS:
        {
            printf("%s %s, [%s + %d]\n", full_inst->instruct, full_inst->operand_1, 
                                       full_inst->operand_2, full_inst->disp);
        } break;
        case DES_DIS:
        {
            printf("%s [%s + %d], %s\n", full_inst->instruct, full_inst->operand_1, 
                                       full_inst->disp, full_inst->operand_2);
        } break;
        case DIS_IM_8:
        {
            printf("%s [%s], byte %d\n", full_inst->instruct, full_inst->operand_1,
                                            full_inst->data);
        } break;
        case DIS_IM_16:
        {
            printf("%s [%s], word %d\n", full_inst->instruct, full_inst->operand_1,
                                            full_inst->data);
        } break;
        case EFDIS_IM_8:
        {
            printf("%s [%s + %d], word %d\n", full_inst->instruct, full_inst->operand_1,
                                            full_inst->disp, full_inst->data);
        } break;
        case EFDIS_IM_16:
        {
            printf("%s [%s + %d], word %d\n", full_inst->instruct, full_inst->operand_1,
                                            full_inst->disp, full_inst->data);
        } break;
        case DIR_ADD:
        {
            printf("%s %s, [%u]\n", full_inst->instruct, full_inst->operand_1,
                                    full_inst->disp);
        } break;
        case ACC_MEM:
        {
            printf("%s [%u], %s\n", full_inst->instruct, full_inst->disp,
                                    full_inst->operand_2);
        } break;
    }
    printf("\n");
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

        case MEM_T_ACC:
        {
            strcpy(full_inst->operand_1, "AX\0");
        } break;

        case ACC_T_MEM:
        {
            strcpy(full_inst->operand_2, "AX\0");
        } break;

        case IM_T_RM_ASC:
        {
            bin_codes->s_bit = (byte & 0b00000010) >> 1;
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case REGMEM_W_REG_ADD:
        {
            bin_codes->d_bit = (byte & 0b00000010) >> 1;
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case REGMEM_A_REG_SUB:
        {
            bin_codes->d_bit = (byte & 0b00000010) >> 1;
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case REGMEM_A_REG_CMP:
        {
            bin_codes->d_bit = (byte & 0b00000010) >> 1;
            bin_codes->w_bit = (byte & 0b00000001);
        } break;

        case IM_T_ACC_ADD:
        {
            bin_codes->w_bit = byte & 0b00000001;
        } break;
        
        case IM_F_ACC_SUB:
        {
            bin_codes->w_bit = byte & 0b00000001;
        } break;

        case IM_W_ACC_CMP:
        {
            bin_codes->w_bit = byte & 0b00000001;
        } break;
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
            bin_codes->rm_bits = (byte & 0b00000111);
            // d == 0: source is specified in REG field
            // d == 1: dest is specified in REG field
            if(bin_codes->mod_bits == REG_MOD)
            {

                RR_GetReg(full_inst, bin_codes); 

                // Register mode tells us this is the last byte
                // TODO: will want to move this to an outside function 
                // so we can handle in other ways besides just printing to 
                // console
                HandleInst(full_inst, STR_STR, 0);
                is_last_byte = true;
            }
            else // if mod_bits are 00, 01, or 10 
            {
                GetReg_MOD00(full_inst, bin_codes);
            }
            // We are done if mod == 00 unless looking for direct address
            if((bin_codes->mod_bits == MEM_MOD))
            {
                if (bin_codes->rm_bits != 0b110)
                {
                    bool is_src_add_calc = bin_codes->d_bit;
                    is_last_byte = true;
                    if(is_src_add_calc)
                    {
                        HandleInst(full_inst, SRC_00, 0);
                    }
                    else
                    {
                        HandleInst(full_inst, DES_00, 0);
                    }
                }
                else
                {
                    // nothing to do here I think,
                    // but we know a 16-bit direct address displacement follows
                    // TODO: We can probably just get rid of this else block
                    // once we're sure we don't need it 
                }
            }


        } break;

        case IM_T_REGMEM:
        {
            // manual specifically mentions bytes 4,5,6 are 0
            assert(!(byte & 0b00111000));
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->rm_bits = (byte & 0b00000111);
        } break;

        case IM_T_REG:
        {
            bool reg_is_dest = true;
            bin_codes->dest_bits = bin_codes->reg_bits;
            bin_codes->data_lo = byte;
            R_GetReg(full_inst, bin_codes->reg_bits, (bool)bin_codes->w_bit, reg_is_dest);
            if(!bin_codes->w_bit)
            {
                int signed_byte = (int8_t)bin_codes->data_lo;
                HandleInst(full_inst, STR_INT, signed_byte);
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

        case MEM_T_ACC:
        {
            bin_codes->disp_lo = byte;
        } break;

        case ACC_T_MEM:
        {
            bin_codes->disp_lo = byte;
        } break;

        case IM_T_RM_ASC:
        {
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->rm_bits = (byte & 0b00000111);
            uint8_t code = byte >> 3;
            switch(code) 
            {
                case IM_T_ADD:
                {
                    strcpy(full_inst->instruct, "ADD\0");
                } break;

                case IM_F_SUB:
                {
                    strcpy(full_inst->instruct, "SUB\0");
                } break;

                case IM_W_CMP:
                {
                    strcpy(full_inst->instruct, "CMP\0");
                } break;
            }
        }

        case REGMEM_W_REG_ADD:
        {
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->reg_bits = (byte & 0b00111000) >> 3;
            bin_codes->rm_bits = (byte & 0b00000111);

            if(bin_codes->mod_bits == MEM_MOD)
            {
                if (bin_codes->rm_bits != 0b110)
                { //START HERE, can't get operands to print ////////////
                    GetReg_IM_T_REGMEM(full_inst, bin_codes);
                    bool is_src_add_calc = bin_codes->d_bit;
                    is_last_byte = true;
                    if(is_src_add_calc)
                    {
                        HandleInst(full_inst, SRC_00, 0);
                    }
                    else
                    {
                        HandleInst(full_inst, DES_00, 0);
                    }
                }
                else
                {
                    // nothing to do here I think,
                    // but we know a 16-bit direct address displacement follows
                    // TODO: We can probably just get rid of this else block
                    // once we're sure we don't need it 
                }
            }

            if(bin_codes->mod_bits == REG_MOD)
            {
                RR_GetReg(full_inst, bin_codes);
                HandleInst(full_inst, STR_STR, 0);
                is_last_byte = true;
            }
        } break;

        case REGMEM_A_REG_SUB: 
        {
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->reg_bits = (byte & 0b00111000) >> 3;
            bin_codes->rm_bits = (byte & 0b00000111);

            if(bin_codes->mod_bits == REG_MOD)
            {
                RR_GetReg(full_inst, bin_codes);
                HandleInst(full_inst, STR_STR, 0);
                is_last_byte = true;
            }
        } break;

        case REGMEM_A_REG_CMP:
        {
            bin_codes->mod_bits = (byte & 0b11000000) >> 6;
            bin_codes->reg_bits = (byte & 0b00111000) >> 3;
            bin_codes->rm_bits = (byte & 0b00000111);

            if(bin_codes->mod_bits == REG_MOD)
            {
                RR_GetReg(full_inst, bin_codes);
                HandleInst(full_inst, STR_STR, 0);
                is_last_byte = true;
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
        case REGMEM_TF_REG:
        {
            bool is_src_add_calc = bin_codes->d_bit;

            // need to read this bit as data anyway
            // then if in 8-bit mem mod we are done
            bin_codes->data_lo = byte;
            if(bin_codes->mod_bits == MEM_MOD_8)
            {
                // TODO:
                // THINK ABOUT HOW TO CLEAN THIS UP
                // ALSO NEED TO DEAL WITH SIGNS in the ACTUAL PRINT (EG DI + -37)
                int8_t signed_byte = (int8_t)byte;
                full_inst->disp = (int16_t)signed_byte;
                is_last_byte = true;
                GetReg_IM_T_REGMEM(full_inst, bin_codes);
                if(is_src_add_calc)
                {
                    HandleInst(full_inst, SRC_DIS, 0);
                }
                else
                {
                    HandleInst(full_inst, DES_DIS, 0);
                }
            }
        } break;

        case IM_T_REGMEM:
        {
            if(bin_codes->mod_bits == MEM_MOD)
            {
                bin_codes->data_lo = byte;
                if(!bin_codes->w_bit)
                {
                    full_inst->data = (int16_t)bin_codes->data_lo;
                    GetReg_IM_T_REGMEM(full_inst, bin_codes);
                    HandleInst(full_inst, DIS_IM_8, 0);
                    is_last_byte = true;
                }
                else
                {
                    // W bit is set
                    // nothing to do I think
                }
            }
            else if(bin_codes->mod_bits == MEM_MOD_8)
            {
                bin_codes->disp_lo = byte;
            }
            else if(bin_codes->mod_bits == MEM_MOD_16)
            {
                bin_codes->disp_lo = byte;
            }
            else if(bin_codes->mod_bits == REG_MOD)
            {

            }

        } break;

        case IM_T_REG:
        {
            bin_codes->data_hi = byte;
            SWORD output_value;
            output_value = (SWORD)Uint16FromBytes(bin_codes->data_lo, bin_codes->data_hi);
            HandleInst(full_inst, STR_INT, (int)output_value);
            is_last_byte = true;
        } break;

        case MEM_T_ACC:
        {
            bin_codes->data_hi = byte;
            full_inst->disp = (int16_t)Uint16FromBytes(bin_codes->disp_lo, bin_codes->disp_hi); 
            // NOTE: notice we can just use DIR_ADD instruction format for this one
            // since we are just doing a direct address move, bute to the accumulator
            HandleInst(full_inst, DIR_ADD, 0);
            is_last_byte = true;
        } break;

        case ACC_T_MEM:
        {
            bin_codes->data_hi = byte;
            full_inst->disp = (int16_t)Uint16FromBytes(bin_codes->disp_lo, bin_codes->disp_hi);
            HandleInst(full_inst, ACC_MEM, 0);
            is_last_byte = true;
        } break;

        case REGMEM_W_REG_ADD:
        {
            bin_codes->disp_lo = byte;
            if(bin_codes->mod_bits == MEM_MOD_8)
            {
                bool is_src_add_calc = bin_codes->d_bit;
                int8_t signed_byte = (int8_t)byte;
                full_inst->disp = (int16_t)signed_byte;
                is_last_byte = true;
                GetReg_MOD00(full_inst, bin_codes);
                if(is_src_add_calc)
                {
                    HandleInst(full_inst, SRC_DIS, 0);
                }
                else
                {
                    HandleInst(full_inst, DES_DIS, 0);
                }
            }
        } break;
    }
    return is_last_byte;
}

bool HandleByte_4(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    bool is_last_byte = false;
    switch(opcode)
    {
        case REGMEM_TF_REG:
        {
            bin_codes->data_hi = byte;
            bool is_src_add_calc = bin_codes->d_bit;
            if(bin_codes->mod_bits == MEM_MOD_16)
            {
                full_inst->disp = Uint16FromBytes(bin_codes->data_lo, bin_codes->data_hi);
                is_last_byte = true;
                if(is_src_add_calc)
                {
                    HandleInst(full_inst, SRC_DIS, 0);
                }
                else
                {
                    HandleInst(full_inst, DES_DIS, 0);
                }
            }
            else if(bin_codes->mod_bits == MEM_MOD)
            {
                full_inst->disp = Uint16FromBytes(bin_codes->data_lo, bin_codes->data_hi);
                HandleInst(full_inst, DIR_ADD, 0);
            }
            is_last_byte = true;
        } break;
        case IM_T_REGMEM:
        {
            if(bin_codes->mod_bits == MEM_MOD)
            {
                bin_codes->data_hi = byte;
                full_inst->data = ((int16_t)bin_codes->data_hi << 8) | ((int16_t)bin_codes->data_lo);
                GetReg_IM_T_REGMEM(full_inst, bin_codes);
                HandleInst(full_inst, DIS_IM_16, 0);
                is_last_byte = true;
            }
            if(bin_codes->mod_bits == MEM_MOD_8)
            {
                bin_codes->data_lo = byte;
                if(!bin_codes->w_bit)
                {
                    full_inst->data = (int16_t)bin_codes->data_lo;
                    GetReg_IM_T_REGMEM(full_inst, bin_codes);
                    HandleInst(full_inst, EFDIS_IM_8, 0);
                    is_last_byte = true;
                }

            }
            if(bin_codes->mod_bits == MEM_MOD_16)
            {
                bin_codes->disp_hi = byte;
                full_inst->disp = ((int16_t)bin_codes->disp_hi << 8 | ((int16_t)bin_codes->disp_lo));
            }
        } break;
    }
    return is_last_byte;
}

bool HandleByte_5(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    bool is_last_byte = false;
    switch(opcode)
    {
        case IM_T_REGMEM:
        {
            if(bin_codes->mod_bits == MEM_MOD_8)
            {
                assert(bin_codes->w_bit);
                if(bin_codes->w_bit)
                {
                    bin_codes->data_hi = byte;
                    full_inst->data = ((int16_t)bin_codes->data_hi << 8) |  ((int16_t)bin_codes->data_lo);
                    GetReg_IM_T_REGMEM(full_inst, bin_codes);
                    HandleInst(full_inst, DIS_IM_8, 0);
                }

            }
            if(bin_codes->mod_bits == MEM_MOD_16)
            {
                bin_codes->data_lo = byte;
                if(!bin_codes->w_bit)
                {
                    full_inst->data = (int16_t)bin_codes->data_lo;
                    GetReg_IM_T_REGMEM(full_inst, bin_codes);
                    HandleInst(full_inst, EFDIS_IM_16, 0);
                    is_last_byte = true;
                }
                else
                {
                    // nothing to do I think
                }
            }
        } break;
    }
 
    return is_last_byte;
}

bool HandleByte_6(asm_inst *full_inst, bin_codes_t *bin_codes, uint16_t opcode, uint8_t byte)
{
    bool is_last_byte = false;
    switch(opcode)
    {
        case IM_T_REGMEM:
        {
            bin_codes->data_hi = byte;
            assert(bin_codes->mod_bits == MEM_MOD_16);
            assert(bin_codes->w_bit);
            bin_codes->data_hi = byte;
            full_inst->data = ((int16_t)bin_codes->data_hi << 8) |  ((int16_t)bin_codes->data_lo);
            GetReg_IM_T_REGMEM(full_inst, bin_codes);
            HandleInst(full_inst, EFDIS_IM_16, 0);
            is_last_byte = true;
        } break;
    }
    return is_last_byte;
}