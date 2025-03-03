#include "file.h"

int open_file_in_rw(char *file_name){
    int fd = open(file_name, O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("open");
    }
    return fd;
}