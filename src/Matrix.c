#include <stdio.h>
#include <stdlib.h>
#include "File.h" //contains "Matrix.h"

//Matrix methods
Matrix loadMatrix(){
    return loadFile();
}

Matrix initialiseMatrix(Matrix matrix){
    printf("\nYou will now be asked to initialise the matrix.\n"
        "NOTE! You will be asked to enter the element again if the input is invalid.\n\n");
    for (int i=0;i<matrix.rows;i++){
        for (int j=0;j<matrix.columns;j++){
            printf("Enter the row %d, column %d element: ",i,j);
            while (scanf("%lf",(*(matrix.data+i)+j))!=1){
                fflush(stdin);
                printf("Real decimal point numbers only: ");
            }
            showMatrix(matrix);
        }
    }
    return matrix;
}

Matrix constructMatrix(int rows, int columns){
    Matrix matrix;
    matrix.rows=rows;
    matrix.columns=columns;
    matrix.data=malloc(rows*sizeof(double*));
    for(int i=0;i<rows;i++){
        *(matrix.data+i) = malloc(columns*sizeof(double));
    }
    for (int i=0;i<matrix.rows;i++){
        for (int j=0;j<matrix.columns;j++){
            (*(*(matrix.data+i)+j))=0;
        }
    }
    return matrix;
}

void clean(Matrix matrix_1){
    for(int i=0;i<matrix_1.rows;i++){
        free(*(matrix_1.data+i));
    }
    free(matrix_1.data);
}

void showMatrix(Matrix initialising){
    printf("\n\nUpdated Matrix:\n");
    for (int i=0;i<initialising.rows;i++){
        printf("(");
        for (int j=0;j<initialising.columns;j++){
            printf("%lf", (*(*(initialising.data+i)+j)));
            if (j!=initialising.columns-1){
                printf(", ");
            }
        }
        printf(")\n");
    }
    printf("\n");
}

void displayMatrix(Matrix result){
    printf("\n\nThe resulting matrix has elements:\n");
    for (int i=0;i<result.rows;i++){
        printf("(");
        for (int j=0;j<result.columns;j++){
            printf("%lf", (*(*(result.data+i)+j)));
            if (j!=result.columns-1){
                printf(", ");
            }
        }
        printf(")\n");
    }
    printf("\n");
    fileMenu(result);
}

