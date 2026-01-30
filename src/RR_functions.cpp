#include "header.h"
#include "functions.h"

//////////////////////////////////////////////////////////////////////
// Functions that set the values in the decoded instruction struct
// i.e. convert from tmachine code to assembly
////////////////////////////////////////////////////////////////////

// NOTE: Many of these switch statements are very condensed on purpose
// they are basically lookup tables and this makes them much easier to read 
// than the usual switch case style

// TODO: Some of these functions can probably be cleaned up and condensed into fewer, more general functions
// to handle more situations

// Set operands in a Register-to-Register MOV, so both are registers
// *Assumes MOD field is 0b11
void RR_GetReg(asm_inst* full_inst, bin_codes_t* bin_codes) 
{
    bool is_w = bin_codes->w_bit;

    if(bin_codes->d_bit)
    {
        bin_codes->dest_bits = bin_codes->reg_bits;
        bin_codes->src_bits = bin_codes->rm_bits;
    }
    else
    {
        bin_codes->dest_bits = bin_codes->reg_bits;

        bin_codes->src_bits = bin_codes->rm_bits;
    }

    uint8_t dest_field = bin_codes->dest_bits;
    uint8_t src_field = bin_codes->src_bits;

    if(is_w)
    {
        switch(dest_field)
        {
            case AX: strcpy(full_inst->operand_1, "AX\0"); break;
            case CX: strcpy(full_inst->operand_1, "CX\0"); break;
            case DX: strcpy(full_inst->operand_1, "DX\0"); break;
            case BX: strcpy(full_inst->operand_1, "BX\0"); break;
            case SP: strcpy(full_inst->operand_1, "SP\0"); break;
            case BP: strcpy(full_inst->operand_1, "BP\0"); break;
            case SI: strcpy(full_inst->operand_1, "SI\0"); break;
            case DI: strcpy(full_inst->operand_1, "DI\0"); break;
        }

        switch(src_field)
        {
            case AX: strcpy(full_inst->operand_2, "AX\0"); break;
            case CX: strcpy(full_inst->operand_2, "CX\0"); break;
            case DX: strcpy(full_inst->operand_2, "DX\0"); break;
            case BX: strcpy(full_inst->operand_2, "BX\0"); break;
            case SP: strcpy(full_inst->operand_2, "SP\0"); break;
            case BP: strcpy(full_inst->operand_2, "BP\0"); break;
            case SI: strcpy(full_inst->operand_2, "SI\0"); break;
            case DI: strcpy(full_inst->operand_2, "DI\0"); break;
        }
    }

    else
    {
        switch(dest_field)
        {
            case AL: strcpy(full_inst->operand_1, "AL\0"); break;
            case CL: strcpy(full_inst->operand_1, "CL\0"); break;
            case DL: strcpy(full_inst->operand_1, "DL\0"); break;
            case BL: strcpy(full_inst->operand_1, "BL\0"); break;
            case AH: strcpy(full_inst->operand_1, "AH\0"); break;
            case CH: strcpy(full_inst->operand_1, "CH\0"); break;
            case DH: strcpy(full_inst->operand_1, "DH\0"); break;
            case BH: strcpy(full_inst->operand_1, "BH\0"); break;
        }
        switch(src_field)
        {
            case AL: strcpy(full_inst->operand_2, "AL\0"); break;
            case CL: strcpy(full_inst->operand_2, "CL\0"); break;
            case DL: strcpy(full_inst->operand_2, "DL\0"); break;
            case BL: strcpy(full_inst->operand_2, "BL\0"); break;
            case AH: strcpy(full_inst->operand_2, "AH\0"); break;
            case CH: strcpy(full_inst->operand_2, "CH\0"); break;
            case DH: strcpy(full_inst->operand_2, "DH\0"); break;
            case BH: strcpy(full_inst->operand_2, "BH\0"); break;
        }
    }
}
    
