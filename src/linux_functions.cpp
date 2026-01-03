#ifndef LINUX_H
#define LINUX_H

#include "linux_header.h"

int OpenFileRead(const char* path)
{
    // linux functions returns a fd
    int fd = open(path, O_RDONLY);
    if(!fd)
    {
        printf("Error opening file in linux\n");
        return 0;
    }

    return fd;
}

int CloseFileRead(int fd)
{
    if(close(fd) == -1)
    {
        printf("Error closing file linux");
        return -1;
    }
    return 0;
}

int ReadInstFromFile(int file_id, BYTE *buffer)
{
    if(!read(file_id, buffer, sizeof(BYTE)))
    {
        // end of file reached i think 
        return 0;
    }
    // return bytes read for now
    // which we assume is 1
    return 1;
}

#endif