#include "parse.h"

void write_file(int fd, db_header_t *header, employee_t* employees){
    if (fd == -1)
    {
        fprintf(stderr, "Invalid file descriptor.\n");
    }
    int count = header->count;
    header->version = htons(header->version);
    header->count = htons(header->count);
    header->magic = htonl(header->magic);
    header->file_size = htonl(sizeof(db_header_t) + (sizeof(employee_t) * count));
    lseek(fd, 0, SEEK_SET);
    write(fd, header, sizeof(db_header_t));
    int i = 0;
    for (; i < count; i++){
        employee_t curr = employees[i];
        curr.hours = htonl(curr.hours);
        write(fd, &employees[i], sizeof(employee_t));
    }
}
int create_db_header(int fd, db_header_t **header_out){
    db_header_t *header = (db_header_t*) calloc(1, sizeof(db_header_t));
    if(header == NULL){
        fprintf(stderr, "Error allocating memory.\n");
        return ERROR;
    }
    header->version = HEADER_VER;
    header->count = 0;
    header->magic = HEADER_MAGIC;
    header->file_size = sizeof(db_header_t);
    *header_out = header;

    return SUCCESS;
}
int validate_db_header(int fd, db_header_t **header_out){
    struct stat dbstat = {0};

    if (fd == -1)
    {
        fprintf(stderr, "Invalid file descriptor.\n");
        return ERROR;
    }
    db_header_t *header = (db_header_t*) calloc(1, sizeof(db_header_t));
    if(header == NULL){
        fprintf(stderr, "Error allocating memory.\n");
        return ERROR;
    }

    if(read(fd, header, sizeof(db_header_t)) != sizeof(db_header_t)){
        perror("read");
        free(header);
        return ERROR;
    }

    header->version = ntohs(header->version);
    header->count = ntohs(header->count);
    header->magic = ntohl(header->magic);
    header->file_size = ntohl(header->file_size);
    if (header->magic != HEADER_MAGIC)
    {
        fprintf(stderr, "Invalid header magic.\n");
        free(header);
        return ERROR;
    }
    if(header->version != HEADER_VER){
        fprintf(stderr, "Invalid header version.\n");
        free(header);
        return ERROR;
    }
    fstat(fd, &dbstat);
    if(header->file_size != dbstat.st_size){
        fprintf(stderr, "Corrupted database file.\n");
        free(header);
        return ERROR;
    }

    *header_out = header;
    return SUCCESS;
}
int read_employees(int fd, db_header_t *header, employee_t **employees_out){
    if (fd == -1){
        fprintf(stderr, "Invalid file descriptor.\n");
        return ERROR;
    }
    int count = header->count;
    employee_t *employees = calloc(count, sizeof(employee_t));
    if(employees == NULL){
        fprintf(stderr, "Error allocating memory.\n");
        return ERROR;
    }
    read(fd, employees, count*sizeof(employee_t));
    int i = 0;
    for (; i < count; i++){
        employee_t em = employees[i];
        em.hours = ntohl(em.hours);
    }
    *employees_out = employees;
    return SUCCESS;
}


int add_employee(char str[], db_header_t *dbhd, employee_t* employees){
    if (strlen(str) < 1)
    {
        fprintf(stderr, "String is empty.");
        return ERROR;
    }
    char *name = strtok(str, ",");
    strcpy(employees[dbhd->count - 1].name, name);
    char *addr = strtok(NULL, ",");
    strcpy(employees[dbhd->count - 1].address, addr);
    char *hrs = strtok(NULL, ",");
    employees[dbhd->count - 1].hours = atoi(hrs);
    return SUCCESS;
}

int list_employees(db_header_t* header, employee_t *employees){
    int i = 0;
    if(!header->count)
        return ERROR;
    while (i < header->count)
    {
        printf("Employee %d:\n", i+1);
        printf("\tName > %s\n", employees[i].name);
        printf("\tAddress > %s\n", employees[i].address);
        printf("\tHours > %lu\n", employees[i].hours);
        i++;
    }
}

int delete_employee(char* name, db_header_t* header, employee_t** employees) {
    int i = 0, new_size = header->count;

    while (i < new_size) {
        if (strcmp((*employees)[i].name, name) == 0) {
            new_size--;
            for (int j = i; j < new_size; j++) {
                (*employees)[j] = (*employees)[j + 1];
            }
            continue; 
        }
        i++;
    }

    if (new_size != header->count) {
        employee_t* temp = realloc(*employees, new_size * sizeof(employee_t));
        if (temp == NULL && new_size > 0) {
            return -1; 
        }
        *employees = temp;
        header->count = new_size;
        return 1;
    }

    return 0;
}

int update_employee(char* name, char* time_update, db_header_t* header, employee_t **employees){
    int i = 0;

    while (i < header->count) {
        if (strcmp((*employees)[i].name, name) == 0){
            (*employees)[i].hours = atoi(time_update);
        }
        i++;
    }
}