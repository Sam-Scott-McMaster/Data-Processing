/*
Header file for data_io utilities.
This file declares a set of functions for working with 2D arrays of float data.
These utilities support cleaning data
*/

#ifndef DATA_CLEANING_H
#define DATA_CLEANING_H

float** clean_delete(float** data, int rows, int cols, int* new_rows);
void clean_impute(float** data, int rows, int cols);

#endif