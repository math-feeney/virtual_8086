// mov instruction decode for computer enhance

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

// create struct to represent the parts of an instruction
typedef struct instruct
{
    char byte_1;
    char byte_2;
};


int main(int argc, char* argv[])
{

    // make sure an argument was entered
    if(argc < 2)
    {
        printf("Must enter an input\n");
        return 1;
    }
    
    // get file name from the cmd line arg 
    char file_input[50];
    strcpy(file_input, argv[1]); 

    printf("you have entered %d arguments\n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // set up file for reading
    FILE *fptr;

    //open file in read mode
    fptr = fopen(file_input, "r");

    // check for file error
    if(fptr == NULL)
    {
        printf("Error opening file\n");
        return 2;
    } 






    char test_bin = 0b00001100;

    //extract last 3 bits
    char test_out = test_bin & 0b00000111;


    // printf("%x\n", test_out);
    
    // close file
    fclose(fptr);
    return 0;
}
