// function to get opcode (first 6 bits)
#include "functions.h"

INST get_opcode(INST instruct)
{
    // apply bit mask
    return instruct & 0b11111100;
}
