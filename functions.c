// function to get instruction (first 6 bits)
#include "inst_key.h"
#include "functions.h"

INST get_instruction(INST instruct)
{
    // apply bit mask
    return instruct & 0b1111110000000000;
}

// whether d bit is 1
bool is_d(INST instruct)
{
    //apply bit mask
    return instruct & 0b0000001000000000;
}

// whether w bit is 1
bool is_w(INST instruct)
{
    //apply bit mask
    return instruct & 0b0000000100000000;    
}