//Calculation methods
Matrix add(Matrix matrix_1){
    Matrix matrix_2,result;
    printf("\nA matrix of the same dimensions has been created.\nPlease initialise the second matrix.\n");
    matrix_2=initialiseMatrix(constructMatrix(matrix_1.rows, matrix_1.columns));
    result=constructMatrix(matrix_1.rows, matrix_1.columns);
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            (*(*(result.data+i)+j))=(*(*(matrix_1.data+i)+j))+(*(*(matrix_2.data+i)+j));
        }
    }
    clean(matrix_1);
    clean(matrix_2);
    return result;
}
Matrix subtract(Matrix matrix_1){
    Matrix matrix_2,result;
    printf("\nA matrix of the same dimensions has been created.\nPlease initialise the second matrix.\n");
    matrix_2=initialiseMatrix(constructMatrix(matrix_1.rows, matrix_1.columns));
    result=constructMatrix(matrix_1.rows, matrix_1.columns);
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            (*(*(result.data+i)+j))=(*(*(matrix_1.data+i)+j))-(*(*(matrix_2.data+i)+j));
        }
    }
    clean(matrix_1);
    clean(matrix_2);
    return result;
}
Matrix computeMultiply(Matrix matrix_1, Matrix matrix_2){
    Matrix result;
    result=constructMatrix(matrix_1.rows, matrix_2.columns);
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            for(int k=0;k<matrix_1.columns;k++){
                (*(*(result.data+i)+j))+=((*(*(matrix_1.data+i)+k)) * (*(*(matrix_2.data+k)+j)));
            }
        }
    }
    return result;
}
Matrix multiply(Matrix matrix_1){
    Matrix matrix_2,result;
    printf("\nPlease now enter your second matrix.\n");
    do{
        matrix_2=sourceMatrix();
        if(!(matrix_1.columns==matrix_2.rows)){
            printf("\nIncorrect dimensions!\n"
            "Please enter your second matrix again.\n\n");
        }
    }while (!(matrix_1.columns==matrix_2.rows));
    result=computeMultiply(matrix_1,matrix_2);
    clean(matrix_1);
    clean(matrix_2);
    return result;
}
Matrix scalarMultiply(Matrix matrix_1){
    Matrix result=constructMatrix(matrix_1.rows, matrix_1.columns);
    printf("Enter the scalar multiple: ");
    double scalar;
    while(scanf("%lf",&scalar)!=1){
        fflush(stdin);
        printf("Real decimal point numbers only: ");
    }
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            (*(*(result.data+i)+j))=(*(*(matrix_1.data+i)+j))*scalar;
        }
    }
    clean(matrix_1);
    return result;
}
Matrix power(){
    Matrix matrix_1, result;
    do{
        matrix_1=sourceMatrix();
        if(!(matrix_1.columns==matrix_1.rows)){
            printf("Incorrect dimensions!\nRows and columns of the matrix MUST match.\n"
            "Please enter the matrix again.\n\n");
        }
    }while(!(matrix_1.columns==matrix_1.rows));
    printf("Enter the power: ");
    int power;
    while((scanf("%d",&power)!=1) && (power>=1)){
        fflush(stdin);
        printf("Natural numbers only: ");
    }
    result=identity(matrix_1.rows, matrix_1.columns);
    for (int p=1;p<=power;p++){
        result=computeMultiply(result, matrix_1);
    }
    clean(matrix_1);
    return result;
}
Matrix identity(int rows, int columns){
    Matrix result=constructMatrix(rows,columns);
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            if (i==j){
                (*(*(result.data+i)+j))=1;
            }
            else{
                (*(*(result.data+i)+j))=0;
            }
        }
    }
    return result;
}
double determinant(){
    Matrix matrix_1;
    double result;
    do{
        matrix_1=sourceMatrix();
        if(!(matrix_1.columns==matrix_1.rows)){
            printf("Incorrect dimensions!\nRows and columns of the matrix MUST match.\n"
            "Please enter the matrix again.\n\n");
        }
        if(matrix_1.rows>3){
            printf("Incorrect dimensions!\nRows and columns of the matrix MUST be less than 4.\n"
            "Please enter the matrix again.\n\n");
        }
    }while((matrix_1.columns!=matrix_1.rows) || matrix_1.rows>3);
    if (matrix_1.rows==1){
        result=(*(*(matrix_1.data)));
    }
    if (matrix_1.rows==2){
        result=(*(*(matrix_1.data)))*(*(*(matrix_1.data+1)+1))-(*(*(matrix_1.data+1)))*(*(*(matrix_1.data)+1));
    }
    if (matrix_1.rows==3){
        int square1=(*(*(matrix_1.data+1)+1))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data+2)+1))*(*(*(matrix_1.data+1)+2));
        int square2=(*(*(matrix_1.data)+1))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data)+2))*(*(*(matrix_1.data+2)+1));
        int square3=(*(*(matrix_1.data)+1))*(*(*(matrix_1.data+1)+2))-(*(*(matrix_1.data)+2))*(*(*(matrix_1.data+1)+1));
        result=(*(*(matrix_1.data)))*square1-(*(*(matrix_1.data+1)))*square2+(*(*(matrix_1.data+2)))*square3;
    }
    clean(matrix_1);
    return result;
}
Matrix inverse(){
    int failure;
    Matrix result;
    do{
        Matrix matrix_1;
        do{
            matrix_1=sourceMatrix();
            if(!(matrix_1.columns==matrix_1.rows)){
                printf("Incorrect dimensions!\nRows and columns of the matrix MUST match.\n"
                "Please enter the matrix again.\n\n");
            }
            if(matrix_1.rows>3){
                printf("Incorrect dimensions!\nRows and columns of the matrix MUST be less than 4.\n"
                "Please enter the matrix again.\n\n");
            }
        }while((matrix_1.columns!=matrix_1.rows) || matrix_1.rows>3);
        result=constructMatrix(matrix_1.rows,matrix_1.columns);
        failure=0;
        if (matrix_1.rows==1){
            if ((*(*(matrix_1.data)))!=0){
                (*(*(result.data)))=1/(*(*(matrix_1.data)));
            }
            else{
                printf("The inverse matrix does not exist!\nThe matrix provided is singular and has determinant 0."
                "\nPlease provide a non-singular matrix.\n");
                failure=1;
            }
        }
        else if (matrix_1.rows==2){
            int determinant=(*(*(matrix_1.data)))*(*(*(matrix_1.data+1)+1))-(*(*(matrix_1.data+1)))*(*(*(matrix_1.data)+1));
            if (determinant!=0){
                (*(*(result.data)))=(*(*(matrix_1.data+1)+1))/determinant;
                (*(*(result.data+1)+1))=(*(*(matrix_1.data)))/determinant;
                (*(*(result.data)+1))=-(*(*(matrix_1.data)+1))/determinant;
                (*(*(result.data+1)))=-(*(*(matrix_1.data+1)))/determinant;
            }
            else{
                printf("The inverse matrix does not exist!\nThe matrix provided is singular and has determinant 0."
                "\nPlease provide a non-singular matrix.\n");
                failure=1;
            }
        }
        else{
            int square1=(*(*(matrix_1.data+1)+1))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data+2)+1))*(*(*(matrix_1.data+1)+2));
            int square2=(*(*(matrix_1.data)+1))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data)+2))*(*(*(matrix_1.data+2)+1));
            int square3=(*(*(matrix_1.data)+1))*(*(*(matrix_1.data+1)+2))-(*(*(matrix_1.data)+2))*(*(*(matrix_1.data+1)+1));
            int determinant=(*(*(matrix_1.data)))*square1-(*(*(matrix_1.data+1)))*square2+(*(*(matrix_1.data+2)))*square3;
            if (determinant!=0){
                (*(*(result.data)))=((*(*(matrix_1.data+1)+1))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data+2)+1))*(*(*(matrix_1.data+1)+2)))/determinant;
                (*(*(result.data)+1))=((*(*(matrix_1.data)+2))*(*(*(matrix_1.data+2)+1))-(*(*(matrix_1.data+2)+2))*(*(*(matrix_1.data)+1)))/determinant;
                (*(*(result.data)+2))=((*(*(matrix_1.data)+1))*(*(*(matrix_1.data+1)+2))-(*(*(matrix_1.data+1)+1))*(*(*(matrix_1.data)+2)))/determinant;
                (*(*(result.data+1)))=((*(*(matrix_1.data+1)+2))*(*(*(matrix_1.data+2)))-(*(*(matrix_1.data+2)+2))*(*(*(matrix_1.data+1))))/determinant;
                (*(*(result.data+1)+1))=((*(*(matrix_1.data)))*(*(*(matrix_1.data+2)+2))-(*(*(matrix_1.data+2)))*(*(*(matrix_1.data)+2)))/determinant;
                (*(*(result.data+1)+2))=((*(*(matrix_1.data)+2))*(*(*(matrix_1.data+1)))-(*(*(matrix_1.data+1)+2))*(*(*(matrix_1.data))))/determinant;
                (*(*(result.data+2)))=((*(*(matrix_1.data+1)))*(*(*(matrix_1.data+2)+1))-(*(*(matrix_1.data+2)))*(*(*(matrix_1.data+1)+1)))/determinant;
                (*(*(result.data+2)+1))=((*(*(matrix_1.data)+1))*(*(*(matrix_1.data+2)))-(*(*(matrix_1.data+2)+1))*(*(*(matrix_1.data))))/determinant;
                (*(*(result.data+2)+2))=((*(*(matrix_1.data)))*(*(*(matrix_1.data+1)+1))-(*(*(matrix_1.data+1)))*(*(*(matrix_1.data)+1)))/determinant;
            }
            else{
                printf("The inverse matrix does not exist!\nThe matrix provided is singular and has determinant 0."
                "\nPlease provide a non-singular matrix.\n");
                failure=1;
            }
        }
        clean(matrix_1);
    }while (failure==1);
    return result;
}
Matrix transpose(Matrix matrix_1){
    Matrix result=constructMatrix(matrix_1.columns, matrix_1.rows);
    for (int i=0;i<result.rows;i++){
        for (int j=0;j<result.columns;j++){
            (*(*(result.data+i)+j))=(*(*(matrix_1.data+j)+i));
        }
    }
    clean(matrix_1);
    return result;
}
