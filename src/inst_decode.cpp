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
        static uint8_t byte_number = 1;
        static bool is_d = 0;
        static bool is_w = 0;
        static uint8_t mod_field, reg_field, rm_field;
        static uint8_t instruction, src_field, dest_field;
        static uint16_t opcode;

        if(byte_number == 1)
        {
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
            switch(opcode)
            {
                case REGMEM_TF_REG:
                {
                    is_d = byte & 0b00000010;   
                    is_w = byte & 0b00000001;
                } break;

                case IM_T_REGMEM:
                {
                    is_w = byte & 0b00000001;
                } break;

                case IM_T_REG:
                {
                    is_w = byte & 0b00001000;
                    reg_field = byte & 0b00000111;                    
                } break;
            }
            byte_number++;
            continue;
        }

        if(byte_number == 2)
        {
            switch(opcode)
            {
                case REGMEM_TF_REG:
                {
                    mod_field = (byte & 0b11000000) >> 6;
                    reg_field = (byte & 0b00111000) >> 3;

                    // d == 0: source is specified in REG field
                    // d == 1: dest is specified in REG field
                    if(mod_field == REG_MOD)
                    {
                        if(is_d)
                        {
                            dest_field = (byte & REG_FIELD) >> 3;
                            src_field = (byte & RM_FIELD);
                        }
                        else
                        {
                            dest_field = (byte & RM_FIELD);
                            src_field = (byte & REG_FIELD) >> 3;
                        }

                        RR_GetReg(&full_inst, src_field, dest_field, is_w); 

                        // Register mode tells us this is the last byte
                        printf("%s %s, %s\n", full_inst.instruct, full_inst.operand_1, full_inst.operand_2);
                        byte_number = 1;
                        continue; 
                    }
                } break;

                case IM_T_REGMEM:
                {
                    // START HERE KEEP FILLING IN THIS
                    // MAYBE AFTER CHAPTER 2 VIDEO
                } break;

                case IM_T_REG:
                {

                } break;
            }
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
