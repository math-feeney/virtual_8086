// Includes key for 8086 instruction set

/*instruction key:
  this is the set of instructions that correspond to
  the first 6 bits of the instruction, so a 0b11111100 
  bit-mask will need to be applied first */ 
    typedef enum {
        MOV = 0b10001000,
        OTH = 0b00000000

    };