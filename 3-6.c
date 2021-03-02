#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "arbrebin.h"
#include "fap.h"

typedef struct {
    int lg;
    int code[256];
} code_char;

code_char HuffmanCode[256];

/*float entropie_r(Arbre a) {
    if(EstVide(a)) {return 0;}
    float tmp = Etiq(a).p * log2(Etiq(a).p);
    return tmp + entropie_r(FilsGauche(a)) + entropie_r(FilsDroit(a));
}

float entropie(Arbre a) {
    if(EstVide(a)) {return -1;}
    return (-1)*entropie_r(a);
}*/

Arbre ConstruireArbre(fap f) {
    while(!est_fap_vide(f)) {
        Arbre b,c;
        float bb,cc;
        f = extraire(f,&b,&bb);
        if(!est_fap_vide(f))
            return b;
        f = extraire(f,&c,&cc);
        Element tmp; tmp.event = -1; tmp.p = 0;
        Arbre a = NouveauNoeud(b,tmp,c);
        if(!est_fap_vide(f))
            inserer(f,a,bb+cc);
        else
            return a;
    }
    return ArbreVide();
}

int Traiter(Arbre a, code_char c) {
    if(Etiq(a).event != 0) {
        HuffmanCode[(int)(Etiq(a).event)].lg = c.lg;
        for(int i = 0 ; i < c.lg; i++ ){
            HuffmanCode[(int)(Etiq(a).event)].code[i] = c.code[i];
        }
        return 1;
    }
    return 0;
}


void Parcourir_profondeur(Arbre a, code_char c) {
    if(a != NULL) {
        if(!Traiter(a,c)) {
            c.code[c.lg++] = 0;
            Parcourir_profondeur(FilsGauche(a),c);
            c.code[c.lg-1] = 1;
            Parcourir_profondeur(FilsDroit(a),c);
        }
    }
}

void Construire_Code(Arbre huff) {
    code_char a; a.lg = -1;
    Parcourir_profondeur(huff,a);
}

int main (int argc, char**argv) {
    if(argc != 2) {printf("pas ou trop d'argument\n");return -1;}
    FILE *file ;
    int i;
    float ftmp1, ftmp2 , entropie = 0;
    Arbre atmp1;
    file = fopen (argv[1], "r") ;
    fap f = creer_fap_vide();
    for (i = 0; fscanf (file, "%f", &ftmp1) != EOF; i++) {
        Element etmp;
        etmp.event = (char)i;
        etmp.p = ftmp1;
        entropie += ftmp1 * log2(ftmp1);
        atmp1 = NouveauNoeud(NULL,etmp,NULL);
        f = inserer(f,atmp1,ftmp1);
    }
    entropie = -1 * entropie;




    fap ftmp = creer_fap_vide();
    while(!est_fap_vide(f)) {
        f = extraire(f,&atmp1,&ftmp1);
        AfficherArbre(atmp1);
        printf("ftmp1 = %f\n",ftmp1);
        ftmp = inserer(ftmp,atmp1,ftmp1);
    }

    while(!est_fap_vide(ftmp)) {
        ftmp = extraire(ftmp,&atmp1,&ftmp1);
        f = inserer(f,atmp1,ftmp1);
    }








    Arbre arbre = ConstruireArbre(f);
    Construire_Code(arbre);
    AfficherArbre(arbre);
    printf("Event\tCode\n");
    for(int j = 0; j < i ; j++) {
        printf("%d\t",j);
        for(int k = 0; k < HuffmanCode[j].lg; k++){
            printf("%d",HuffmanCode[j].code[k]);
        }
        printf("\n");
    }
    //printf("Entropie : %f\n",entropie(arbre));
    printf("Entropie : %f\n",entropie);


    

    fclose (file) ;
}