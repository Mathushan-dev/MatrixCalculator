# Matrix Calculator
My first project in the C programming language - Matrix calculator, as part of a UCL project.

This application is a matrix calculator that can perform the standard matrix operations to matrices with a maximum row and column size of 1000 unless a lower maximum level is shown below:

1. Add
2. Subtract
3. Multiply
4. Scalar multiply
5. Power
6. Identity
7. Determinant (max 3x3) - (TODO Make this implemetation more efficient by studying the maths behind it XD)
8. Inverse (max 3x3) - (TODO Make this implemetation more efficient by studying the maths behind it XD)
9. Transpose

It can then save these resulting matrices to a file data.txt and it can use the matrices in the file for calculations too.

The application is quite easy to use, however the following must be noted:

The determinant and inverse can only be calculated for matrices with a maximum of 3 rows and columns, if a matrix with larger dimensions is entered, the program will notify the user and offer a menu to proceed.
The user can only load matrices from a file after the file has been created, if a user tries to load a matrix from the file without saving a matrix to it, then the program will notify the user and offer a menu to proceed.
The user MUST NOT alter anything in the file, the file will only be handled by the program.
The user can use the application for as many calculations as required and the file will constantly be updated without having to quit the program.

Terminal commands to run:

gcc Main.c Matrix.c File.c
./a.out
