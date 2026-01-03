// mov instruction decode for computer enhance
#include "inst_key.h"
#include "functions.h"

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
    // set up file for reading
    FILE *fptr;

    //open file in read mode
    fptr = fopen(argv[1], "rb"); // "rb" tells fopen to expect a binary file

    // check for file error
    if(fptr == NULL)
    {
        printf("Error opening file\n");
        return 2;
    } 
    /*////////////////////////////////////////
    read file in and store each instruction
    *//////////////////////////////////////////
    
    INST byte;
  
    // will need to make more but this is for first instruction
    char inst_out[4]; // 3 letters plus NUL
    char left_operand[3]; // 2 plus NUL for both register letters
    char right_operand[3];
   
    while(fread(&byte, sizeof(INST), 1, fptr) != 0)
    {  
       //copy the correct string into the inst_out array based on opcode value in input byte 
       match_instruction(get_instruction(byte), inst_out); 

       //NEXT NEED TO COPY THE RIGHT PARTS INTO LEFT AND RIGHT
        if(is_d(byte))
        {
            match_register(get_reg(byte), left_operand);
            match_register(get_regmem(byte, is_w(byte)), right_operand); 
        }

        // else flip left and right operand
        else
        {
            match_register(get_reg(byte), right_operand);
            match_register(get_regmem(byte, is_w(byte)), left_operand); 
 
        }
        
       printf("%s %s, %s\n", inst_out, left_operand, right_operand);
    
     //FOR DEBUGGING //////////////////////////

     printf("actual value of binary: %x\n", byte);
    //printf("get_reg :  %x\n", get_reg(byte));
    //printf("get_regmem : %02x\n", get_regmem(byte, is_w(byte)));
    //printf("is_d : %x\n", is_d(byte));

    //////////////////////////////////////////////////
    
   
    }
    // close file
    fclose(fptr);

    /*/////////////////////////////////
    Print dissasembly 
    ////////////////////////////////*/
   
    //printf("Output:\n %s %s, %s\n", );


    return 0;
}
