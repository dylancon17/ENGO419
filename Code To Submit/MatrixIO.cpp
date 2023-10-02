/*---------------------------Title------------------------------
 * File MatrixIO.cpp for ENGO 419 - Geomatics Networks
 * Lab 1 - Precision analysis of observations, data pre-processing and pre-adjustment screening
 * Question 1 – Covariance propagation for directions and angles
 *
 * Dylan Conley, Titus Castillon, Nick Kennedy
 * Orginally designed for ENGO 363
 * Updated September 26, 2023 for Lab 1
 *
 * This file is used to read/write text files and to display matrices in the Eigen library
 *-------------------------------------------------------------*/
#include "MatrixIO.h"

/*---------------------------Display Matrices----------------*/

//Not used in this lab
void Describe_Matrix(MatrixXd& matrix, string matrix_name){
    // This function is used to display matrices in the command line to allow for easier debugging of matrices
    /* Formatted as:
        -----------------------------------
        matrix_name:
        Rows:           rows
        Columns:        columns
        -----------------------------------
    */
    cout << endl << "-----------------------------------" << endl;
    cout << matrix_name << endl;
    cout << "\tRows:\t\t" << matrix.rows() << endl;
    cout << "\tColumns:\t" << matrix.cols() << endl;
    cout << "-----------------------------------" << endl;
}

/*---------------------------Read/Write Files---------------*/

/**
 * Imports a text file in csv comma delimeted format and converts it to a matrix
 * @param textfile the file, include ".txt" at the end: ex. "question3obs.txt"
 * @param num_cols the number of columns in each row of data
 * @return a matrix of size a x num_cols, where a is dynamically allocated during runtime based on the text file
 */
MatrixXd Read_Data(const string textfile, int num_cols){
    // Imports the data from textfile and returns a matrix
    // Dynamically sized, it will read the number of rows in the text file in order to create the correct matrix size
    ifstream inputfile;
    inputfile.open(textfile);

    if (inputfile.is_open()){
        //Determines the number of lines in the data value.
        //This is based on the assumption that the number of rows can vary to avoid hardcoding.
        int line = 0;
        string temp;

        //Reads through and counts each line
        while (getline(inputfile, temp)){
            line++;
        }
        inputfile.close();

        //Creates Input Matrix of Determined Size
        MatrixXd Input_Matrix(line,num_cols);

        inputfile.open(textfile);
        string input;

        //Adds data to the matrix
        //Data added as doubles
        for (int i=0; i < line; i++){
            //If it's not the last data point in the line looks for a comma delimiter
            cout << "Start of Line: ";
            for (int j=0; j < (num_cols - 1); j++){
                getline(inputfile, input, ',');
                Input_Matrix(i,j) = stod(input);
            }
            //If it's the last data point in the line looks for an end of line delimiter
            getline(inputfile, input);
            Input_Matrix(i,num_cols-1) = stof(input);
        }
        return Input_Matrix;
    }
    else{
        cout << textfile << " Failed to Open" << endl;
        exit(1);
    }
}

//Not used in this lab
void OutputMatrix(MatrixXd& output_matrix, const string file_name, const int precision, const int width){
    //Outputs a matrix to file_name with a set precision and width
    ofstream outputfile;
    outputfile.open(file_name);

    int rows = output_matrix.rows();
    int cols = output_matrix.cols();


    if (outputfile.is_open()){
        cout << endl << file_name << " Opened" << endl;
        //Iterates through each row of a matrix, for each row outputs each column and then outputs a new line
        for (int i=0; i < rows;i++){
            for (int j=0; j < cols;j++){
                outputfile << setprecision( precision ) << setw( width ) << output_matrix(i,j) << " ";
            }
            outputfile << endl;
        }
        cout << file_name << " Filled With Data" << endl;
    }
    else{
        cout << file_name << " Failed to Open" << endl;
        exit(1);
    }

}