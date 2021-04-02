//Max row and column sizes can be set, despite dynamic memory allocation
#define MAXROWSIZE 1000
#define MAXCOLUMNSIZE 1000

typedef struct Matrix{
    int rows;
    int columns;
    double **data;
}Matrix;

void calculationsMenu();
Matrix sourceMatrix();
void calculationsMenuOption(int option);
int validOption(int options);

Matrix loadMatrix();
Matrix initialiseMatrix();
Matrix constructMatrix(int rows, int columns);
void clean(Matrix matrix_1);
void showMatrix(Matrix initialising);
void displayMatrix(Matrix matrix_1);

Matrix add(Matrix matrix_1);
Matrix subtract(Matrix matrix_1);
Matrix computeMultiply(Matrix matrix_1, Matrix matrix_2);
Matrix multiply(Matrix matrix_1);
Matrix scalarMultiply(Matrix matrix_1);
Matrix power();
Matrix identity(int rows, int columns);
double determinant();
Matrix inverse();
Matrix transpose(Matrix matrix_1);