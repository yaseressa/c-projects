#ifndef FILE_HEADER
#define FILE_HEADER
#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <unistd.h>
int open_file_in_rw(char *file_name);
#endif