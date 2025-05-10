#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>     

typedef struct {
    char Ad[9];     // 8 bits + null
    char Crtl[9];   // 8 bits + null
    char Data[33];  // 32 bits + null
    char FCS[17];   // 16 bits + null
} Trame;

#define FANION "01111110"

void afficher_trame(Trame t) {
    printf("%s | %s | %s | %s | %s\n", FANION, t.Ad, t.Crtl, t.Data, t.FCS);
}

void creer_trame(Trame *t, const char *ad, const char *crtl, const char *data, const char *fcs) {
    strncpy(t->Ad, ad, 8);     t->Ad[8] = '\0';
    strncpy(t->Crtl, crtl, 8); t->Crtl[8] = '\0';
    strncpy(t->Data, data, 32); t->Data[32] = '\0';
    strncpy(t->FCS, fcs, 16);  t->FCS[16] = '\0';
}

void ajout_bit_transparance(Trame *t) {
    int c = 0;
    char d[] = "";
    for (int i = 0; i < strlen(t->Data); i++) {
        d[i] = t->Data[i];
        if (t->Data[i] == '1') {
            c++;
            if (c == 5){
                // Ajouter le '0'
                d[i+1] = '0';
                c = 0;
            }
        } else { c = 0;}
    }
    
    strncpy(t->Data, d, strlen(d));
    t->Data[strlen(d)] = '\0';
}

void retrait_bit_transparance(Trame *t) {
    int c = 0, i = 0;
    char mssg[] = "";

    while (i < strlen(t->Data)){
        mssg[i] = t->Data[i];
        if (mssg[i] == '1') {
            c++;
            if (c == 5){
                // Retrait du bit '0'
                i++;
                c = 0;
            }
        } else {
            c = 0;
        }

        strncpy(t->Data, mssg, strlen(mssg));
        t->Data[strlen(mssg)] = '\0';
    }
}

int main() {
    
    int fd[2];
    int pid;
    Trame trame;

    // Création de la trame
    creer_trame(&trame, "00000001", "00000010", "010101000110100001100101", "1010101010101010");

    // Création du pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        return 2;
    }

    // Processus émetteur
    if (pid == 0) {
        close(fd[0]); // fermer lecture
        write(fd[1], &trame, sizeof(Trame));
        close(fd[1]); // fermeture écriture
        exit(0);
    }
    // Processus récepteur
    else {
        Trame t_recu;
        close(fd[1]); // fermer écriture
        read(fd[0], &t_recu, sizeof(Trame));
        close(fd[0]);
        printf("Trame reçue :\n");
        afficher_trame(t_recu);
    }

    return 0;
}