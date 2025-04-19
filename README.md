Author: Muhammad Khan | UMBC | CMSC 313 Professor Kidd MW 14:30

Purpose of Software: This project implements a basic matrix library in both C and C++. 
                      The library supports standard matrix operations such as:
                      - Matrix Addition
                      - Matrix Multiplication
                      - Scalar Multiplication
                      - Transposition
                      
Files:
matrix.cpp - a program that utilizes OOP to create a Matrix Class that includes 
              member functions for matrix operations as well as a test case.
matrix.c - a C program that has all the functionality needed for the matrix operations
            as well as a test case.

Build Instructions:
To compile and run matrix.cpp
g++ -Wall -g matrix.cpp -o matrix_cpp
./matrix_cpp
To compile and run matrix.c
gcc -Wall -g matrix.c -o matrix_c

Testing Methodology:
Both programs implement the same equation to test for errors
    D = A + (3 * B) * C^T
    where
    A = [6 4] ; B = [1 2 3] ; C = [2 4 6]
        [8 3] ;     [4 5 6] ;     [1 3 5]
