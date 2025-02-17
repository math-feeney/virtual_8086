// mov instruction decode for computer enhance

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// define type to store each instruction
typedef uint8_t INST; // accounting for the 8086 16 bit register

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

// create struct to represent the parts of an instruction
typedef struct instruct
{
    INST byte_1;
    INST byte_2;
};
 
int main(int argc, char *argv[])
{

    // Just make a sample instruction now and deal with file I/O later
    INST test_inst = 00000010;

    // make sure an argument was entered
    if(argc < 2)
    {
        printf("Must enter an input\n");
        return 1;
    }
    
    // get file name from the cmd line arg 
    char file_input[50];
    strcpy(file_input, argv[1]); // maybe not necessary?

    printf("you have entered %d arguments\n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    // set up file for reading
    FILE *fptr;

    //open file in read mode
    fptr = fopen(file_input, "rb"); // "rb" tells fopen to expect a binary file

    // check for file error
    if(fptr == NULL)
    {
        printf("Error opening file\n");
        return 2;
    } 

    /*////////////////////////////////////////
    read file in and store each instruction
    *//////////////////////////////////////////


    // create array to store instructions
    INST instruct;

    INST isntruct_dest[0];

    while(fread(&instruct, sizeof(instruct), 1, fptr) != 0)
    {
        
      
    }
    
    // close file
    fclose(fptr);

    return 0;  
}
