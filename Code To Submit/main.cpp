/*---------------------------Title------------------------------
 * File main.cpp for ENGO 419 - Geomatics Networks
 * Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
 * Question 1 – Covariance propagation for directions and angles
 *
 * Dylan Conley, Titus Castillon, Nick Kennedy
 * Written September 26, 2023 for Lab 1
 *
 * This file is used to read a text file of direction observations and manipulate the observations to solve for
 * angles with an associated covariance-variance matrix
 *-------------------------------------------------------------*/


#include <iostream>
#include <iomanip>
#include "C:\Users\conle\OneDrive - University of Calgary\School\Winter 23\ENGO 363\eigen-3.4.0\eigen-3.4.0\Eigen\Eigen"
using namespace std;
using namespace Eigen;

//Used to import  data as txt files
#include "MatrixIO.h"
//Used to solve correlation matrices and create variance covariance matrices
#include "CovarianceMatrices.h"



void question1();

/**
 * Converts a number in DMS format to decimal degrees
 * @param deg The degrees of a direction (double to avoid typecasting issues)
 * @param minutes The minutes of a direction (double to avoid typecasting issues)
 * @param seconds The seconds of a number
 * @return The same number as double in decimal degrees
 */
double convDMSToDecDeg(double deg, double minutes, double seconds){
    cout << deg << " " << minutes << " " << seconds << endl;
    double decimalDegrees = deg + minutes/60 + seconds/3600;
    return decimalDegrees;
}

/**
 * Runs the main program
 * @return 0 if successful runtime
 */
int main() {
    question1();
    return 0;
}

/**
 * Imports the observation and solves for the unknowns with associated errors
 */
void question1() {

    //Imports the data into a 11x9 matrix
    MatrixXd question1obs = Read_Data("question1obs.txt",9);

    //Finds the mean of the seconds
    double amean = question1obs.col(2).mean();
    double bmean = question1obs.col(5).mean();
    double cmean = question1obs.col(8).mean();

    //Finds the residual of each observation using the formula: observation mean - observation
    MatrixXd residualsMatrix1(11, 3);
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j <9; j++) {
            if(j==2){
                residualsMatrix1(i,0) = amean - question1obs(i,j);
            }
            if(j==5){
                residualsMatrix1(i,1) = bmean - question1obs(i,j);
            }
            if(j==8){
                residualsMatrix1(i,2) = cmean - question1obs(i,j);
            }
        }
    }

    //Uses a matrix of the residuals to solve for the covariance matrix
    MatrixXd obsCovariance = covarianceMatrix(residualsMatrix1);
    //Converts the covariance matrix to a correlation matrix
    MatrixXd obsCorrelation = correlationMatrix(obsCovariance);


    cout << "Obs Correlation" << endl;
    cout << obsCorrelation << endl;

    //Creates a Jacobian Matrix based on the equations set out in the methodology
    MatrixXd J(3,3);
    J(0,0) = -1; J(0,1) = 1; J(0,2) = 0;
    J(1,0) = 0; J(1,1) = -1; J(1,2) = 1;
    J(2,0) = -1; J(2,1) = 0; J(2,2) = 1;


    //Converts the observations from DMS to degrees decimal and stores in a vector in the same order as defined by the Jacobian
    MatrixXd obs(3,1);
    obs(0,0) = convDMSToDecDeg(question1obs(0,0),question1obs(0,1),amean);
    obs(1,0) = convDMSToDecDeg(question1obs(0,3),question1obs(0,4),bmean);
    obs(2,0) = convDMSToDecDeg(question1obs(0,6),question1obs(0,7),cmean);

    //Creates a second covariance matrix, but this time as a diagonal matrix with independent observations
    MatrixXd covarianceWithZeros = MatrixXd::Zero(3,3);
    covarianceWithZeros(0,0) = obsCovariance(0,0);
    covarianceWithZeros(1,1) = obsCovariance(1,1);
    covarianceWithZeros(2,2) = obsCovariance(2,2);

    //Solves for the unknowns
    MatrixXd unknowns(3,1);
    unknowns(0,0) = obs(1,0) - obs(0,0);
    unknowns(1,0)= obs(2,0) - obs(1,0);
    unknowns(2,0)= obs(2,0)-obs(0,0);

    //Propogates error by C unk = J * C obs * Jt for both independent and dependent observations
    MatrixXd varianceCovarianceUnknownsCorrelated = J*obsCovariance*J.transpose();
    MatrixXd varianceCovarianceUnknownsUncorrelated = J*covarianceWithZeros*J.transpose();

    //Finds correlation matrices for both covariance matrices
    MatrixXd correlationUnknownsUncorrelated = correlationMatrix(varianceCovarianceUnknownsUncorrelated);
    MatrixXd correlationUnknownsCorrelated = correlationMatrix(varianceCovarianceUnknownsCorrelated);

    cout << "Observations" << endl;
    cout << obs << endl;

    cout << "Unknowns" << endl;
    cout << setprecision(10) << unknowns << endl << endl;

    cout << "varianceCovarianceUnknownsCorrelated" << endl;
    cout << varianceCovarianceUnknownsCorrelated << endl;

    cout << "correlationUnknownsCorrelated" << endl;
    cout << correlationUnknownsCorrelated << endl;


    cout << "varianceCovarianceUnknownsUncorrelated" << endl;
    cout << varianceCovarianceUnknownsUncorrelated << endl;

    cout << "correlationUnknownsUncorrelated" << endl;
    cout << correlationUnknownsUncorrelated << endl;

    return;
}
