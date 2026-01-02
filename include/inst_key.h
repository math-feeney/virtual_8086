// Includes key for 8086 instruction set

/*instruction key:
  this is the set of instructions that correspond to
  the first 6 bits of the instruction, so a 0b11111100 
  bit-mask will need to be applied first */
  
  #ifndef INST_KEY_H
  #define INST_KEY_H
    enum {
        MOV = 0b0000000010001000,
        OTH = 0b0000000000000000

    };

    // ENUM for the REG field encoding key
    // NOTE: This includes the W-bit (bit-8)
    enum {
      AL = 0b0000000000000000,
      CL = 0b0000100000000000,
      DL = 0b0001000000000000,
      BL = 0b0001100000000000,
      AH = 0b0010000000000000,
      CH = 0b0010100000000000,
      DH = 0b0011000000000000,
      BH = 0b0011100000000000,
      AX = 0b0000000000000001,
      CX = 0b0000100000000001,
      DX = 0b0001000000000001,
      BX = 0b0001100000000001,
      SP = 0b0010000000000001,
      BP = 0b0010100000000001,
      SI = 0b0011000000000001,
      DI = 0b0011100000000001,
    };

  #endif