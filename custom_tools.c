#include "custom_tools.h"
#define C_SUDOKU_TOOLS_H

int display_usage(void);

int read_conf_file(cell_t ** table, char *path)
{
    FILE *conf;
    int i = 0, chk = 0;
    int cell_prop[3] = { 0, 0, 0 };
    char param;
    i = 0;
    chk = 0;
    conf = fopen(path, "rt");
    if (!conf) {
        printf
            ("Config file is missing, ensure that 'config' file is in executable location.\n");
        return 0;
    }
    do {
        fscanf(conf, "%c", &param);
        if ((param == ',' || param == ';') && cell_prop[2] && i > 2) {
            i = 0;
            table[cell_prop[0]][cell_prop[1]].num = cell_prop[2];
            cell_prop[2] = 0;
        }
        if ((chk = param - '0') >= 0 && (chk = param - '0') <= 9) {
            if (i > 2) {
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
    }
    while (param != ';');
    fclose(conf);
    return 1;
}

int options(argv_t * Arguments, int argc, char **argv)
{
    int no_arguments_needed = 1, i = 0, path_set = 0, len = 0;
    char *arg;
    char *destination = NULL;
    if (argc < 2)
        printf("No arguments found. Use -h or --help.\n");
    for (i = 1; i < argc; i++) {
        arg = *(argv + i);
        switch (getopt_c(arg)) {
        case 0:
            if (no_arguments_needed) {
                printf("Unknown command %s.\n", arg);
                return 0;
            }
            strncpy(destination, arg, strlen(arg));
            no_arguments_needed = 1;
            destination = NULL;
            break;
        case 1:
            if (no_arguments_needed == 0)
                return 0;
            switch (*arg) {
            case 'h':
                no_arguments_needed = 1;
                display_usage();
                break;
            case 'l':
                no_arguments_needed = 0;
                destination = Arguments->custom_conf_location;
                path_set = 1;
                break;
            case 'o':
                no_arguments_needed = 0;
                destination = Arguments->output_file;
                Arguments->output_type = 1;
                break;
            default:
                printf("Unknown command -%s.\n", arg);
                return 0;
                break;
            }
            break;
        case 2:
            if (no_arguments_needed == 0)
                return 0;
            if (!strcmp(arg, "help"))
                display_usage();
            else if (!strcmp(arg, "config-location")) {
                destination = Arguments->custom_conf_location;
                no_arguments_needed = 0;
                path_set = 1;
            } else if (!strcmp(arg, "output")) {
                no_arguments_needed = 0;
                destination = Arguments->output_file;
            } else {
                printf("Unknown command --%s.\n", arg);
                return 0;
            }
            break;
        default:
            printf("Unknown command %s.\n", arg);
            return 0;
            break;
        }
    }
    if (!path_set) {
        i = 0;
        len = strlen(*argv);
        strncpy(Arguments->custom_conf_location, *argv, strlen(*argv));
        while (*(Arguments->custom_conf_location + len - i) != '/'
               && *(Arguments->custom_conf_location + len - i) != '\\')
            i++;
        Arguments->custom_conf_location =
            Arguments->custom_conf_location + len - i + 1;
        Arguments->custom_conf_location =
            strncpy(Arguments->custom_conf_location, "config\0", 7);
        Arguments->custom_conf_location =
            Arguments->custom_conf_location - len + i - 1;
    }
    return 1;
}

int getopt_c(char *arg)
{
    int arg_type = 0, i = 1;
    while (*arg == '-') {
        arg_type++;
        *(arg) = *(arg + 1);
        while (*(arg + i - 1)) {
            *(arg + i) = *(arg + i + 1);
            i++;
        }
        i = 1;
    }
    return arg_type;
}

int display_usage(void)
{
    printf
        ("Usage: sudoku [options]\n -h --help                   Displays usage information\n -l --config_location <path> Defines config location(default is program directory)\n -o --output <path>          Sets output file name and location\n");
    return 1;
}
