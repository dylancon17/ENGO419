/*---------------------------Title------------------------------
 * File MatrixIO.h for ENGO 363 - Estimation and Statistical Testing
 * Lab 5 - Implicit Least Squares Adjustment
 *
 * Dylan Conley
 * 30140483
 * Written January 29, 2023 for Lab 1
 * Updated February 9, 2023 for Lab 2
 * Used April 2, 2023 for Lab 5
 *
 * Program used to read data in a text file
 * This file is used for standard operations such as writing to text files, reading from text files and displaying matrices
 *-------------------------------------------------------------*/

#ifndef LAB1_STANDARDMATRIXOPERATIONS_H
#define LAB1_STANDARDMATRIXOPERATIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "../../Winter 23/ENGO 363/eigen-3.4.0/eigen-3.4.0/Eigen/Eigen"
using namespace std;
using namespace Eigen;

/*---------------------------Display Matrices----------------*/
void Describe_Matrix(MatrixXd& matrix, string matrix_name);
void Describe_Unknown_Parameters(MatrixXd& matrix);

/*---------------------------Read/Write Files----------------*/
MatrixXd Read_Data(const string textfile, int num_cols);
void OutputMatrix(MatrixXd& output_matrix, const string file_name, const int precision, const int width);

#endif //LAB2_STANDARDMATRIXOPERATIONS_H

