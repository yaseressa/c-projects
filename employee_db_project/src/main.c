#include "main.h"

int main(int argc, char* argv[]){
    db_header_t *dbhd = NULL;
    int c;
    char *db_file = NULL, *add_str = NULL, *user = NULL, *time_update = NULL;
    bool new_file = false, list = false, delete = false;
    int dbfd = -1;
    employee_t *employees = NULL;
    while ((c = getopt(argc, argv, "nf:a:ldu:t:")) != -1)
    {
        switch(c){
            case 'n':
                new_file = true;
                break; 
            case 'f':
                db_file = optarg;
                break;
            case 'a':
                add_str = optarg;
                break;
            case 'l':
                list = true;
                break;
            case 'd':
                delete = true;
                break;
            case 't':
                time_update = optarg;
                break;
            case 'u':
                user = optarg;
                break;
            case '?':
                fprintf(stderr, "Unknown option -%c", c);
                break;
            default:
                return -1;
            }

    }
    if(db_file == NULL){
        printf("File is a required argument\n");
        print_usage(argv);
        return 0;
    }

    if(new_file){
        dbfd = create_db_file(db_file);
        if(dbfd == ERROR){
            fprintf(stderr, "Unable to create the db file\n");
            return ERROR;
        }
        create_db_header(dbfd, &dbhd);
        
        printf("New file: %d\n", new_file);
        printf("File path: %s\n", db_file);
    }
    else
    {
        dbfd = open_db_file(db_file);
        if(dbfd == ERROR){
            fprintf(stderr, "Unable to open the db file\n");
            return ERROR;
        }
        if(validate_db_header(dbfd, &dbhd) == ERROR){
            fprintf(stderr, "Failed to validate the database file. \n");
            return ERROR;
        }
       
    }


    if(read_employees(dbfd, dbhd, &employees) == ERROR){
        fprintf(stderr, "Error reading employees.\n");
        return ERROR;
    }

    if(add_str){
        employee_t* employees_resized = (employee_t*) realloc(employees, (++dbhd->count) * sizeof(employee_t));
        if(employees_resized == NULL){
            fprintf(stderr, "Failed in allocated memory for the new employee.\n");
            return ERROR;
        }
        
        employees = employees_resized;
        add_employee(add_str, dbhd, employees);
    }
    
    if(delete){
        if(delete_employee(user, dbhd, &employees) == ERROR){
            fprintf(stderr, "Error deleting employee.\n");
        }
    }

    if(time_update && user){
        if(update_employee(user, time_update, dbhd, &employees) == ERROR){
            fprintf(stderr, "Error deleting employee.\n");
        }
    }

    if(list){
        if(list_employees(dbhd, employees) == ERROR){
            fprintf(stderr, "No employees saved.\n");
        }
    }
    if(!(dbhd->count) && !new_file){
        fclose(fopen(db_file, "w"));
    }
    write_file(dbfd, dbhd, employees);

    return 0;
}
