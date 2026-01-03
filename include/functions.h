#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "header.h"

// declare function to get instruction (first 6 bits)
INST get_instruction(INST instruct);
INST get_reg(INST instruct);
INST get_regmem(INST instruct, bool is_w);

void match_instruction(INST instruct, char *inst_out);
void match_register(INST instruct, char *operand);


// d and w bit instructions
bool is_d(INST instruct);
bool is_w(INST instruct);

#endif