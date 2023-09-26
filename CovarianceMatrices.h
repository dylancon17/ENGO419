/*---------------------------Title------------------------------
 * File CovarianceMatrices.h for ENGO 363 - Estimation and Statistical Testing
 * Lab 5 - Implicit Least Squares Adjustment
 *
 * Dylan Conley
 * 30140483
 * Written February 9, 2023 for Lab 2
 * Updated March 5, 2023 for Lab 3
 * Used April 2, 2023 for Lab 5, no updates needed
 *
 * This file is used to determine and convert between covariance, correlation, weight and standard deviations using
 * a variety of different techniques
 *-------------------------------------------------------------*/

#ifndef LAB_2_MULTIVARIATECALCULATIONS_H
#define LAB_2_MULTIVARIATECALCULATIONS_H

#include <iostream>
#include "../../Winter 23/ENGO 363/eigen-3.4.0/eigen-3.4.0/Eigen/Eigen"
using namespace std;
using namespace Eigen;

MatrixXd covarianceIndependentMatrix(MatrixXd sd);
MatrixXd covarianceMatrix(MatrixXd residualMatrix);
MatrixXd covarianceResiduals(double a, MatrixXd P, MatrixXd B);
MatrixXd covarianceUnknowns(MatrixXd J,MatrixXd C_l_corr);

MatrixXd correlationMatrix(MatrixXd);

MatrixXd weightMatrix(MatrixXd covariance, double a);

MatrixXd SDFromCovariance(MatrixXd C);







#endif //LAB_2_MULTIVARIATECALCULATIONS_H
