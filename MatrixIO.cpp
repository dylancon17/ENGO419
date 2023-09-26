/*---------------------------Title------------------------------
 * File MatrixIO.cpp for ENGO 363 - Estimation and Statistical Testing
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
#include "MatrixIO.h"

/*---------------------------Display Matrices----------------*/

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


MatrixXd Read_Data(const string textfile, int num_cols){
    // A code partially provided by Sayeh Bayat and partially created by Dylan Conley (the author of this code)
    // was used as reference in the design on this function. Proper accreditation is provided in the lab report

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
            //If it's not the last data point in the line looks for a tab delimiter
            for (int j=0; j < (num_cols - 1); j++){
                getline(inputfile, input, '\t');
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