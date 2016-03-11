#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <iostream>

int threadsNum;

using std::vector;
using std::cout;
using std::cin;

class Matrix {
    public:
        vector<vector<int> > elements;
        int matrixSize;

        Matrix(int size, bool fillByRandom);
        Matrix multiply(Matrix matrix);
        Matrix transport();
        void showMatrix();
};

Matrix::Matrix(int size, bool fillByRandom) {
    vector<vector<int> > newElements(size);
   
    for (int i = 0; i < size; i++)
    newElements[i].resize(size); 

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (fillByRandom)
                newElements[i][j] = rand() % 100;
            else
                newElements[i][j] = 0;
        }
    }

    elements = newElements;
    matrixSize = size;
}

Matrix Matrix::multiply(Matrix matrix) {
    if (matrixSize != matrix.matrixSize) {
        cout << "Error. Matrices should be same size.";
        exit(-1);
    }

    Matrix result(matrixSize, false);

    #pragma omp parallel num_threads(threadsNum) 
    {
        #pragma omp for
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                for (int k = 0; k < matrixSize; k++) {
                    result.elements[i][j] += elements[i][k] * matrix.elements[k][j];
                }
            }
        }
    }

    return result;
}

Matrix Matrix::transport() {
    Matrix result(matrixSize, false);

    #pragma omp parallel num_threads(threadsNum)
    {
        #pragma omp for
        for (int i = 0; i < matrixSize; i++)
            for (int j = 0; j < matrixSize; j++)
                result.elements[i][j] = elements[j][i];
    }
    return result;
}

void Matrix::showMatrix() {
    for(int i = 0; i < matrixSize; i++) {
        for(int j = 0; j < matrixSize; j++) {
            cout << elements[i][j] << " ";
        }
 
        cout << "\n";
    }
    
    cout << "\n";
}

int main (int argc, char *argv[]) {
    cout << "Enter threads num: ";
    cin >> threadsNum;
/*
    Matrix matrix(1000, true);
    Matrix secondMatrix(1000, true);
  
    double time = omp_get_wtime();  
    Matrix result = matrix.multiply(secondMatrix);
    time = omp_get_wtime() - time;
    cout << "\ntime: " << time;
*/
//    result.showMatrix();
    Matrix matrix(10000, true);
//    matrix.showMatrix();
    double time = omp_get_wtime();
    matrix.transport();
    cout << "\ntime: " << omp_get_wtime() - time;
}
 
