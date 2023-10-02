/*---------------------------Title------------------------------
 * File MatrixIO.h for ENGO 419 - Geomatics Networks
 * Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
 * Question 1 – Covariance propagation for directions and angles
 *
 * Dylan Conley, Titus Castillon, Nick Kennedy
 * Orginally designed for ENGO 363
 * Updated September 26, 2023 for Lab 1
 *
 * This file is used to read/write text files and to display matrices in the Eigen library
 *-------------------------------------------------------------*/

#ifndef LAB1_STANDARDMATRIXOPERATIONS_H
#define LAB1_STANDARDMATRIXOPERATIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "C:\Users\conle\OneDrive - University of Calgary\School\Winter 23\ENGO 363\eigen-3.4.0\eigen-3.4.0\Eigen\Eigen"
using namespace std;
using namespace Eigen;

/*---------------------------Display Matrices----------------*/
void Describe_Matrix(MatrixXd& matrix, string matrix_name);

/*---------------------------Read/Write Files----------------*/
//Used in this code
MatrixXd Read_Data(const string textfile, int num_cols);

void OutputMatrix(MatrixXd& output_matrix, const string file_name, const int precision, const int width);

#endif //LAB2_STANDARDMATRIXOPERATIONS_H

