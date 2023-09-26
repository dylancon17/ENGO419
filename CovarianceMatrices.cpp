/*---------------------------Title------------------------------
 * File CovarianceMatrices.cpp for ENGO 363 - Estimation and Statistical Testing
 * Lab 4 - Implicit Least Squares Adjustment
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



#include "CovarianceMatrices.h"
#include <cmath>
#include <string>
#include "MatrixIO.h"

MatrixXd covarianceIndependentMatrix(MatrixXd sd){
    //Creates a covariance matrix given standard deviations
    //The covariance between measurements is not known so creates a diagonal matrix
    int size = sd.rows();
    MatrixXd covariance = MatrixXd::Zero(size,size);
    for (int i=0;i<size;i++){
        //Squares to get variance
        covariance(i,i) = sd(i,0) * sd(i,0);
    }
    //Outputs Matrix
    cout << "--------------------" << endl;
    cout << "Covariance Matrix Observations" << endl;
    cout << covariance << endl << endl;
    return covariance;
}


MatrixXd covarianceMatrix(MatrixXd residualMatrix){
    //Creates a covariance matrix given residuals

    //Finds sizes of residual matrix
    int numberDataSets = residualMatrix.cols();
    int numberDataPoints = residualMatrix.rows();

    //Creates a covariance matrix of the correct size
    MatrixXd covariance(numberDataSets, numberDataSets);

    //For each row in covariance
    for (int i = 0; i < numberDataSets; i++) {
        //For each column in covariance
        for (int j = 0; j < numberDataSets; j++) {
            double sum = 0;
            //For each residual value
            for (int m = 0; m < numberDataPoints; m++) {
                //Finds the sum of the residuals multiplied together
                sum += residualMatrix(m, i) * residualMatrix(m, j);
            }
            //Divides by n - 1
            double cov = sum / (numberDataPoints - 1);
            covariance(i, j) = cov;
        }
    }
    //Outputs Matrix
    cout << "--------------------" << endl;
    cout << "Covariance Matrix" << endl;
    cout << covariance << endl << endl;
    return covariance;
}

MatrixXd covarianceResiduals(double a, MatrixXd P, MatrixXd B){
    //Finds a covariance matrix of the residuals
    //Uses the formula C = a * P^-1 * B^T * M^-1 * B * P^-1 where M = B * P^-1 * B^T
    MatrixXd M = B * P.inverse() * B.transpose();
    MatrixXd covariance = a * P.inverse() * B.transpose() * M.inverse() * B * P.inverse();

    //Outputs Matrix
    cout << "--------------------" << endl;
    cout << "Covariance Matrix Residuals" << endl;
    cout << covariance << endl << endl;
    return covariance;
}

MatrixXd covarianceUnknowns(MatrixXd J,MatrixXd C_l_corr){
    //Finds a covariance matrix of the unknowns
    //Uses the formula C = J * C of corrected observations * J^T

    MatrixXd covariance = J * C_l_corr * J.transpose();

    //Outputs Matrix
    cout << "--------------------" << endl;
    cout << "Covariance Matrix Unknowns" << endl;
    cout << covariance << endl << endl;
    return covariance;
}


MatrixXd correlationMatrix(MatrixXd covarianceMatrix){
    //Finds a correlation matrix from a covariance matrix

    int size = covarianceMatrix.rows();

    MatrixXd correlation(size, size);

    //For each row in the correlation matrix
    for (int i = 0; i < size; i++) {
        //Fore each column in the correlation matrix
        for (int j = 0; j < size; j++) {
            //Finds correlation from covariance
            correlation(i, j) = covarianceMatrix(i, j) / (sqrt(covarianceMatrix(i, i)) * sqrt(covarianceMatrix(j, j)));
        }
    }

    return correlation;
}

MatrixXd weightMatrix(MatrixXd covariance, double a){
    //Finds a weight matrix from the covariance
    //Uses the formula C = a * P^-1 * B^T * M^-1 * B * P^-1 where M = B * P^-1 * B^T

    int size = covariance.rows();
    MatrixXd P = MatrixXd::Zero(size,size);
    for (int i=0;i<size;i++){
        P(i,i) = a / covariance(i,i);
    }

    //Outputs Matrix
    cout << "--------------------" << endl;
    cout << "Weight Matrix Observations" << endl;
    cout << P << endl << endl;
    return P;
}

MatrixXd SDFromCovariance(MatrixXd C){
    //Finds standard deviation vector from variance covariance matrix
    //Takes the sqrt of each valuue on the diagonal
    int size = C.cols();
    MatrixXd sd(size, 1);
    for (int i=0;i<size;i++){
        sd(i,0) = sqrt(C(i,i));
    }

    return sd;
}
