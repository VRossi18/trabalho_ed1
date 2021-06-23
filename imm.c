#include "imm.h"
#include <string.h>
#include <stdio.h>
#include "TMat2D.h"
#include "TStack.h"

int openImage(char *arq)
{
    char *ret;
    if (arq == NULL)
    {
        return INVALID_NULL_POINTER;
    }
    TMat2D *matriz;
    ret = strstr(arq, ".");
    if (strcmp(ret, ".txt") == 0)
    {
        matriz = txt_to_mat(arq);
        if (matriz != NULL)
        {
            printaMatriz(matriz);
            return SUCCESS;
        }
        else
        {
            printf("Erro na alocação da Matriz!\n");
            return INVALID_NULL_POINTER;
        }
    }
    else if (strcmp(ret, ".imm") == 0)
    {
        matriz = imm_to_mat(arq);
        if (matriz != NULL)
        {
            printaMatriz(matriz);
        }
        else
        {
            printf("Erro na alocação da Matriz!\n");
            return INVALID_NULL_POINTER;
        }
    }
    else
    {
        printf("Extensão inválida!\n");
    }
}

TMat2D *txt_to_mat(char *arqTXT)
{
    int row = 0, col = 1, data;
    FILE *arq;
    char c;
    TMat2D *mat;

    arq = fopen(arqTXT, "r");
    if (arq == NULL)
    {
        return NULL;
    }
    while (fread(&c, sizeof(char), 1, arq))
    {
        if (c == '\n')
        {
            row++;
        }
        else if (c == '\t' && row <= 0)
        {
            col++;
        }
    }

    rewind(arq);

    mat = mat2D_create(row, col);
    if (mat == NULL)
    {
        printf("\nMatriz não foi criada!\n");
        return NULL;
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(arq, "%d", &data);
            escreveMatriz(mat, i, j, data);
        }
    }
    fclose(arq);
    return mat;
}

TMat2D *imm_to_mat(char *arqIMM)
{
    int row, col, data;
    TMat2D *mat;

    FILE *arq;
    arq = fopen(arqIMM, "rb");
    if (arq == NULL)
    {
        return NULL;
    }
    fread(&row, sizeof(int), 1, arq);
    fread(&col, sizeof(int), 1, arq);
    mat = mat2D_create(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fread(&data, sizeof(int), 1, arq);
            if ((escreveMatriz(mat, i, j, data)) != SUCCESS)
            {
                return NULL;
            }
        }
    }
    fclose(arq);
    return mat;
}

int convert_txt_imm(char *arqTXT, char *arqIMM)
{
    int row, col, data;
    FILE *arq;

    arq = fopen(arqIMM, "wb");
    if (arq == NULL)
    {
        printf("Erro ao abrir arquivo!");
        return INVALID_NULL_POINTER;
    }

    TMat2D *mat = txt_to_mat(arqTXT);
    row = getLinha(mat);
    col = getCol(mat);

    fwrite(&col, sizeof(int), 1, arq);
    fwrite(&row, sizeof(int), 1, arq);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            acessaMatriz(mat, i, j, &data);
            fwrite(&data, sizeof(int), 1, arq);
        }
    }

    free(mat);
    fclose(arq);
    return SUCCESS;
}

int segment_imm(int seg, char *imm, char *saida){
    if(seg<0 || seg>255){
        return -1;
    }
    int lin, cols, x;

    TMat2D *mat = imm_to_mat(imm);
    if(imm == NULL)
        return INVALID_NULL_POINTER;

    FILE *arqseg = fopen(saida, "wb");
	if(arqseg ==NULL){
		return -1;
    }
    lin = getLinha(mat);
    cols = getCol(mat);

    fwrite(&cols, sizeof(int), 1, arqseg);
    fwrite(&lin, sizeof(int), 1, arqseg);

    for(int i=0; i<lin; i++){
        for(int j=0; j<cols; j++){
            acessaMatriz(mat, i, j, &x);
            if(x>=seg){
               x=1;                    
            }else{
                x=0;
            }
           fwrite(&x,sizeof(int), 1, arqseg);             
        }
    }

    free(mat);
    fclose(arqseg);

    return SUCCESS;
}

int compConexo(char *arqIMM, char *arqFINAL){
    int dadosArq;
    int grupo = 1;
    int lin, col;
    int dataEntrada;
    int dataSaida;

    TMat2D *imm = imm_to_mat(arqIMM);
    if(imm == NULL){
        return INVALID_NULL_POINTER;
    }
    lin = getLinha(imm);
    col = getCol(imm);

    TMat2D *res = mat2D_create(lin, col);

    TStack *agrup = create_stack();
    preencheMatriz(res);

    Ponto ponto; 
    Ponto recebe;
    Ponto aux;

    for(int i = 0; i < lin; i++){
        for(int j = 0; i < col; i++){
            ponto.x = i;
            ponto.y = j;

            acessaMatriz(imm, ponto.x, ponto.y, &dataEntrada);
            acessaMatriz(res, ponto.x, ponto.y, &dataSaida);

            if((dataEntrada == 1) && (dataSaida == 0)){
                escreveMatriz(res, ponto.x, ponto.y, grupo);
                stack_push(agrup, ponto);
                while(stack_size(agrup) != 0){
                    stack_top(agrup, &recebe);
                    stack_pop(agrup);
                    for(int next = 0; next < 4; next++){
                        aux.x = ponto.x;
                        aux.y = ponto.y;
                        ponto.x = recebe.x - (next == 0) + (next == 1);
                        ponto.y = recebe.y - (next == 2) + (next == 3);
                        acessaMatriz(imm, ponto.x, ponto.y, &dataEntrada);
                        acessaMatriz(res, ponto.x, ponto.y, &dataSaida);

                        if((dataEntrada == 1) && (dataSaida == 0)){
                            escreveMatriz(res, ponto.x, ponto.y, grupo);
                            stack_push(agrup, ponto);
                            
                        }
                        ponto.x = aux.x;
                        ponto.y = aux.y;
                    }
                }
            grupo++;
            printf("MILAGROSAMENTE CHEGOU AQUI");
            }
            
            
        }
    }
    FILE *arq = fopen(arqFINAL, "wb");
    fwrite(&lin, sizeof(int), 1, arq);
    fwrite(&col, sizeof(int), 1, arq);
    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){
            acessaMatriz(res, i, j, &dadosArq);
            fwrite(&dadosArq, sizeof(int), 1, arq);
        }
    }
    stack_free(agrup);
    return SUCCESS;
}
