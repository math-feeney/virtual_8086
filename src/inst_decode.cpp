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
    
    INST inst;
  
    // Get file descriptor for linux
    // TODO: figure out how to make portable
    int file_id;
    file_id = OpenFileRead(argv[1]);
    if(!file_id)
    {
        printf("Error opening file\n");
        return 0;
    }

    while(ReadInstFromFile(file_id, &inst))
    {
        printf("DEBUG SUCCESSFULLY READ SOMETHING!\n");
        printf("%04x\n", inst);
        inst = be16toh()
        uint8_t hi = 
        printf("Low Byte(assuming little endian): %02x\n", (inst & 0xFF00) >> 8);
        printf("High Byte(assuming little endian): %02x\n", (inst & 0x00FF));
    }
  /* 
    /////////////////////////////////////
    while(fread(file_id, sizeof(INST), 1, fptr) != 0)
    {  
       //copy the correct string into the inst_out array based on opcode value in input byte 
       match_instruction(get_instruction(inst), inst_out); 

       //NEXT NEED TO COPY THE RIGHT PARTS INTO LEFT AND RIGHT
        if(is_d(inst))
        {
            match_register(get_reg(inst), left_operand);
            match_register(get_regmem(inst, is_w(inst)), right_operand); 
        }

        // else flip left and right operand
        else
        {
            match_register(get_reg(inst), right_operand);
            match_register(get_regmem(inst, is_w(inst)), left_operand); 
 
        }
        
       printf("%s %s, %s\n", inst_out, left_operand, right_operand);
*/
     //FOR DEBUGGING //////////////////////////

    // printf("actual value of binary: %x\n", inst);
    // printf("get_reg :  %x\n", get_reg(inst));
    // printf("get_regmem : %02x\n", get_regmem(inst, is_w(byte)));
    // printf("is_d : %x\n", is_d(byte));

    //////////////////////////////////////////////////
    
   

    // close file
    // returns nonzero on error
    // TODO: try to standardize this return value maybe
    if(CloseFileRead(file_id) == -1)
    {
        printf("Error closing file\n");
        return 1;
    }
    /*/////////////////////////////////
    Print dissasembly 
    ////////////////////////////////*/
   
    //printf("Output:\n %s %s, %s\n", );


    return 0;
}
