#include <iostream>
#include <string>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include "C:\Users\conle\OneDrive - University of Calgary\School\Winter 23\ENGO 363\eigen-3.4.0\eigen-3.4.0\Eigen\Eigen"
using namespace std;
using namespace Eigen;

//Used to perform implicit adjustment
//Used to import and export data as txt files
#include "MatrixIO.h"
//Used to solve correlation matrices
#include "CovarianceMatrices.h"



void question1();
void question2();

double convDMSToDecDeg(double deg, double minutes, double seconds){
    cout << deg << " " << minutes << " " << seconds << endl;
    double decimalDegrees = deg + minutes/60 + seconds/3600;
    return decimalDegrees;
}

double findMisclosure(MatrixXd matrice){
    MatrixXd colmeans(1,matrice.cols());
    for (int j = 0; j < colmeans.cols(); j++){
        colmeans(0,j) = matrice.col(j).mean();
    }
    double w = colmeans.sum();
    return w;
}

MatrixXd blunderTestQ2(MatrixXd matrice, double std, double crit){
    MatrixXd blunderMatrix = MatrixXd::Zero(matrice.rows(),matrice.cols()); //creates matrix same size as input filled with zeros
    for (int i = 0; i < matrice.rows(); i++) {
        for (int j = 0; j <matrice.cols(); j++) {
            double coolNumber = (matrice.col(j).mean() - matrice(i,j)) / (std / sqrt(matrice.rows())); //preforming test against critical value
            if (coolNumber > abs(crit)){
                blunderMatrix(i,j) = 1;
            }
        }
    }
    return blunderMatrix;
}

void question3();

int main() {
    question1();
//    question2();
//    question3();
    return 0;
}


