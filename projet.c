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
    char login[50];
    char motDePasse[50];
    int typeUtilisateur;
} USER;
typedef struct
{
    int id;
    USER  user;
} ADMIN;

int autoIdEtu = 0;
int autoIdAdm = 0;
//prototype
int ListerUser(USER Us[], ETUDIANT E[], ADMIN A[], int nbe, int nba);
void afficherListeUser(USER U[], int nu);
void afficherEtudiant(ETUDIANT e);
ETUDIANT saisirEtudiant();
int saisirTabEtudiant(ETUDIANT Etudiants[],int *nbEtu);
ETUDIANT modifieretudiant(ETUDIANT Etudiants[], ETUDIANT e);
int supprimerEtudiant(ETUDIANT Etudiants[], ETUDIANT e);
void afficherTabEtudiant(ETUDIANT Etudiants[], int nbEtu);
ADMIN ajouterAdmin(ADMIN Admins[],int *nbAdm,USER u);
ADMIN chercherAdmin(ADMIN Admins[],int nbAdm,char login[]);
int isAdminExist(ADMIN Admins[],int nbAdm,char login[]);
CLASSE creerClasse(CLASSE c,int *nbCl);
CLASSE chercherClasse(CLASSE classes[],int nbCl,int numClasse);
int isClassExist(CLASSE classes[],int nbCl,int numClasse);
CLASSE ajouterEtudiantAuneClasse(CLASSE classes[],int nbCl,CLASSE c,ETUDIANT e);
void afficherClasses(CLASSE classes[],int nbCl);
int connexion(char* login,char* mdp);
int verifUserExist(char *login, char* mdp);
void ajouterEtudiantAClasse(CLASSE * c, ETUDIANT e);
int main() {
    
    return 0;
}
void afficherEtudiant(ETUDIANT e) {
    printf("id Étudiant : %d\t",e.id);
    printf("Nom : %s\t",e.nom);
    printf("Prénom : %s\t",e.prenom);
    int e.nbPresences = e.presence->nbPresence;
    int e.nbAbsences = e.absence->nbAbsence;
    printf("Nombre de présence : %d\t",e.nbPresences);
    printf("Nombre d'abscence : %d\t",e.nbAbscences);
    printf("Nombre de minutes de retards cumulés : %d\t",e.minutesretardtotal);
    if (e.estBloque)
    {
        printf("Accès\n");
    }
    else
    {
        printf("Bloqué\n");
    }
}
void afficherMois(ETUDIANT e) {
    int nbPresences = e.presence->nbPresence;
    for(int i=0;i<nbPresences;i++) {
        printf("%02d/%02d/%4d \n",e.presence[i].datep.jour,e.presence[i].datep.mois,e.presence[i].datep.annee);
    }
    int nbAbsences = e.absence->nbAbsence;
    for(int j=0;j<nbAbsences;j++) {
        printf("%02d/%02d/%4d \n",e.abscence[i].date.jour,e.abscence[i].date.mois,e.abscence[i].date.annee);
    }
}

int ListerUser(USER Us[], ETUDIANT E[], ADMIN A[], int nbe, int nba) {
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
         
void afficherListeUser(USER U[], int nu) {

    printf("\n             Liste des utilisateurs:\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|   ID   |LOGIN          | TYPE UTILISEUR   |MOT DE PASSE   |\n");
    printf("+-----------------------------------------------------------+\n");
        for (int i = 0; i < nu; i++) {
            printf("|%6d| %-15s|%13s|%14s|\n", U[i].id, U[i].login);
            printf("|%6d| %-15s|", U[i].id , U[i].login);
            if (U[i].typeUtilisateur==1)
            {
                printf("Étudiant");
            }
            else
            {
                printf("Administrateur");

            }
            printf("| %-15s|\n", U[i].motDePasse);
            
        }
}

ETUDIANT saisirEtudiant() {

}

void afficherTabEtudiant(ETUDIANT Etudiants[], int nbEtu)
{
}