// get single register from a field 
// note last parameter is whether to assign to src or dest operand
void R_GetReg(asm_inst *full_inst, uint8_t reg_field, bool is_w, bool is_dest) 
{
    if(is_w)
    {
        if(is_dest)
        {
            switch(reg_field)
            {
                case AX: strcpy(full_inst->operand_1, "AX\0"); break;
                case CX: strcpy(full_inst->operand_1, "CX\0"); break;
                case DX: strcpy(full_inst->operand_1, "DX\0"); break;
                case BX: strcpy(full_inst->operand_1, "BX\0"); break;
                case SP: strcpy(full_inst->operand_1, "SP\0"); break;
                case BP: strcpy(full_inst->operand_1, "BP\0"); break;
                case SI: strcpy(full_inst->operand_1, "SI\0"); break;
                case DI: strcpy(full_inst->operand_1, "DI\0"); break;
            }
        }
        else
        {
            switch(reg_field)
            {
                case AX: strcpy(full_inst->operand_2, "AX\0"); break;
                case CX: strcpy(full_inst->operand_2, "CX\0"); break;
                case DX: strcpy(full_inst->operand_2, "DX\0"); break;
                case BX: strcpy(full_inst->operand_2, "BX\0"); break;
                case SP: strcpy(full_inst->operand_2, "SP\0"); break;
                case BP: strcpy(full_inst->operand_2, "BP\0"); break;
                case SI: strcpy(full_inst->operand_2, "SI\0"); break;
                case DI: strcpy(full_inst->operand_2, "DI\0"); break;
            }
        }
    }
    else
    {
        if(is_dest)
        {
            switch(reg_field)
            {
                case AL: strcpy(full_inst->operand_1, "AL\0"); break;
                case CL: strcpy(full_inst->operand_1, "CL\0"); break;
                case DL: strcpy(full_inst->operand_1, "DL\0"); break;
                case BL: strcpy(full_inst->operand_1, "BL\0"); break;
                case AH: strcpy(full_inst->operand_1, "AH\0"); break;
                case CH: strcpy(full_inst->operand_1, "CH\0"); break;
                case DH: strcpy(full_inst->operand_1, "DH\0"); break;
                case BH: strcpy(full_inst->operand_1, "BH\0"); break;
            }
        }
        else
        {
            switch(reg_field)
            {
                case AL: strcpy(full_inst->operand_2, "AL\0"); break;
                case CL: strcpy(full_inst->operand_2, "CL\0"); break;
                case DL: strcpy(full_inst->operand_2, "DL\0"); break;
                case BL: strcpy(full_inst->operand_2, "BL\0"); break;
                case AH: strcpy(full_inst->operand_2, "AH\0"); break;
                case CH: strcpy(full_inst->operand_2, "CH\0"); break;
                case DH: strcpy(full_inst->operand_2, "DH\0"); break;
                case BH: strcpy(full_inst->operand_2, "BH\0"); break;
            }
        }
    }
}

// this resolved an unreferenced function linker error
// can probably get rid of soon
void force_emit() {
    R_GetReg(nullptr, 0, false, false);
}

void SwapOperands(asm_inst *full_inst)
{
    char holding[17];
    strcpy(holding, full_inst->operand_1);
    strcpy(full_inst->operand_1, full_inst->operand_2);
    strcpy(full_inst->operand_2, holding);
}