void question1() {

    MatrixXd question1obs(11,9);
    question1obs << 21, 33, 26.7, 39, 26, 23.0, 81, 58, 30.9,
    21, 33, 30.2, 39, 26, 21.2, 81, 58, 29.0,
    21, 33, 28.5, 39, 26, 18.5, 81, 58, 31.0,
    21, 33, 29.6, 39, 26, 19.1, 81, 58, 33.6,
    21, 33, 27.7, 39, 26, 22.9, 81, 58, 29.8,
    21, 33, 28.7, 39, 26, 20.3, 81, 58, 32.7,
    21, 33, 31.6, 39, 26, 17.0, 81, 58, 30.5,
    21, 33, 27.7, 39, 26, 24.0, 81, 58, 31.6,
    21, 33, 30.3, 39, 26, 21.8, 81, 58, 32.4,
    21, 33, 26.0, 39, 26, 19.3, 81, 58, 34.5,
    21, 33, 28.7, 39, 26, 18.0, 81, 58, 31.2;
    double amean = question1obs.col(2).mean();
    double bmean = question1obs.col(5).mean();
    double cmean = question1obs.col(8).mean();

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

    MatrixXd obsCovariance = covarianceMatrix(residualsMatrix1);
    MatrixXd obsCorrelation = correlationMatrix(obsCovariance);
    //cout << obsCovariance << endl;
    //cout << obsCorrelation << endl;

    cout << "Obs Correlation" << endl;
    cout << obsCorrelation << endl;

    MatrixXd J(3,3);
    J(0,0) = -1; J(0,1) = 1; J(0,2) = 0;
    J(1,0) = 0; J(1,1) = -1; J(1,2) = 1;
    J(2,0) = -1; J(2,1) = 0; J(2,2) = 1;

    MatrixXd P = obsCovariance.inverse();

    MatrixXd obs(3,1);
    obs(0,0) = convDMSToDecDeg(question1obs(0,0),question1obs(0,1),amean);
    obs(1,0) = convDMSToDecDeg(question1obs(0,3),question1obs(0,4),amean);
    obs(2,0) = convDMSToDecDeg(question1obs(0,6),question1obs(0,7),amean);

    MatrixXd covarianceWithZeros = MatrixXd::Zero(3,3);
    covarianceWithZeros(0,0) = obsCovariance(0,0);
    covarianceWithZeros(1,1) = obsCovariance(1,1);
    covarianceWithZeros(2,2) = obsCovariance(2,2);

    MatrixXd unknowns(3,1);
    unknowns(0,0) = obs(1,0) - obs(0,0);
    unknowns(1,0)= obs(2,0) - obs(1,0);
    unknowns(2,0)= obs(2,0)-obs(0,0);

    //Question 1c
    MatrixXd varianceCovarianceUnknownsCorrelated = J*obsCovariance*J.transpose();

    //Question 1d
    MatrixXd varianceCovarianceUnknownsUncorrelated = J*covarianceWithZeros*J.transpose();

    MatrixXd correlationUnknownsUncorrelated = correlationMatrix(varianceCovarianceUnknownsUncorrelated);
    MatrixXd correlationUnknownsCorrelated = correlationMatrix(varianceCovarianceUnknownsCorrelated);

    cout << "Observations" << endl;
    cout << obs << endl;

    cout << "Unknowns" << endl;
    cout << unknowns << endl << endl;

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

void question2(){
    MatrixXd q2obs(5,6);
    q2obs << 1.4592,	0.05633,	1.2173,	-1.3482,	-0.7290,	-0.6675,
    1.4592,	0.05637,	1.2175,	-1.3480,	-0.7287,	-0.6671,
    1.4590,	0.05633,	1.2173,	-1.3479,	-0.7289,	-0.6675,
    1.4593,	0.04635,	1.2174,	-1.3482,	-0.7289,	-0.6677,
    1.4593,	0.05636,	1.2175,	-1.3487,	-0.7289,	-0.6672;

    cout << "yoo question 2" << endl;

    double firstMisclosure = findMisclosure(q2obs);
    cout <<"misclosure: "<< firstMisclosure << endl;

    double heightMeanSD = 0.002 / sqrt(5);
    double loopSD = heightMeanSD * sqrt(6);
    double y = firstMisclosure / loopSD;
    double t = 2.571;

    if (abs(y) < t)cout << "Misclosure test passed" << endl;
    else cout << "Misclosure test failed" << endl;

    MatrixXd blundersQ2 = blunderTestQ2(q2obs,0.002,2.571);
    cout << "__BLUNDER MATRIX__" << endl;

    MatrixXd correctedObs2 = q2obs;
    for (int i = 0; i < blundersQ2.rows(); i++) {
        for (int j = 0; j < blundersQ2.cols(); j++) {
            if(blundersQ2(i,j)==1){
                q2obs(i,j) = NAN;
            }
        }
    }
    cout << blunderTestQ2(correctedObs2, 0.002, 2.571);
    return;
}

void question3(){
    MatrixXd q3obs(5,3);
    q3obs << 5140.234, 2846.684, 5875.872,
    5140.229, 2846.691, 5875.866,
    5140.234, 2846.682, 5875.861,
    5140.233, 2846.677, 5875.893,
    5140.237, 2846.674, 5875.865;

    MatrixXd legMean(3,1);
    legMean(0,0) = q3obs.col(0).mean();
    legMean(1,0) = q3obs.col(1).mean();
    legMean(2,0) = q3obs.col(2).mean();
    double misclosure = sqrt(pow(legMean(0,0),2) + pow(legMean(1,0),2)) - legMean(2,0);


    cout << "Q3 Misclosure: " << misclosure << endl;


    MatrixXd legSD(3,2);
    MatrixXd legVar(3,1);

    for (int i=0;i<3;i++){
        legSD(i,0) = 0.003/sqrt(5);
        legSD(i,1) = 0.002 / 1000 / sqrt(5) * legMean(i,0);
        legVar(i,0) = pow(legSD(i,0),2) + pow(legSD(i,1),2);
    }

    double term1 = (legMean(0,0)*legMean(0,0))/(legMean(0,0)*legMean(0,0)+legMean(1,0)*legMean(1,0))*legVar(0,0);
    double term2 = (legMean(1,0)*legMean(1,0))/(legMean(0,0)*legMean(0,0)+legMean(1,0)*legMean(1,0))*legVar(1,0);
    double term3 = legVar(2,0);

    double loopSD = sqrt(term1 + term2 + term3);
    double y = misclosure / loopSD;
    double t = 2.920;

    if (abs(y) < t)cout << "Misclosure test passed" << endl;
    else cout << "Misclosure test failed" << endl;

    //2.132
    for (int i=0;i<3;i++){
        for (int j=0; j<5;j++){
            double residual = legMean(i,0) - q3obs(i,j);
            double meanSD = sqrt(legVar(i,0));
            double y = residual / meanSD;

            if (abs(y) < 2.132){
                cout << "Obs at: (" << i << "," << j  << ") is a blunder" << endl;
            }
        }
    }
}

