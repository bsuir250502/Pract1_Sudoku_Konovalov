#include "stdio.h"
#include "stdlib.h"
#include "string.h"
typedef struct argv_ {
    char *custom_conf_location;
    int output_enabled;
    char *output_file;
} argv_t;
typedef struct cell_ {
    int num, poss_count;
    int poss[9];
} cell_t;
#ifndef C_SUDOKU_TOOLS_H

int options(argv_t *, int, char **);
int getopt_c(char *);
int read_conf_file(cell_t **, char *);
int write_output_file(cell_t **, char *);

#endif
