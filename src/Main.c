/*Last Modified: 07/11/2020
  Version: 2.4.1*/

#include <stdio.h>
#include <stdlib.h>
#include "File.h" //contains "Matrix.h"

int main(){
    calculationsMenu();
    return 0;
}

void calculationsMenu(){
    printf("This is a matrix calculator that can perform standard matrix operations.\n"
    "Please select which of the calculations you would like to perform.\n"
    "\t1. Add\n\t2. Subtract\n\t3. Multiply\n\t4. Scalar multiply\n\t5. Power\n\t"
    "6. Identity\n\t7. Determinant (max 3x3)\n\t8. Inverse (max 3x3)\n\t9. Transpose\n\t10. Exit\n\n");
    char option=validOption(10);
    calculationsMenuOption(option);
}

Matrix sourceMatrix(){
    printf("\nPlease select one of the following: "
    "\n\t1. Load an existing matrix\n\t2. Create a new matrix\n\n");
    char option=validOption(2);
    if (option==1){
        return loadMatrix();
    }
    else{
        printf("Enter the number of rows (max %d). ", MAXROWSIZE);
        int rows=validOption(MAXROWSIZE);
        printf("Enter the number of columns (max %d). ", MAXCOLUMNSIZE);
        int columns=validOption(MAXCOLUMNSIZE);
        return initialiseMatrix(constructMatrix(rows, columns));
    }
}

void calculationsMenuOption(int option){
    switch (option){
        case 1:
            displayMatrix(add(sourceMatrix()));
            break;
        case 2:
            displayMatrix(subtract(sourceMatrix()));
            break;
        case 3:
            displayMatrix(multiply(sourceMatrix()));
            break;
        case 4:
            displayMatrix(scalarMultiply(sourceMatrix()));
            break;
        case 5:
            displayMatrix(power());
            break;
        case 6:
            printf("Enter the number of rows and columns (max %d). ", MAXROWSIZE);
            int dimension=validOption(MAXROWSIZE);
            displayMatrix(identity(dimension,dimension));
            break;
        case 7:
            printf("%lf", determinant());
            break;
        case 8:
            displayMatrix(inverse());
            break;
        case 9:
            displayMatrix(transpose(sourceMatrix()));
            break;
        case 10:
            exit(0);
            break;
        default:
            break;
    }
}

int validOption(int options){
    printf("\nPlease enter your option: ");
    int option;
    fflush(stdin);
    while(scanf("%d", &option)!=1){
        fflush(stdin);
    }
    fflush(stdin);

    while (option<1 || option>options){
        printf("Please enter a valid option in the range 1-%d: ", options);
        while(scanf("%d", &option)!=1){
            fflush(stdin);
            printf("Please enter a valid option in the range 1-%d: ", options);
        }
        fflush(stdin);
    }
    return option;
}