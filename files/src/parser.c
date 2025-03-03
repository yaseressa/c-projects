#include "parser.h"

db_header *create_db_header(uint16_t version, uint16_t employees, uint64_t filesize){
    db_header *header = (db_header *)malloc(sizeof(db_header));
    header->employees = employees;
    header->filesize = filesize;
    header->version = version;
    return header;
}

uint8_t parse_header(uint64_t fd, uint16_t* filesize){
    db_header *header = create_db_header(0, 0, 0);
    struct stat db_stat = {0};
    
    if(read(fd, header, sizeof(*header))!= sizeof(*header)){
        perror("read");
        return -1;
    }
    if(fstat(fd, &db_stat) == -1){
        perror("fstat");
        return -1;
    }
    if(header->filesize != db_stat.st_size){
        fprintf(stderr, "Permission denied!");
        return -1;
    }
    *filesize = db_stat.st_size;
    return 0;
}
