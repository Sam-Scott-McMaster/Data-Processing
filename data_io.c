#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_io.h"

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
