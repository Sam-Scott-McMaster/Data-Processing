//Viraj Patel, patev110, November 21

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_io.h"
#include "data_cleaning.h"
/*
Entry point for the data cleaner program.
This program reads a 2D array of float data from standard input, cleans it
using row deletion or NaN value imputation, and
outputs the cleaned data. The cleaning method is determined by the `-d` 
command-line flag.
*/

int main(int argc, char* argv[]) {
    int rows, cols, new_rows;
    int use_delete = 0;

    // Check for the -d flag
    if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        use_delete = 1;
    } else if (argc > 1) {
        fprintf(stderr, "Usage: %s [-d]\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Read data from stdin
    float** data = read_data(&rows, &cols);
    if (!data) {
        fprintf(stderr, "Error reading data.\n");
        return EXIT_FAILURE;
    }

    // Clean data using the selected strategy
    float** cleaned_data = NULL;
    if (use_delete) {
        cleaned_data = clean_delete(data, rows, cols, &new_rows);
        free_2d_array(data, rows);
    } else {
        clean_impute(data, rows, cols);
        cleaned_data = data;
        new_rows = rows;
    }

    // Output cleaned data
    output_data(cleaned_data, new_rows, cols);

    // Free memory
    free_2d_array(cleaned_data, new_rows);

    return EXIT_SUCCESS;
}
