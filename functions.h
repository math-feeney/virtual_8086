#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "inst_key.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// define type to store each instruction
typedef uint8_t INST;

// declare function to get instruction (first 6 bits)
INST get_instruction(INST instruct);

#endif