#include <stdio.h>
#include <stdlib.h>

#include "math.h"

float entropie(float tab[][2], int len) {
    float somme = 0;
    for(int i = 0; i < len ; i++) {
        somme += tab[i][0]*log2(tab[i][0]);
    }
    return (-1)*somme;
}

int main (int argc, char**argv) {
    if(argc != 2) {printf("pas ou trop d'argument\n");return -1;}
    float tab[1000][2], tmp;
    FILE *f ;
    int i = 0;
    f = fopen (argv[1], "r") ;
    for (i = 0; fscanf (f, "%f", &tmp) != EOF; i++) {
        tab[i][0] = tmp;
        tab[i][1] = i;
    }
    fclose (f) ;
    printf("Entropie : %f .\n",entropie(tab,i));
    return 0;
}