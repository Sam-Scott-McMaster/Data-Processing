/*
Header file for data processing utilities.
This file declares a set of functions for working with 2D arrays of float data.
These utilities support reading, cleaning, and outputting data, as well as 
memory management for 2D arrays.
*/

#ifndef DATA_PROCESSING_H
#define DATA_PROCESSING_H

float** read_data(int* rows, int* cols);
float** clean_delete(float** data, int rows, int cols, int* new_rows);
void clean_impute(float** data, int rows, int cols);
void output_data(float** data, int rows, int cols);
void free_2d_array(float** array, int rows);

#endif
