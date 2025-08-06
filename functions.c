#include "inst_key.h"
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
void match_instruction(INST opcode, char *inst_out)
{
    switch (opcode) // **** FIGURE OUT HOW TO USE THIS TO ASSIGN ACTUAL STRINGS
    {
    case MOV:
        /// code
        strcpy(inst_out, "MOV\n");
        break;
    
    default:
        break;
    } 
}


    
