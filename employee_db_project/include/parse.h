#pragma once

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "common.h"

#define HEADER_MAGIC 0x43C232F6
#define HEADER_VER 1
#define VARCHAR_LEN 256
typedef struct {
    uint64_t magic;
    uint16_t version;
    uint16_t count;
    uint64_t file_size;
} db_header_t;

typedef struct {
    char name[VARCHAR_LEN];
    char address[VARCHAR_LEN];
    uint64_t hours;
} employee_t;

int create_db_header(int fd, db_header_t **header_out);
int validate_db_header(int fd, db_header_t **header_out);
int read_employees(int fd, db_header_t *header_out, employee_t **employees_out);
void write_file(int fd, db_header_t *header, employee_t *employees);
int add_employee(char str[], db_header_t *dbhd, employee_t* employees);
int list_employees(db_header_t* header, employee_t *employees);
int delete_employee(char* name, db_header_t* header, employee_t **employees);
int update_employee(char* name, char* time_update, db_header_t* header, employee_t **employees);