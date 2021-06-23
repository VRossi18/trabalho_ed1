#ifndef imm_h
#define imm_h
#include <stdio.h>
#include "TMat2D.h"
#define SUCCESS 0
#define INVALID_NULL_POINTER -1

int openImage(char *arq);
TMat2D *txt_to_mat(char *arqTXT);
TMat2D *imm_to_mat(char *arqIMM);
int convert_txt_imm(char *arqTXT, char *arqIMM);
int compConexo(char *arqIMM, char *arqFINAL);
int segment_imm(int seg, char *imm, char *saida);
#endif