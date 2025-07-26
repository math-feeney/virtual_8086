// function to get instruction (first 6 bits)
#include "header.h"

INST get_instruction(INST instruct)
{
    // apply bit mask
    return instruct & 0b11111100;
}
