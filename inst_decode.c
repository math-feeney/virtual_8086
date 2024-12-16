// mov instruction decode for computer enhance

#include <stdio.h>
#include <string.h>

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

    // read file in
    // currently just prints one character at a time from the file
    // specified in the first argument from the cmd line arg
    char file_raw[1000];
    while(fgets(file_raw, 1000, fptr))
    {
        printf("%s", file_raw); // <- CONTINUE HERE I can't figure out how to make print the raw hex values
    }

    char test_bin = 0b00001100;

    //extract last 3 bits
    char test_out = test_bin & 0b00000111;


    // printf("%x\n", test_out);
    
    // close file
    fclose(fptr);
    return 0;
}
