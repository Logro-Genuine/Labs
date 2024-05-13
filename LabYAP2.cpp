#include <iostream>
#include <fstream>

using namespace std;

double** Matrix(int columns, int rows, ifstream& input) {
    double** matrix = new double* [columns];

    for (int j = 0; j < columns; j++) {
        matrix[j] = new double[rows];
        for (int i = 0; i < rows; i++) {
            input >> matrix[j][i];
        }
    }

    return matrix;
}

double** cumulSum(int columns, int rows, double** matrix) {
    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < (columns-1); i++) {
            matrix[i+1][j] += matrix[i][j];
        }
    }
    return matrix;
}

void matrixWrite(int columns, int rows, double** matrix, ofstream& output) {
    for (int j = 0; j < columns; j++) {
        for (int i = 0; i < rows; i++) {
            output << matrix[j][i] << ' ';
        }
    }
}

int main()
{
    ifstream input("input.txt");
    ofstream output("output.txt");
    int columns; input >> columns;
    int rows; input >> rows;

    double** matrix = cumulSum(columns, rows, Matrix(columns, rows, input));
    matrixWrite(columns, rows, matrix, output);

    for (int j = 0; j < columns; j++) {
        delete[] matrix[j];
    }
    delete[] matrix;
    input.close();
    output.close();
}
