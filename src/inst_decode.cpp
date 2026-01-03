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

    // Get instruction ////////////////////////
    /////////////////////////////////////////
    while(ReadInstFromFile(file_id, &byte))
    {
        static uint8_t byte_number = 1;
        bool is_w = 0;
        bool is_d = 0;
        uint8_t mod_field;
        uint8_t rm_field;
        uint8_t src_field;
        uint8_t dest_field;

        if(byte_number == 1)
        {
            // check opcode first
            switch(byte & OPCODE)
            {
                case REGMEM_TF_REG:
                {
                    strcpy(full_inst.instruct, "MOV\0"); 
                } break; // not sure yet if we need to keep this break

            }

            is_w = byte & W_BIT;
            is_d = byte & D_BIT;

            byte_number++;
        }

        if(byte_number == 2)
        {
            mod_field = byte & MOD_FIELD;
            rm_field = byte & RM_FIELD;

            // d == 0: source is specified in REG field
            // d == 1: dest is specified in REG field
            if(mod_field == REG_MOD)
            {
                if(is_d)
                {
                    src_field = (byte & REG_FIELD) >> 3;
                    dest_field = (byte & RM_FIELD);
                }
                else
                {
                    src_field = (byte & RM_FIELD);
                    dest_field = (byte & REG_FIELD) >> 3;
                }

                RR_GetReg(&full_inst, src_field, dest_field, is_w); 

                // Register mode tells us this is the last byte
                printf("%s %s, %s\n", full_inst.instruct, full_inst.operand_1, full_inst.operand_2);
                continue; 
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
