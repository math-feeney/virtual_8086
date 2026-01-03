#include "header.h"
#include "functions.h"

// So far just includes functions in the "Register to Register" scenario 

void RR_GetReg(asm_inst* full_inst, uint8_t src_field, uint8_t dest_field, bool is_w) 
{
    if(is_w)
    {
        switch(dest_field)
        {
            case AX:
            {
                strcpy(full_inst->operand_1, "AX\0");
            } break;
            case CX:
            {
                strcpy(full_inst->operand_1, "CX\0");
            } break;
            case DX:
            {
                strcpy(full_inst->operand_1, "DX\0");
            } break;
            case BX:
            {
                strcpy(full_inst->operand_1, "BX\0");
            } break;
            case SP:
            {
                strcpy(full_inst->operand_1, "SP\0");
            } break;
            case BP:
            {
                strcpy(full_inst->operand_1, "BP\0");
            } break;
            case SI:
            {
                strcpy(full_inst->operand_1, "SI\0");
            } break;
            case DI:
            {
                strcpy(full_inst->operand_1, "DI\0");
            } break;
        }
        switch(src_field)
        {
            case AX:
            {
                strcpy(full_inst->operand_2, "AX\0");
            } break;
            case CX:
            {
                strcpy(full_inst->operand_2, "CX\0");
            } break;
            case DX:
            {
                strcpy(full_inst->operand_2, "DX\0");
            } break;
            case BX:
            {
                strcpy(full_inst->operand_2, "BX\0");
            } break;
            case SP:
            {
                strcpy(full_inst->operand_2, "SP\0");
            } break;
            case BP:
            {
                strcpy(full_inst->operand_2, "BP\0");
            } break;
            case SI:
            {
                strcpy(full_inst->operand_2, "SI\0");
            } break;
            case DI:
            {
                strcpy(full_inst->operand_2, "DI\0");
            } break;
        }
    }

    else
    {
        switch(dest_field)
        {
            case AL:
            {
                strcpy(full_inst->operand_1, "AL\0");
            } break;
            case CL:
            {
                strcpy(full_inst->operand_1, "CL\0");
            } break;
            case DL:
            {
                strcpy(full_inst->operand_1, "DL\0");
            } break;
            case BL:
            {
                strcpy(full_inst->operand_1, "BL\0");
            } break;
            case AH:
            {
                strcpy(full_inst->operand_1, "AH\0");
            } break;
            case CH:
            {
                strcpy(full_inst->operand_1, "CH\0");
            } break;
            case DH:
            {
                strcpy(full_inst->operand_1, "DH\0");
            } break;
            case BH:
            {
                strcpy(full_inst->operand_1, "BH\0");
            } break;
        }
        switch(src_field)
        {
            case AL:
            {
                strcpy(full_inst->operand_2, "AL\0");
            } break;
            case CL:
            {
                strcpy(full_inst->operand_2, "CL\0");
            } break;
            case DL:
            {
                strcpy(full_inst->operand_2, "DL\0");
            } break;
            case BL:
            {
                strcpy(full_inst->operand_2, "BL\0");
            } break;
            case AH:
            {
                strcpy(full_inst->operand_2, "AH\0");
            } break;
            case CH:
            {
                strcpy(full_inst->operand_2, "CH\0");
            } break;
            case DH:
            {
                strcpy(full_inst->operand_2, "DH\0");
            } break;
            case BH:
            {
                strcpy(full_inst->operand_2, "BH\0");
            } break;
        }
    }
}
    
