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
    char inst_1[4]; // 3 letters plus NUL
    //char l_arg[3]; // 2 plus NUL for both register letters
    //char r_arg[3];
   
    while(fread(&byte, sizeof(INST), 1, fptr) != 0)
    {
       printf("%x\n", get_instruction(byte)); 
       if(get_instruction(byte) == MOV)
       {
        strcpy(inst_1, "MOV");// this of course only works once
        printf("match!\n");
        printf("This should say MOV: %s", inst_1); // this is just to test
       }
       printf("%s\n", "test"); 
    }
    // close file
    fclose(fptr);

    printf("in mov: %x\n", MOV);

    if(is_d)
    {
        printf("d is 1\n");
    }

    else
        printf("d is 0\n");

    // correctly assign relevant variables

    //l_arg

    /*/////////////////////////////////
    Print dissasembly 
    ////////////////////////////////*/
   
    //printf("Output:\n %s %s, %s\n", );


    return 0;  
}
