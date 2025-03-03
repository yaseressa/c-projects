#pragma once
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "common.h"

int64_t create_db_file(char* file_path);
int64_t open_db_file(char *file_path);