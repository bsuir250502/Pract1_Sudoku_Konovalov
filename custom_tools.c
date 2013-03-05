#include "custom_tools.h"
#define C_SUDOKU_TOOLS_H
 typedef struct com_line_options  {
    int type;                  /*0-option,1-argument */
     char opt;
     char *value;
} cl_opt;
int getopt_out(int, cl_opt *, argv_t *);
int read_conf_file(cell_t ** table, char *path) 
{
    FILE * conf;
    int i = 0, chk = 0;
    int cell_prop[3] = { 0, 0, 0 };
    char param;
    chk = strlen(path);
    while (*(path + chk - i) != '/' && *(path + chk - i) != '\\')
        i++;
    path = path + chk - i + 1;
    path = strncpy(path, "config\0", 7);
    path = path - chk + i - 1;
    i = 0;
    chk = 0;
    conf = fopen(path, "rt");
    if (!conf)
         {
        printf
            ("Config file is missing, ensure that 'config' file is in executable location.\n");
        return 0;
        }
    
    do
         {
        fscanf(conf, "%c", &param);
        if ((param == ',' || param == ';') && cell_prop[2] && i > 2)
             {
            i = 0;
            table[cell_prop[0]][cell_prop[1]].num = cell_prop[2];
            cell_prop[2] = 0;
            }
        if ((chk = param - '0') >= 0 && (chk = param - '0') <= 9)
             {
            if (i > 2)
                 {
                printf
                    ("Bad config file, see -h or --help for more info.\n");
                fclose(conf);
                return 0;
                }
            if (i < 2)
                cell_prop[i] = param - '0' - 1;
            
            else
                cell_prop[i] = param - '0';
            i++;
            }
    } while (param != ';');
    fclose(conf);
    return 1;
}

int getopt_c(int argc, char **argv, argv_t * Arguments) /*Will be remade */ 
{
    int i;
    cl_opt * Parameters;
    Parameters = (cl_opt *) calloc(argc - 1, sizeof(Parameters));
    for (i = 1; i < argc; i++)
        Parameters[i].value =
            (char *) calloc(strlen(*(argv + i)), sizeof(char));
    strncpy(Arguments->path, *argv, strlen(*argv));
    if (argc < 2)
        printf
            ("No arguments found. Are you really thinking help will display itself? Use -h or --help.\n");
    for (i = 1; i < argc; i++)
        if (**(argv + i) == '-')
             {
            Parameters[i - 1].type = 0;
            if (*(*(argv + i) + 1) == '-')
                Parameters[i - 1].opt = *(*(argv + i) + 2);
            
            else
                Parameters[i - 1].opt = *(*(argv + i) + 1);
            }
    
        else
             {
            Parameters[i - 1].type = 1;
            sscanf(*(argv + i), "%s", Parameters[i - 1].value);
            }
    if (!getopt_out(argc, Parameters, Arguments))
        return 0;
    return 1;
}

int getopt_out(int argc, cl_opt * Parameters, argv_t * Arguments) 
{
    int i = 0;
    for (i = 0; i < argc; i++)
        switch (Parameters[i].type)
             {
        case 0:
            switch (Parameters[i].opt)
                 {
            case 'h':
                Arguments->help = 1;
                break;
            case 'l':
                if (Parameters[i + 1].value)
                    Arguments->custom_conf_location =
                        Parameters[i + 1].value;
                break;
            case 'c':
                if (Parameters[i + 1].value)
                    Arguments->custom_conf_location =
                        Parameters[i + 1].value;
                break;
            case 'o':
                if (Parameters[i + 1].value)
                    Arguments->output_file = Parameters[i + 1].value;
                break;
                }
        case 1:
            if ((Parameters[i - 1].opt!='l' || Parameters[i - 1].opt!='c' || Parameters[i - 1].opt!='o') && i-1>0)
                 {
                printf("Unknown command %s", Parameters[i].value);
                return 0;
                }
            break;
            }
    return 1;
}
