#ifndef matriz_h
#define matriz_h
#include <stdlib.h>

typedef struct TMat2D TMat2D;

int getCol(TMat2D *mat);

int getLinha(TMat2D *mat);

TMat2D *mat2D_create(int nlin, int ncol);

int mat2d_free(TMat2D *mat);

int escreveMatriz(TMat2D *mat, int lin, int col, int dado);

int acessaMatriz(TMat2D * mat, int lin, int col, int *valor);

int preencheMatriz(TMat2D *mat);

int somaMatrizes(TMat2D *mat, TMat2D *mat2, TMat2D *matsoma);

int multiplicaMatrizes(TMat2D *mat, TMat2D *mat2, TMat2D *matmult);

int multiplicaMatrizEscalar(TMat2D *mat, int escalar);

int calcularTracoMatriz(TMat2D *mat, int *result);

int * somaLinhasMatriz(TMat2D *mat);

int * somaColunasMatriz(TMat2D *mat);

int printaMatriz(TMat2D *mat);

#endif