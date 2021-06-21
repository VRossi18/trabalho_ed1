#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imm.h"

int main(int argc, char *argv[])
{
    if (strcmp(argv[1], "-open") == 0)
    {
        if ((openImage(argv[2])) == SUCCESS)
        {
            printf("Arquivo foi aberto!\n");
        }
        else
        {
            printf("Erro. Arquivo não foi aberto!\n");
        }
    }

    else if (strcmp(argv[1], "-convert") == 0)
    {
        if (convert_txt_imm(argv[2], argv[3]) == SUCCESS)
            printf("Arquivo convertido com sucesso");

        else
            printf("Erro ao converter o arquivo");
    }

    else if (strcmp(argv[1], "-segment") == 0)
    {
        if (segment_imm(atoi(argv[2]), argv[3], argv[4]) == SUCCESS){
            printf("Arquivo segmentado com sucesso!");
        }else
            printf("Erro no segmento!");
        
    }

    else if (strcmp(argv[1], "-cc") == 0)
    {
        comp_conexo(argv[2], argv[3]);
    }

    else if (strcmp(argv[1], "-lab") == 0)
    {
    }

    else
    {
        system("clear");
        printf("Comando inexistente");
    }
    return 0;
}


