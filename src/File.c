#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "File.h" //contains "Matrix.h"

FILE *fPtr;
char filePath[]="../data/data.txt";

void fileMenu(Matrix matrix_1){
    printf("\nPlease select one of the following:\n\t1. Save matrix to file then go to menu\n\t"
    "2. Go to menu\n\t3. Exit\n\n");
    int option=validOption(3);
    fileMenuOption(option, matrix_1);
}

void fileMenuOption(int option, Matrix matrix_1){
    switch (option){
        case 1:
            saveFile(matrix_1);
            clean(matrix_1);
            calculationsMenu();
            break;
        case 2:
            clean(matrix_1);
            calculationsMenu();
            break;
        case 3:
            clean(matrix_1);
            exit(0);
            break;
        default:
            break;

    }
}

void saveFile(Matrix matrix_1){
    fPtr = fopen(filePath, "a");
    char dataToAppend[30];
    if (fPtr == NULL)
    {
        printf("\nUnable to open '%s' file.\n", filePath);
        printf("Please check whether file exists and you have write privilege.\n");
    }
    else{
        char buffer[16];
        fputs("\n", fPtr);
        sprintf(buffer, "%d", matrix_1.rows);
        fputs(buffer, fPtr);
        fputs(" ", fPtr);
        sprintf(buffer, "%d", matrix_1.columns);
        fputs(buffer, fPtr);
        fputs(" ", fPtr);
        for (int i=0;i<matrix_1.rows;i++){
            for (int j=0;j<matrix_1.columns;j++){
                snprintf(dataToAppend, 30, "%lf", (*(*(matrix_1.data+i)+j)));
                fputs(dataToAppend, fPtr);
                if (j!=matrix_1.columns-1 || i!=matrix_1.rows-1){
                    fputs(" ", fPtr);
                }
            }
        }
    }
    fclose(fPtr);
}

Matrix loadFile(){
    int rows,columns,choice;
    Matrix matrix_1;
    fPtr = fopen(filePath, "r");
    if (fPtr == NULL){
        printf("\nUnable to open '%s' file.\n", filePath);
        printf("The file has not yet been created as no calculations were performed.\nYou will now be asked to initialise a matrix instead.\n\n");
        choice=3;
    }
    else{
        double result;
        do{
            fscanf(fPtr, "%d", &rows);
            fscanf(fPtr, "%d", &columns);
            matrix_1 = constructMatrix(rows, columns);
            for (int i=0;i<matrix_1.rows;i++){
                for (int j=0;j<matrix_1.columns;j++){
                    fscanf(fPtr, "%lf", &result);
                    (*(*(matrix_1.data+i)+j))=result;
                }
            }
            showMatrix(matrix_1);
            printf("Is this the matrix you wish to choose?\n\t1. Yes\n\t2. No, show the next matrix\n\t3. Initialise matrix instead\n");
            choice=validOption(3);
        }while (choice==2);
        fclose(fPtr);
    }
    if (choice==3){
        printf("Enter the number of rows (max %d). ", MAXROWSIZE);
        rows=validOption(MAXROWSIZE);
        printf("Enter the number of columns (max %d). ", MAXCOLUMNSIZE);
        columns=validOption(MAXCOLUMNSIZE);
        matrix_1=initialiseMatrix(constructMatrix(rows, columns));
    }
    return matrix_1;
}