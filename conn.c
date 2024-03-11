#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>

typedef struct {
    int heure;
    int minute;
} Heure;

typedef struct {
    int jour;
    int mois;
    int annee;
} Date;

typedef struct {
    int estPresent;
    Heure hmarque;
    Date datep;
} PRESENCE;

typedef struct {
    int retardQuota;
    int minutesRetard;
    Date date;
} RETARD;

typedef struct {
    int estJustifiee;
    Date date;
} ABSCENCE;

typedef struct {
    int identifiantMessage;
    char expediteur[50];
    char sujet[100];
    char corps[1000];
    char destinataires[100][50];
    int nbDestinataires;
} MESSAGE;

typedef struct {
    int id;
    char login[50];
    char motDePasse[50];
    int typeUtilisateur;
} USER;

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char code[50];
    PRESENCE presence[31];
    PRESENCE abscence[31];
    int nbPresences;
    RETARD retard[31];
    int minutesretardtotal;
    MESSAGE messages[100];
    int nbMessages;
    int estBloque;
    int nbAbsences;
} ETUDIANT;

typedef struct {
    int numClasse;
    char nom[50];
    char filiere[50];
    int annee;
    ETUDIANT etudiants[100];
    int nbEtudiants;
} CLASSE;

typedef struct {
    int id;
    USER  user;
} ADMIN;


int verifUserExist(char *login, char* mdp, USER U[], int n);
int connexion(char* login,char* mdp, USER U[], int n);
char* read_password(char *password, int max_length);

int main() {
    char login[50];
    char *mdp = malloc(15 * sizeof(char));

    USER U[2];
    int n=sizeof(U);
    strcpy(U[0].login,"Admin");
    strcpy(U[0].motDePasse,"passer");
    strcpy(U[1].login,"etu");
    strcpy(U[1].motDePasse,"passe");

    printf("Enter your login: ");
    scanf("%s", login);

    read_password(mdp, 15);
    free(mdp); // ne pas oublier de libérer la mémoire allouée avec malloc !

    printf("\nYour password is: %s\n", mdp);
    printf("\nYour password is: %s\n", mdp);

    if (connexion(login, mdp, U, n)) {
        printf("User is authenticated!\n");
    } else {
        printf("Invalid login or password!\n");
    }

    return 0;
}

char* read_password(char *password, int max_length) {
    char *ch;
    int i = 0;

    printf("Enter your password: ");
    ch=getpass("*");
    while ((ch[1] = getchar())) {
        if (i < max_length - 1) {
            password[i] = ch[1];
            i++;
            putchar('*');
        }
    }
    password[i] = '\0';
    return password;
}

int connexion(char* login,char* mdp, USER U[], int n) {
    return verifUserExist(login, mdp, U, n);
}

int verifUserExist(char *login, char* mdp, USER U[], int n) {
    FILE *f;
    USER user;
    f = fopen("users.txt", "r");
    while (fscanf(f, "%d %s %s\n", &user.id, user.login, user.motDePasse) != EOF) {
        if (strcmp(U[0].login, login) == 0 && strcmp(U[0].motDePasse, mdp) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
