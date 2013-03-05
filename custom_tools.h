#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct argv_  {
    char *path;
     char *custom_conf_location;
     int help;
     int output_type;
     char *output_file;
} argv_t;
typedef struct cell_  {
    int num, poss_count;
     int poss[9];
} cell_t;

#ifndef C_SUDOKU_TOOLS_H
#define C_SUDOKU_TOOLS_H
int getopt_c(int, char **, argv_t *);
int read_conf_file(cell_t **, char *);

#endif
