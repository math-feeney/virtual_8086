// Includes key for 8086 instruction set

/*instruction key:
  this is the set of instructions that correspond to
  the first 6 bits of the instruction, so a 0b11111100 
  bit-mask will need to be applied first */
  
  #ifndef INST_KEY_H
  #define INST_KEY_H
    typedef enum {
        MOV = 0b0000000010001000,
        OTH = 0b0000000000000000

    };

  #endif