//Get the register operand values for when mod field is 00 (no displacement except if rm == 0b110) 
void GetReg_MOD00(asm_inst *full_inst, bin_codes_t *bin_codes) 
{
    // assume d == 1, inst source is in the REG field
    // NOTE, we test d == 1 at the end, if false, we swap
    if(!bin_codes->w_bit)
    {
        switch(bin_codes->reg_bits)
        {
            case AL: strcpy(full_inst->operand_1, "AL\0"); break;
            case CL: strcpy(full_inst->operand_1, "CL\0"); break;
            case DL: strcpy(full_inst->operand_1, "DL\0"); break;
            case BL: strcpy(full_inst->operand_1, "BL\0"); break;
            case AH: strcpy(full_inst->operand_1, "AH\0"); break;
            case CH: strcpy(full_inst->operand_1, "CH\0"); break;
            case DH: strcpy(full_inst->operand_1, "DH\0"); break;
            case BH: strcpy(full_inst->operand_1, "BH\0"); break;
        }
    }
    else
    {
        switch(bin_codes->reg_bits)
        {
            case AX: strcpy(full_inst->operand_1, "AX\0"); break;
            case CX: strcpy(full_inst->operand_1, "CX\0"); break;
            case DX: strcpy(full_inst->operand_1, "DX\0"); break;
            case BX: strcpy(full_inst->operand_1, "BX\0"); break;
            case SP: strcpy(full_inst->operand_1, "SP\0"); break;
            case BP: strcpy(full_inst->operand_1, "BP\0"); break;
            case SI: strcpy(full_inst->operand_1, "SI\0"); break;
            case DI: strcpy(full_inst->operand_1, "DI\0"); break;
        }
    }
    switch(bin_codes->rm_bits)
    {
        case BX_PLUS_SI: strcpy(full_inst->operand_2, "BX + SI\0"); break;
        case BX_PLUS_DI: strcpy(full_inst->operand_2, "BX + DI\0"); break;
        case BP_PLUS_SI: strcpy(full_inst->operand_2, "BP + SI\0"); break;
        case BP_PLUS_DI: strcpy(full_inst->operand_2, "BP + DI\0"); break;
        case SI_EFF_ADD: strcpy(full_inst->operand_2, "SI\0"); break;
        case DI_EFF_ADD: strcpy(full_inst->operand_2, "DI\0"); break;
        case BP_DIR_ADD: strcpy(full_inst->operand_2, "BP\0"); break;
        case BX_EFF_ADD: strcpy(full_inst->operand_2, "BX\0"); break;
    }
    if(!bin_codes->d_bit)
    {
        SwapOperands(full_inst);
    }
}

void GetReg_IM_T_REGMEM(asm_inst *full_inst, bin_codes_t *bin_codes) 
{
    // There is no d-bit, this is moving an immediate value to reg/mem
    // so obviously the reg/mem val is the destination
    if(bin_codes->mod_bits == REG_MOD)
    {
        if(bin_codes->w_bit)
        {
            switch(bin_codes->rm_bits)
            {
                case AX: strcpy(full_inst->operand_1, "AX\0"); break;
                case CX: strcpy(full_inst->operand_1, "CX\0"); break;
                case DX: strcpy(full_inst->operand_1, "DX\0"); break;
                case BX: strcpy(full_inst->operand_1, "BX\0"); break;
                case SP: strcpy(full_inst->operand_1, "SP\0"); break;
                case BP: strcpy(full_inst->operand_1, "BP\0"); break;
                case SI: strcpy(full_inst->operand_1, "SI\0"); break;
                case DI: strcpy(full_inst->operand_1, "DI\0"); break;

            }
        }
        else
        {
            switch(bin_codes->rm_bits)
            {
                case AL: strcpy(full_inst->operand_1, "AL\0"); break;
                case CL: strcpy(full_inst->operand_1, "CL\0"); break;
                case DL: strcpy(full_inst->operand_1, "DL\0"); break;
                case BL: strcpy(full_inst->operand_1, "BL\0"); break;
                case AH: strcpy(full_inst->operand_1, "AH\0"); break;
                case CH: strcpy(full_inst->operand_1, "CH\0"); break;
                case DH: strcpy(full_inst->operand_1, "DH\0"); break;
                case BH: strcpy(full_inst->operand_1, "BH\0"); break;

            }
        }
    }
    else
    {
        switch(bin_codes->rm_bits)
        {
            case BX_PLUS_SI: strcpy(full_inst->operand_1, "BX + SI\0"); break;
            case BX_PLUS_DI: strcpy(full_inst->operand_1, "BX + DI\0"); break;
            case BP_PLUS_SI: strcpy(full_inst->operand_1, "BP + SI\0"); break;
            case BP_PLUS_DI: strcpy(full_inst->operand_1, "BP + DI\0"); break;
            case SI_EFF_ADD: strcpy(full_inst->operand_1, "SI\0"); break;
            case DI_EFF_ADD: strcpy(full_inst->operand_1, "DI\0"); break;
            case BP_DIR_ADD: strcpy(full_inst->operand_1, "BP\0"); break;
            case BX_EFF_ADD: strcpy(full_inst->operand_1, "BX\0"); break;
        }
    }
}









