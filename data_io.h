/*
Header file for data_io utilities.
This file declares a set of functions for working with 2D arrays of float data.
These utilities support reading and outputting data, as well as 
memory management for 2D arrays.
*/

#ifndef DATA_IO_H
#define DATA_IO_H

float** read_data(int* rows, int* cols);
void output_data(float** data, int rows, int cols);
void free_2d_array(float** array, int rows);

#endif
