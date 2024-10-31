/*
# Name: Samantha Adorno
# KUID: 3147214
# LAB Assignment: 07
# Description: Complete operations with matrices using classes and operator overloading
*/

#include <iostream>
#include <fstream>

using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    // constructor
    Matrix(int size = 0) : matrix_size(size) {
        if (matrix_size > 0) {
            matrix_data = new double*[matrix_size];
            for (int i = 0; i < matrix_size; ++i) {
                matrix_data[i] = new double[matrix_size]();
            }
        } else {
            matrix_data = nullptr;
        }
    }

    // destructor
    ~Matrix() {
        if (matrix_data) {
            for (int i = 0; i < matrix_size; ++i) {
                delete[] matrix_data[i];
            }
            delete[] matrix_data;
        }
    }

    // method to set matrix size and allocate memory
    void set_size(int size) {
        if (matrix_data) {
            for (int i = 0; i < matrix_size; ++i) {
                delete[] matrix_data[i];
            }
            delete[] matrix_data;
        }

        matrix_size = size;
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size]();
        }
    }
};

// read matrix from file
void read_matrix_from_file(const char* file_name, Matrix& matrix_1, Matrix& matrix_2) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int size;
    file >> size;
    matrix_1.set_size(size);
    matrix_2.set_size(size);

    // read matrix 1
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            file >> matrix_1.matrix_data[i][j];
        }
    }

    // read matrix 2
    for (int i = 0; i < matrix_2.matrix_size; ++i) {
        for (int j = 0; j < matrix_2.matrix_size; ++j) {
            file >> matrix_2.matrix_data[i][j];
        }
    }

    file.close();
}

// print a matrix
void print_matrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix_size; ++i) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
}

// print both matrices
void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    cout << "Matrix 1:\n";
    print_matrix(matrix_1);
    cout << "Matrix 2:\n";
    print_matrix(matrix_2);
}

// add matrices
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

// multiply matrices
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2) {
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            result.matrix_data[i][j] = 0;
            for (int k = 0; k < matrix_1.matrix_size; ++k) {
                result.matrix_data[i][j] += matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j];
            }
        }
    }
    return result;
}

// get diagonal sum
void get_diagonal_sum(const Matrix& matrix) {
    double main_diagonal_sum = 0, secondary_diagonal_sum = 0;
    for (int i = 0; i < matrix.matrix_size; ++i) {
        main_diagonal_sum += matrix.matrix_data[i][i];
        secondary_diagonal_sum += matrix.matrix_data[i][matrix.matrix_size - i - 1];
    }
    cout << "Main diagonal sum: " << main_diagonal_sum << "\n";
    cout << "Secondary diagonal sum: " << secondary_diagonal_sum << "\n";
}

// swap matrix rows
void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    if (row1 >= 0 && row2 >= 0 && row1 < matrix.matrix_size && row2 < matrix.matrix_size) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            swap(matrix.matrix_data[row1][j], matrix.matrix_data[row2][j]);
        }
    } else {
        cerr << "Invalid row indices!\n";
    }
}

int main(int argc, char* argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix_input.txt", matrix_1, matrix_2);

    print_matrix(matrix_1, matrix_2);

    cout << "\nAdd matrices result:\n";
    Matrix add_result = matrix_1 + matrix_2;
    print_matrix(add_result);

    cout << "\nMultiply matrices result:\n";
    Matrix multiply_result = matrix_1 * matrix_2;
    print_matrix(multiply_result);

    cout << "\nGet matrix diagonal sum:\n";
    get_diagonal_sum(matrix_1);

    cout << "\nSwap matrix rows:\n";
    swap_matrix_row(matrix_1, 0, 1);
    print_matrix(matrix_1);

    return 0;
}
