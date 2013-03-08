#include "custom_tools.h"

/*int analysis_rowsNcolumns (cell_t**);*/
/*int analysis_squareNode (cell_t**);*/
/*int advanced_analyzis (cell_t**);*/

int main(int argc, char **argv)
{
    argv_t Arguments;
    cell_t **table;
    int i = 0, j = 0;
    Arguments.output_file = (char *) calloc(255, sizeof(char));
    Arguments.custom_conf_location = (char *) calloc(255, sizeof(char));
    Arguments.output_enabled = 0;
    if (!options(&Arguments, argc, argv)) {
        printf("Error in parsing parameters.\n");
        return 0;
    }
    table = (cell_t **) calloc(9, sizeof(cell_t *));
    for (i = 0; i < 9; i++)
        *(table + i) = (cell_t *) calloc(9, sizeof(cell_t));
    if (!read_conf_file(table, Arguments.custom_conf_location))
        printf("Error in reading config file.\n");
    if (Arguments.output_enabled)
        if (!write_output_file(table, Arguments.output_file))
            printf("Error in writing file");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            printf(" %d ", table[i][j].num);
        printf("\n");
    }
    return (0);                 /* I like it */
}

/*int analysis_rowsNcolumns (cell_t** table)
{
	int i=0,j=0,node_val=0,a_=0,b_=0;
	node_val=table[a_][b_].num;
	if (!table[a_][b_].num)
	{
		for (j=0;j<9;j++)
			if (table[a_][j].num)
				table[a_][b_].poss[table[a_][j].num-1]=table[a_][j].num;
		for (i=0;i<9;i++)
			if (table[i][b_].num)
				table[a_][b_].poss[table[i][b_].num-1]=table[i][b_].num;	
	}
	return 1;
}*/

/*int analysis_squareNode (cell_t** table)
{
	int i=0;
	return 1;
}*/
