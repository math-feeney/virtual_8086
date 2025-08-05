// function to get instruction (first 6 bits)
#include "inst_key.h"
#include "functions.h"

// PAY ATTENTION TO ENDIANNESS!!!!!!!!!!!!!
INST get_instruction(INST instruct)
{
    // apply bit mask
    return instruct & 0b0000000011111100;
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
/* 
//code instruction to correct string
char inst_str[4](INST instruct)
{
    switch (expression) // **** FIGURE OUT HOW TO USE THIS TO ASSIGN ACTUAL STRINGS
    {
    case constant expression:
        /// code 
        break;
    
    default:
        break;
    } 
}
    */
