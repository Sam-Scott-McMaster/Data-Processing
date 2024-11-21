#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_cleaning.h"
#include "data_io.h"

/*
Cleans the data by removing rows containing `NaN` values.
new_rows is a pointer to an integer where the number of valid rows will be stored.
returns a new 2D array containing only the valid rows.
 */

float** clean_delete(float** data, int rows, int cols, int* new_rows) {
    float** new_data = NULL;
    *new_rows = 0;
    for (int i = 0; i < rows; i++) {
        int valid = 1;
        for (int j = 0; j < cols; j++) {
            if (isnan(data[i][j])) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            float** temp = realloc(new_data, (*new_rows + 1) * sizeof(float*));
            if (!temp) {
                fprintf(stderr, "Error: Memory reallocation failed.\n");
                free_2d_array(new_data, *new_rows);
                return NULL;
            }
            new_data = temp;
            // Allocate memory for new row
            new_data[*new_rows] = malloc(cols * sizeof(float));
            if (!new_data[*new_rows]) {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                free_2d_array(new_data, *new_rows);
                return NULL;
            }
            for (int j = 0; j < cols; j++) {
                new_data[*new_rows][j] = data[i][j];
            }
            (*new_rows)++;
        }
    }
    return new_data;
}

/*
Cleans the data by replacing NaN values with the column's average.
Takes the 2D array of float data as input
 */
void clean_impute(float** data, int rows, int cols) {
    for (int j = 0; j < cols; j++) {
        float sum = 0.0;
        int count = 0;
        for (int i = 0; i < rows; i++) {
            if (!isnan(data[i][j])) {
                sum += data[i][j];
                count++;
            }
        }
        float avg = count > 0 ? sum / count : 0.0;
        // Replace NaN values with column average
        for (int i = 0; i < rows; i++) {
            if (isnan(data[i][j])) {
                data[i][j] = avg;
            }
        }
    }
}
