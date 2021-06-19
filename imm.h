#ifndef imm_h
#define imm_h
#include <stdio.h>
#include "TMat2D.h"
#define SUCCESS 0
#define INVALID_NULL_POINTER -1

int openImage(char *arq);
TMat2D *txt_to_mat(char *arqTXT);
TMat2D *imm_to_mat(char *arqIMM);

#endif