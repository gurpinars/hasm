#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <getopt.h>
#include "parser.h"


int main(int argc, char *argv[]) {
    int opt;
    FILE* src_file = NULL;
    struct Symbol* sym_tbl = NULL;

    const char* usage = "Usage: ./hasm [file]";
    while ((opt = getopt(argc, argv, "h:")) != -1)
    {
        switch (opt){
            case 'h':
                printf("%s\n", usage);
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [file]\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (argv[optind] == NULL || strlen(argv[optind]) == 0)
        printf("%s\n", usage);
    else
        src_file = fopen(argv[optind], "r");

    assert(src_file != NULL);

    // initializing symbol table
    init_sym_table(&sym_tbl);
    // extracting labels
    preprocessor(src_file, argv[optind], &sym_tbl);
    // processing
    processor(argv[optind], &sym_tbl);

    clear(&sym_tbl);

    fclose(src_file);
    return 0;
}