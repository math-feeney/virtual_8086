#include <fcntl.h>
#include <unistd.h>
#include "header.h"

int OpenFileRead(const char* path);
int CloseFileRead(int fd);
int ReadInstFromFile(int file_id, BYTE *buffer);