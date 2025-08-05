#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "inst_key.h"


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// define type to store each instruction
typedef uint16_t INST;

// declare function to get instruction (first 6 bits)
INST get_instruction(INST instruct);
void match_instruction(INST opcode, char *inst_out);

// d and w bit instructions
bool is_d(INST instruct);
bool is_w(INST instruct);

#endif