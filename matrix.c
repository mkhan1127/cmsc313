#include <stdio.h>
#include <stdlib.h>

typedef struct {        // creates a structure for the matrix
    int rows;
    int cols;
    double** data;
} Matrix;


Matrix* createMatrix(int rows, int cols) {      // creates the matrix of size rows x cols
    Matrix* m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        m->data[i] = malloc(cols * sizeof(double));
        for (int j = 0; j < cols; j++) {
            m->data[i][j] = 0;
        }
    }
    return m;
}


void freeMatrix (Matrix* m) {       // function to free allocated memory
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}


void printMatrix(const Matrix* m) {     // prints out the matrix
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("%.2f ", m->data[i][j]);
        }
        printf("\n");
    }
}


Matrix* addMatrix(const Matrix* a, const Matrix* b) {       // adds 2 matrices together
    if (a->rows != b->rows || a->cols != b->cols) {      // size validation
        return NULL;
    }
    Matrix* result = createMatrix(a->rows, a->cols);
    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < a->cols; ++j) {
            result->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return result;
}


Matrix* scalarMultiply(const Matrix* m, double scalar) {        // multiplies a matrix by a scalar
    Matrix* result = createMatrix(m->rows, m->cols);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            result->data[i][j] = scalar * m->data[i][j];
        }
    }
    return result;
}


Matrix* multiplyMatrix(const Matrix* a, const Matrix* b) {      // multiplies 2 matrices
    if (a->cols != b->rows) {       // size validation
        return NULL;
    }

    Matrix* result = createMatrix(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            result->data[i][j] = 0.0;
            for (int k = 0; k < a->cols; k++) {
                result->data[i][j] += a->data[i][k] * b->data[k][j];
            }
        }
    }
    return result;
}


Matrix* transposeMatrix(const Matrix* m) {      // transposes the matrix
    Matrix* result = createMatrix(m->cols, m->rows);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            result->data[j][i] = m->data[i][j];
        }
    }
    return result;
}


int main() {
    Matrix* A = createMatrix(2, 2);
    Matrix* B = createMatrix(2, 3);
    Matrix* C = createMatrix(2, 3);

    // A = [6 4; 8 3]
    A->data[0][0] = 6; A->data[0][1] = 4;
    A->data[1][0] = 8; A->data[1][1] = 3;

    // B = [1 2 3; 4 5 6]
    B->data[0][0] = 1; B->data[0][1] = 2; B->data[0][2] = 3;
    B->data[1][0] = 4; B->data[1][1] = 5; B->data[1][2] = 6;

    // C = [2 4 6; 1 3 5]
    C->data[0][0] = 2; C->data[0][1] = 4; C->data[0][2] = 6;
    C->data[1][0] = 1; C->data[1][1] = 3; C->data[1][2] = 5;

    // D = A + (3 * B) * C^T
    Matrix* threeB = scalarMultiply(B, 3);
    Matrix* CT = transposeMatrix(C);
    Matrix* product = multiplyMatrix(threeB, CT);
    Matrix* D = addMatrix(A, product);

    printf("Matrix D = A + (3 * B) * C^T:\n");
    if (D != NULL)
        printMatrix(D);
    else
        printf("Error in matrix dimensions.\n");

    // Free memory
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);
    freeMatrix(threeB);
    freeMatrix(CT);
    freeMatrix(product);
    freeMatrix(D);

    return 0;
}

