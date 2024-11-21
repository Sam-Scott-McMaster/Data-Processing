#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_processing.h"

/*
Reads a 2D array of float data from standard input.
Pointer to an integer where the number of rows will be stored.
Pointer to an integer where the number of columns will be stored.
2D array containing the input data.
 */
float** read_data(int* rows, int* cols) {
    scanf("%d %d", rows, cols);
    if (*rows <= 0 || *cols <= 0) {
        fprintf(stderr, "Error: Invalid dimensions.\n");
        return NULL;
    }
    // Allocate memory for rows
    float** data = malloc(*rows * sizeof(float*));
    if (!data) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }
    for (int i = 0; i < *rows; i++) {
        data[i] = malloc(*cols * sizeof(float));
        if (!data[i]) {
            fprintf(stderr, "Error: Memory allocation failed.\n");
            free_2d_array(data, i);
            return NULL;
        }
        for (int j = 0; j < *cols; j++) {
            scanf("%f", &data[i][j]);
        }
    }
    return data;
}

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

/* 
Outputs a 2D array to standard output
Outputs the number of rows and cols in the array
*/
void output_data(float** data, int rows, int cols) {
    printf("%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.3f ", data[i][j]);
        }
        printf("\n");
    }
}

// Frees dynamically allocated 2D array
void free_2d_array(float** array, int rows) {
    if (!array) return; // Avoid freeing NULL value
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
