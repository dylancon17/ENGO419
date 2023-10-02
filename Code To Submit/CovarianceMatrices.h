/*---------------------------Title------------------------------
 * File CovarianceMatrices.h for ENGO 419 - Geomatics Networks
 * Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
 * Question 1 – Covariance propagation for directions and angles
 *
 * Dylan Conley, Titus Castillon, Nick Kennedy
 * Originally designed for ENGO 363
 * Updated September 26, 2023 for Lab 1
 *
 * This file is used to determine and convert between covariance, correlation, weight and standard deviations using
 * a variety of different techniques
 *-------------------------------------------------------------*/

#ifndef LAB_2_MULTIVARIATECALCULATIONS_H
#define LAB_2_MULTIVARIATECALCULATIONS_H

#include <iostream>
#include "C:\Users\conle\OneDrive - University of Calgary\School\Winter 23\ENGO 363\eigen-3.4.0\eigen-3.4.0\Eigen\Eigen"
using namespace std;
using namespace Eigen;

MatrixXd covarianceIndependentMatrix(MatrixXd sd);

//Used in this lab analysis
MatrixXd covarianceMatrix(MatrixXd residualMatrix);

MatrixXd covarianceResiduals(double a, MatrixXd P, MatrixXd B);
MatrixXd covarianceUnknowns(MatrixXd J,MatrixXd C_l_corr);

//Used in this lab analysis
MatrixXd correlationMatrix(MatrixXd);

MatrixXd weightMatrix(MatrixXd covariance, double a);

MatrixXd SDFromCovariance(MatrixXd C);







#endif //LAB_2_MULTIVARIATECALCULATIONS_H
