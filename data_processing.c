#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data_processing.h"

float** read_data(int* rows, int* cols) {
    scanf("%d %d", rows, cols);
    float** data = malloc(*rows * sizeof(float*));
    for (int i = 0; i < *rows; i++) {
        data[i] = malloc(*cols * sizeof(float));
        for (int j = 0; j < *cols; j++) {
            scanf("%f", &data[i][j]);
        }
    }
    return data;
}

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
            new_data = realloc(new_data, (*new_rows + 1) * sizeof(float*));
            new_data[*new_rows] = malloc(cols * sizeof(float));
            for (int j = 0; j < cols; j++) {
                new_data[*new_rows][j] = data[i][j];
            }
            (*new_rows)++;
        }
    }
    return new_data;
}

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

        for (int i = 0; i < rows; i++) {
            if (isnan(data[i][j])) {
                data[i][j] = avg;
            }
        }
    }
}

void output_data(float** data, int rows, int cols) {
    printf("%d %d\n", rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.3f ", data[i][j]);
        }
        printf("\n");
    }
}

void free_2d_array(float** array, int rows) {
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    free(array);
}
