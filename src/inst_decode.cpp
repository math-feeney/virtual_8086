// mov instruction decode for computer enhance
#include "header.h"
#include "functions.h"
#include "linux_header.h"

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[])
{
    // make sure an argument was entered
    if(argc < 2)
    {
        printf("Must enter an input\n");
        return 1;
    }
    printf("you have entered %d arguments\n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }
    /*////////////////////////////////////////
    read file in and store each instruction
    *//////////////////////////////////////////
    
    BYTE byte;
    asm_inst full_inst;
  
    // Get file descriptor for linux
    // TODO: figure out how to make portable
    int file_id;
    file_id = OpenFileRead(argv[1]);
    if(!file_id)
    {
        printf("Error opening file\n");
        return 0;
    }

    // Decode instruction ////////////////////////
    /////////////////////////////////////////
    while(ReadInstFromFile(file_id, &byte))
    {
        static bin_codes_t bin_codes = {}; 
       /*
        uint8_t bin_codes_t.d_bit;
        uint8_t bin_codes_t.w_bit;
        uint8_t bin_codes_t.mod_bits;
        uint8_t bin_codes_t.reg_bits;
        uint8_t bin_codes_t.rm_bits;
        uint8_t bin_codes_t.src_bits;
        uint8_t bin_codes_t.dest_bits;
       */ 
        ////////////////////////////////////

        static uint8_t byte_number = 1;
        static uint8_t instruction; // got rid of 
        static uint16_t opcode;

        if(byte_number == 1)
        {
            // TODO: we can maybe move some of the below code into the
            // HandleByte_1() function, though not sure if we 
            // should/need to, think about it
            opcode = GetOpcode(byte);
            instruction = (uint8_t)(opcode >> 8); //the high order byte indicates instruction

            if(!opcode) 
            {
                printf("Error: Matching opcode not found in byte %u\n", byte_number);
                printf("byte: %02x\n", byte);
                return 1;
            }
            
            switch(instruction)
            {
                case MOV:
                {
                    strcpy(full_inst.instruct, "MOV\0"); 
                } break;

                case PUSH:
                {
                    strcpy(full_inst.instruct, "PUSH\0");
                } break;
            }
            // if on the last byte, (return value of HandleByte),
            // then back to top of loop
            if(HandleByte_1(&full_inst, &bin_codes, opcode, byte))
            {
                byte_number = 1;
                continue;
            }
            // otherwise move on to the next byte
            // NOTE: we need to move to next iteration of loop
            // because we need to read the next byte
            byte_number++;
            continue; 
        }

        if(byte_number == 2)
        {

            if(HandleByte_2(&full_inst, &bin_codes, opcode, byte))
            {
                byte_number = 1;
                continue;
            }
            byte_number++;
            continue;
        }
        if(byte_number == 3)
        {
            if(HandleByte_3(&full_inst, &bin_codes, opcode, byte))
            {
                byte_number = 1;
                continue;
            }
            byte_number++;
            continue;

        }
    }

    // close file
    // returns nonzero on error
    // TODO: try to standardize this return value maybe
    if(CloseFileRead(file_id) == -1)
    {
        printf("Error closing file\n");
        return 1;
    }

    return 0;
}
