#include "file.h"

int64_t create_db_file(char* file_path){
    int fd = open(file_path, O_RDONLY);
    if(fd != -1){
        fprintf(stderr, "File %s already exists\n", file_path);
        return ERROR;
    }
    fd = open(file_path, O_RDWR | O_CREAT, 0644);
    if(fd == -1){
        perror("Error opening file");
        return ERROR;
    }
    return fd;
}
int64_t open_db_file(char *file_path){
    int fd = open(file_path, O_RDWR);
    if (fd == -1)
    {
        fprintf(stderr, "File %s doesn't exist\n", file_path);
        return ERROR;
    }
    return fd;
}