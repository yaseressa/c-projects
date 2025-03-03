#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include "file.h"
#include "parse.h"

void print_usage(char* argv[]){
    printf("Usage: %s -n -f <db file>\n", argv[0]);
    printf("\t -n - create new database file\n");
    printf("\t -f - (required) path to db file\n");
}

