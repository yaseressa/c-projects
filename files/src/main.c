#include "main.h"

int main(int argc, char *argv[])
{
    int16_t filesize = 0;
    if (argc < 2)
    {
        printf("Usage %s <filename>\n", argv[0]);
        return 0;
    }
    int fd = open_file_in_rw(argv[1]);
    if (fd == -1) return -1;

    if(parse_header(fd, &filesize) == -1) return -1;
    printf("File size: %u", filesize);
    close(fd);
    return 0;
}