#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

class Matrix {
private: 
    int rows;
    int cols;
    vector<vector<double>> data;

public: 
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, vector<double>(cols, 0.0)) {}
    Matrix(const vector<vector<double>>& values): rows(values.size()), cols(values[0].size()), data(values) {}

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void set(int r, int c, double value) {      // function to set the value of a matrix at a specific spot
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value;
        }
    }

    double get(int r, int c) const {        // returns the value at row r, col c
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return data[r][c];
        }
        return 0.0;
    }

    Matrix add(const Matrix& other) const {     // adds two matrices
        if (rows != other.rows || cols != other.cols) {     // size validation
            throw invalid_argument("Matrix Addition Error: dimensions do not match");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix matrixMultiply(const Matrix& other) const {      // multiplies two matrices
        if (cols != other.rows){        // size validation
            throw invalid_argument("Matrix Multiplication Error: A.cols != B.rows");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix scalarMultiply(double scalar) const {        // multiplies a matrix by a scalar
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix transpose() const {      // transposes a matrix
        Matrix result(cols, rows);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[j][i] = data[i][j];
            }
        }
        return result;
    }

    void print() const {        // prints out the matrix
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // A = [6 4; 8 3]
    Matrix A(2, 2);
    A.set(0, 0, 6); A.set(0, 1, 4);
    A.set(1, 0, 8); A.set(1, 1, 3);

    // B = [1 2 3; 4 5 6]
    Matrix B(2, 3);
    B.set(0, 0, 1); B.set(0, 1, 2); B.set(0, 2, 3);
    B.set(1, 0, 4); B.set(1, 1, 5); B.set(1, 2, 6);

    // C = [2 4 6; 1 3 5]
    Matrix C(2, 3);
    C.set(0, 0, 2); C.set(0, 1, 4); C.set(0, 2, 6);
    C.set(1, 0, 1); C.set(1, 1, 3); C.set(1, 2, 5);

    // D = A + (3 * B) * C^T
    Matrix threeB = B.scalarMultiply(3);
    Matrix CT = C.transpose();
    Matrix product = threeB.matrixMultiply(CT);   
    Matrix D = A.add(product);
    cout << "Matrix D = A + (3 * B) * C^T:\n";
    D.print();

    return 0;
}
