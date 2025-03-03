#ifndef PARSER_HEADER
#define PARSER_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <unistd.h>


typedef struct __attribute__((__packed__)){
    uint16_t version;
    uint16_t employees;
    uint64_t filesize;
} db_header;


db_header *create_db_header(uint16_t version, uint16_t employees, uint64_t filesize);
uint8_t parse_header(uint64_t fd, uint16_t* filesize);

#endif