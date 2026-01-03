#include "header.h"
#include "functions.h"

// PAY ATTENTION TO ENDIANNESS!!!!!!!!!!!!!
// function to get instruction (first 6 bits)
INST get_instruction(INST instruct)
{
    // apply bit mask
    return instruct & 0b0000000011111100;
}

// get w-bit plus reg (bits 8, 11-13) 
INST get_reg(INST instruct)
{
    return instruct & 0b0011100000000001;
}
// get w-bit plus r/m (bits 8, 14-16) 
INST get_regmem(INST instruct, bool is_w)
{   
    //isolate regmem
    instruct = instruct & 0b0000011100000000;
    //bit shift to move to reg field so it works with enum
    instruct = instruct << 3;
    //return w-bit if there 
    if(is_w)
    {
    instruct = instruct | 0b000000000000001;
    }
    return instruct;
}


// whether d bit is 1
bool is_d(INST instruct)
{
    //apply bit mask
    return instruct & 0b0000000000000010;
}

// whether w bit is 1
bool is_w(INST instruct)
{
    //apply bit mask
    return instruct & 0b0000000000000001;    
}
 
// copy the correct instruction into the buffer created for the output instruction
void match_instruction(INST instruct, char *inst_out)
{
    switch (instruct) // **** FIGURE OUT HOW TO USE THIS TO ASSIGN ACTUAL STRINGS
    {
    case MOV:
        /// code
        strcpy(inst_out, "MOV\0");
        break;
    
    default:
        break;
    } 
}

void match_register(INST instruct, char *operand)
{
    switch (instruct) // **** FIGURE OUT HOW TO USE THIS TO ASSIGN ACTUAL STRINGS
    {
    case AL:
        /// code
        strcpy(operand, "AL\0");
        break;
    case CL:
        /// code
        strcpy(operand, "CL\0");
        break;
    case DL:
        /// code
        strcpy(operand, "DL\0");
        break;
    case BL:
        /// code
        strcpy(operand, "BL\0");
        break;
    case AH:
        /// code
        strcpy(operand, "AH\0");
        break;
    case CH:
        /// code
        strcpy(operand, "CH\0");
        break;
    case DH:
        /// code
        strcpy(operand, "DH\0");
        break;
    case BH:
        /// code
        strcpy(operand, "BH\0");
        break;
    case AX:
        /// code
        strcpy(operand, "AX\0");
        break;
    case CX:
        /// code
        strcpy(operand, "CX\0");
        break;
    case DX:
        /// code
        strcpy(operand, "DX\0");
        break;
    case BX:
        /// code
        strcpy(operand, "BX\0");
        break;
    case SP:
        /// code
        strcpy(operand, "SP\0");
        break;
    case BP:
        /// code
        strcpy(operand, "BP\0");
        break;
    case SI:
        /// code
        strcpy(operand, "SI\0");
        break;
    case DI:
        /// code
        strcpy(operand, "DI\0");
        break;
        
    default:
        strcpy(operand, "00\0");
        break;
    } 
}
    
