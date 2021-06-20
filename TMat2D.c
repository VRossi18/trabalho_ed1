#include<stdlib.h>
#include<stdio.h>
#include "TMat2D.h"

struct TMat2D{
    int nrows;
    int ncolums;
    int *data;
};

int getCol(TMat2D *mat){
    int col;
    col = mat->ncolums;
    return col;
}

int getLinha(TMat2D *mat){
    int lin;
    lin = mat->nrows;
    return lin;
}

TMat2D *mat2D_create(int nrow, int ncol){
    TMat2D *mat;

    if(nrow <= 0 || ncol <= 0){
        return NULL;
    }

    mat = (TMat2D *)malloc(sizeof(TMat2D));
    if(mat == NULL){
        return NULL;
    }
    mat->nrows = nrow;
    mat->ncolums = ncol;
    mat->data = (int *)malloc(ncol*nrow*sizeof(int));
    if(mat->data == NULL){
        free(mat);
        return NULL;
    }
    return mat;
}

int mat2d_free(TMat2D *mat){
    if(mat == NULL){
        return -1;
    }else{
        free(mat->data);
        free(mat);
    }

    return 0;
}




int escreveMatriz(TMat2D *mat, int lin, int col, int dado){
    int pos;
    
    if(mat == NULL){
        return -1;
        
    }else{
        pos = col * mat->nrows + lin;
        mat->data[pos] = dado;
    }
    return 0;
}

int acessaMatriz(TMat2D *mat, int lin, int col, int *dado){
    if(mat == NULL){
        return -1;
    }else{
        
        *dado = mat->data[col * mat->nrows + lin];
        return 0;
    }
}

int preencheMatriz(TMat2D *mat){
    if(mat == NULL){
        return -1;
    }else{
        for(int i = 0; i < mat->nrows; i++){
            for(int j = 0; j < mat->ncolums; j++){
                mat->data[j * mat->nrows + i] = (int)(rand() % 10);
            }
        }
        return 0;
    }
}

int somaMatrizes(TMat2D *mat, TMat2D *mat2, TMat2D *matsoma){
    if(mat == NULL || mat2 == NULL || matsoma == NULL){
        return -1;
    }else if(mat->ncolums == mat2->ncolums && mat->nrows && mat2->nrows && matsoma->ncolums == mat->ncolums && matsoma->nrows == mat->nrows){
        matsoma->data = (int *)malloc((matsoma->ncolums*matsoma->nrows)*sizeof(int));
        for(int i = 0; i < matsoma->ncolums*matsoma->nrows; i++){
            matsoma->data[i] = mat->data[i] + mat2->data[i];
        }
    }else{
        return 0;
    }
}

int multiplicaMatrizes(TMat2D *mat, TMat2D *mat2, TMat2D *matmult){
    if(mat == NULL || mat2 == NULL || matmult == NULL){
        return -1;
    }else if(mat->ncolums != mat->nrows || mat->nrows != matmult->nrows || mat2->ncolums != matmult->ncolums){
        return -1;
    }else{
        int matriz1[mat->nrows][mat->ncolums];
        int matriz2[mat2->nrows][mat2->ncolums];
        int lin1, col1, i, j, k, pos1, pos2, posmult;

        matmult->data = (int *)malloc((matmult->ncolums*matmult->nrows)*sizeof(int));

        for(int i=0;i<matmult->nrows;i++){
            for(int j=0;j<matmult->ncolums;j++){
                posmult = j * mat->nrows + i;
                matmult->data[posmult] = 0.0;
            }
        }

        for(int i=0;i<mat->nrows;i++){
            for(int j=0;j<mat->ncolums;j++){
                pos1 = j * mat->nrows + i;
                matriz1[i][j] = mat->data[pos1];
            }
        }

        for(int i=0;i<mat2->nrows;i++){
            for(int j=0;j<mat2->ncolums;j++){
                pos2 = j * mat2->nrows + i;
                matriz2[i][j] = mat2->data[pos2];
            }
        }

        lin1 = mat->nrows;
        col1 = mat->ncolums;

        for(i = 0; i < lin1; i++){
            for(j = 0; j < lin1; j++){
                for(k = 0; k < col1; k++){
                    posmult = j * matmult->nrows + i;
                    matmult->data[posmult] = matmult->data[posmult] + (matriz1[i][k])*(matriz2[k][j]);
                }
            }
        }
        return 0;
    }
}

int multiplicaMatrizEscalar(TMat2D *mat, int escalar){
    if(mat == NULL){
        return -1;
    }else{
        for(int i = 0; i < mat->nrows*mat->ncolums; i++){
            mat->data[i] *= escalar;
        }
        return 0;
    }
}

int calcularTracoMatriz(TMat2D *mat, int *result){
    if(mat == NULL){
        return -1;
    }else{
        for(int i = 0; i < mat->nrows; i++){
            for(int j = 0; j < mat->ncolums; j++){
                if(i==j){
                    *result += mat->data[j * mat->nrows + i];
                }
            }
        }
        return 0;
    }
}

int * somaLinhasMatriz(TMat2D *mat){
    
    int *vetlinha;
    vetlinha = (int *)malloc(mat->nrows*sizeof(int));
    for(int i=0; i < mat->nrows; i++){
        vetlinha[i] = 0.0;
    }
    for(int i=0; i < mat->nrows; i++){
        for(int j=0; j < mat->ncolums; j++){
            vetlinha[i] += mat->data[j * mat->nrows + i];
        }
    }
    return vetlinha;
}

int * somaColunasMatriz(TMat2D *mat){

    int *vetcoluna;
    vetcoluna = (int *)malloc(mat->ncolums*sizeof(int));
    for(int i=0;i < mat->ncolums; i++){
        vetcoluna[i] = 0.0;
    }
    for(int j=0; j < mat->ncolums; j++){
        for(int i=0;i < mat->nrows; i++){
            vetcoluna[i] += mat->data[i * mat->ncolums + j];
        }
    }
    return vetcoluna;
}

int printaMatriz(TMat2D *mat){
    int i, j;
    if (mat == NULL){
        return -1;
    }
    else {
        for(i = 0; i < mat->nrows; i++){
		    for(j = 0; j < mat->ncolums; j++){
			printf("%3d\t ", mat->data[j * mat->nrows + i]);
		    }
		printf("\n");
	    }
    }
    return 0;
}

