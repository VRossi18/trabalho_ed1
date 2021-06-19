#include "imm.h"
#include <string.h>
#include <stdio.h>
#include "TMat2D.h"



int openImage(char *arq){
    char *ret;
    TMat2D *matriz;
    ret = strstr(arq, ".");
    if(strcmp(ret, ".txt") == 0){
       matriz = txt_to_mat(arq);
       printaMatriz(matriz);
    }else if(strcmp(ret, ".imm") == 0){
        matriz = imm_to_mat(arq);
        printaMatriz(matriz);
    }else{
        printf("Extensão inválida!\n");
    }
    
}

TMat2D *txt_to_mat(char *arqTXT){
    int row, col, data;
    FILE *arq;
    char c;
    char charEnter = '\n';
    char charTab = '\t';
    TMat2D *mat;

    arq = fopen(arqTXT, "r");
    if(arq == NULL){
        return NULL;
    }
    while(fread(&c, sizeof(char), 1, arq)) {
        if(c==charEnter) 
    	    row++;
       	else if(c==charTab && row<=0)
       		col++;	
   	}
    
    rewind(arq);
    
    mat = mat2D_create(row, col);
    if(mat == NULL){
        printf("\nMatriz não foi criada!\n");
        return NULL;
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            fscanf(arq, "%d", &data);
            if((escreveMatriz(mat, i, j, data)) != SUCCESS){
                return NULL;
            }
        }
    }
    fclose(arq);
    return mat;
}