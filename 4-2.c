#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float Binf;
    float Bsup;
    float p;
} symbole_t;

int string_length(char *s) {
  int result = 0;
  for(int i = 0; *(s+i) != 0 ; i++) {
    result++;
  }
  return result;
}

void ajouter(int* tab, int nb) {
    int j;
    for(j = 0; tab[j] != 0;j++) {
        if(tab[j] == (int)nb) {
            return ;
        }
    }
    tab[j] = nb;
}

int main (int argc, char**argv) {
    symbole_t symbole[256];
    for(int i = 0 ; i < 256 ; i++) {
        symbole[i].p = 0;
        symbole[i].Binf = 0;
        symbole[i].Bsup = 0;
    }
    int len = string_length(argv[1]);
    int* ordre = (int*)malloc(sizeof(int)*(len+1));
    for(int i = 0 ; i <= len ; i++) {
        ordre[i] = 0;
    }



    for(int i = 0; i < len; i++) {
        symbole[(int)argv[1][i]].p += (float)1/(float)len;
        ajouter(ordre,(int)argv[1][i]);
    }

    float Binf= 0, Bsup = 1, Vmessage = 1, Vecart = 1;
    int nbentries = 0;
    for(int i = 0; ordre[i] != 0; i++ ,nbentries++) {
        symbole[ordre[i]].Binf = Binf;
        Binf += symbole[ordre[i]].p;
        symbole[ordre[i]].Bsup = Binf;
    }
    printf("%d\n",nbentries);
    for(int i = 0; ordre[i] != 0; i++) {
        printf("%d %f %f %f\n",ordre[i],symbole[ordre[i]].p,symbole[ordre[i]].Binf,symbole[ordre[i]].Bsup);
    }

    Binf = 0;
    for(int i = 0; i < len;i++) {
        Bsup = Binf + Vecart * symbole[(int)argv[1][i]].Bsup;
        Binf = Binf + Vecart * symbole[(int)argv[1][i]].Binf;
        Vmessage = (Bsup+Binf) / (float)2;
        Vecart = Bsup - Binf;
        // Vecart = Bsup - Binf;
        // Binf = Binf + Vecart * symbole[(int)argv[1][i]].Binf;
        // Bsup = Bsup - Vecart * symbole[(int)argv[1][i]].Bsup;
        // Vmessage = (Bsup+Binf) / (float)2;
    }

    printf("%s -> %f\n",argv[1],Vmessage);

    free(ordre);


}