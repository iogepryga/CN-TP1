#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float Binf;
    float Bsup;
    float p;
} symbole_t;

symbole_t symbole[256];
int* table;
int table_len;

int Lettre(float p) {
    int j = 0;
    while(j < table_len && !(symbole[table[j]].Binf < p && p < symbole[table[j]].Bsup)) {
        j++;
    }
    return table[j];
}

int main (int argc, char**argv) {
    FILE *table_file = fopen(argv[1], "r");
    fscanf(table_file,"%d",&table_len);
    table = (int*)malloc(sizeof(int)*table_len);
    float Vmessage;
    sscanf(argv[2],"%f",&Vmessage);
    int n; sscanf(argv[3],"%d",&n);
    
    for(int i = 0; i < table_len ; i++) {
        int tmp;
        float tmp2, tmp3, tmp4;
        fscanf(table_file,"%d %f %f %f",&tmp, &tmp2, &tmp3, &tmp4);
        table[i] = tmp;
        symbole[tmp].p = tmp2;
        symbole[tmp].Binf = tmp3;
        symbole[tmp].Bsup = tmp4;
    }
    for(int i = 0; i < table_len; i++) {
        printf("%d %c %f %f %f\n",table[i],(char)table[i],symbole[table[i]].p,symbole[table[i]].Binf,symbole[table[i]].Bsup);
    }




    printf("%f -> ",Vmessage);
    int symb = Lettre(Vmessage);
    for(int i = 0; i < n;i++) {
        printf("%c",(char)symb);
        Vmessage = (Vmessage-symbole[symb].Binf)/symbole[symb].p;
        symb = Lettre(Vmessage);
    }
    printf("\n");

    free(table);
}