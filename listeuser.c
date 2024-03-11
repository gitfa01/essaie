#include <stdio.h>
#include </home/fatoumata/Bureau/LangageC/projet/projet.h>

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
    int statut;
} USER;
typedef struct {
    int numClasse;
    char nom[50];
    char filiere[50];
    int annee;
    int nbEtudiants;
} CLASSE;
typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    char code[50];
    USER user;
    PRESENCE presence[31];
    PRESENCE abscence[31];
    int nbPresences;
    RETARD retard[31];
    int minutesretardtotal;
    MESSAGE messages[100];
    int nbMessages;
    int estBloque;
    int nbAbsences;
    CLASSE classe;
} ETUDIANT;
typedef struct
{
    int id;
    USER  user;
} ADMIN;

int ListerUser(USER Us[], ETUDIANT E[], ADMIN A[], int nbe, int nba, int max);
void enregistrerUser(USER Us[], int nu);

int main() {
    int ne=5, na=2, max=100;
    ETUDIANT E[ne];
    ADMIN A[na];
    USER Us[max];
    ETUDIANT E[5] = {
	{0, "login1", "motDePasse1", 1}
	{1, "login2", "motDePasse2", 1}
	{2, "login3", "motDePasse3", 1}
	{3, "login4", "motDePasse4", 1}
	{4, "login5", "motDePasse5", 1}
};
Admin Us[2] = {
	{0, "login1", "motDePasse1", 2},
	{1, "login2", "motDePasse2", 2},
};
    ListerUser(U,E,A,ne,na,max);
}

int ListerUser(USER Us[], ETUDIANT E[], ADMIN A[], int nbe, int nba, int maxu) {
    int n=0;
    int id;

    printf("\nListe des utilisateurs:\n");
    if (nba > 0) {
        for (int k = 0; k < nba; k++) {
            Us[n].id = A[k].id;
            if (id != -1) {
                strcpy(Us[n].login,A[k].user.login);
                strcpy(Us[n].motDePasse,A[k].user.motDePasse);
                Us[n].typeUtilisateur=2;
                Us[n].statut=A[k].user.statut;
                n++;
            }
        }
    }
    if (nbe > 0) {
        for (int i = 0; i < nbe; i++) {
            Us[n].id = E[i].id;
            strcpy(Us[n].login,E[i].user.login);
            strcpy(Us[n].motDePasse,E[i].user.motDePasse);
            Us[n].typeUtilisateur=1;
            Us[n].statut=E[i].user.statut;
            n++;
        }
    }
    return n;
}
void enregistrerUser(USER Us[], int nu) {
    FILE *file = fopen("user.ods", "w");
if (file == NULL) {
	printf("Error: Unable to open file user.ods\n");
	return -1;
}

for (int i = 0; i < nu; i++) {
	fwrite(&Us[i], sizeof(USER), 1, file);
}

fclose(file);
}
 