#include "imm.h"
#include <string.h>
#include <stdio.h>
#include "TMat2D.h"
#include "stack.h"

typedef struct Img
{
    TMat2D *data;
} Img;

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

int comp_conexo(char *arquivoimm, char *arquivoSaida)
{
    Img *im = lerImage(arquivoimm);
    int lin, col;
    int dadosim;
    int dadosrot;
    if (mat2D_get_lincol(im->data, &lin, &col) != SUCCESS)
    {
        return INVALID_FILE;
    }
    Img *im_rot = (Img *)malloc(sizeof(Img));
    if (im_rot == NULL)
    {
        return INVALID_FILE;
    }
    im_rot->data = mat2D_create(lin, col);

    int label = 1;
    Stack *lista_proximos = create_stack();
    struct Ponto p, p_atual, a;
    for (int i = 0; i < lin; i++)
    {
        for (int j = 0; j < col; j++)
        {
            p.x = i;
            p.y = j;
            mat2D_get_value(im->data, p.x, p.y, &dadosim);
            mat2D_get_value(im_rot->data, p.x, p.y, &dadosrot);
            if ((dadosim == 1) && (dadosrot == 0))
            {
                mat2D_set_value(im_rot->data, p.x, p.y, label);
                stack_push(lista_proximos, p);
                while (stack_size(lista_proximos) != 0)
                {

                    stack_find(lista_proximos, &p_atual);
                    stack_pop(lista_proximos);

                    for (int d = 0; d < 4; d++)
                    {
                        a.x = p.x;
                        a.y = p.y;
                        p.x = p_atual.x - (d == 0) + (d == 1);
                        p.y = p_atual.y - (d == 2) + (d == 3);

                        mat2D_get_value(im->data, p.x, p.y, &dadosim);
                        mat2D_get_value(im_rot->data, p.x, p.y, &dadosrot);

                        if ((dadosim == 1) && (dadosrot == 0))
                        {
                            mat2D_set_value(im_rot->data, p.x, p.y, label);
                            stack_push(lista_proximos, p);
                        }
                        p.x = a.x;
                        p.y = a.y;
                    }
                }
                label++;
            }
        }
    }
    imagemParaArquivo(im_rot, arquivoSaida);
    stack_free(lista_proximos);
    return SUCCESS;
}
