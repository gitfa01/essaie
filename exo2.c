/*EXERCICE 2 : 
Soit un tableau de tableau d’artistes de taille N = 200.
Écrire un sous-programme qui détermine et 
affiche le pourcentage de présence de chaque type d’artiste dans le tableau. 
Un artiste est caractérisé par son nom, son prénom, sa date de naissance et son type.

*/

#include<stdio.h>
#include <string.h>

typedef struct {
    int j;
    int m;
    int a;
} Date;

typedef struct {
        char nom[32];
        char prenom[60];
        char type[32];
        Date ddn;
} Artiste;

int reponse();
void afficherartiste(Artiste a);
Artiste saisieartiste();
void affichertabartiste(Artiste a[], int n);
int saisietabartiste(Artiste A[], int n);
void pourcentagetype(Artiste A[],int n, char tp[]);
void afficherpourcentage(Artiste A[],int n);

int main () {
    const int N=200;
    Artiste A[N];
    int t;
    t=saisietabartiste(A,N);
    afficherpourcentage(A,t);

}

int reponse() {
    int r;
    printf("Voudrez-vous ajouter un autre animal ? Si oui tapez 1 si non tapez 0\n");
    do
    {
        scanf("%d", &r);
        if (r!=0 && r!=1)
        {
            printf("Veuillez choisir une réponse valable. Tapez 1 pour ajouter un autre animal sinon tapez 0\n");
        }
        
    } while (r!=0 && r!=1);
    
    if (r==1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void afficherartiste(Artiste a) {
    printf("%s \t %s \n",a.nom, a.prenom);
    printf("\t Type : %s",a.type);
    printf("\t Date de naissance : %d",a.ddn.j);
    printf("/%d",a.ddn.m);
    printf("/%d \n",a.ddn.a);
}

Artiste saisieartiste() {
    Artiste a;
    printf("Donner le nom de l'artiste \n");
    scanf("%s",a.nom);
    printf("Donner le prenom de l'artiste \n");
    scanf("%s",a.prenom);
    printf("Donner le type de l'artiste \n");
    scanf("%s",a.type);
    printf("Donner la date de naissance de l'artiste \n");
    scanf("%d",&a.ddn.j);
    scanf("%d",&a.ddn.m);
    scanf("%d",&a.ddn.a);
    return a;
}

void affichertabartiste(Artiste a[], int n) {
    for (int i = 0; i < n; i++)
    {
        afficherartiste(a[i]);
    }
    
}

int saisietabartiste(Artiste A[], int n) {
    int i = 0;
    do
    {
        A[i]=saisieartiste();
        i++;
    } while (reponse()&& i<n);
    affichertabartiste(A,i);
    return i;
}

void pourcentagetype(Artiste A[],int n, char tp[]) {
    float ptype;
    int s=0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(tp,A[i].type))
        {
            s++;
        }
    }
    ptype = s*100/n;
    printf("Le pourcentage de %s est de %.2f \n", tp, ptype);
}

void afficherpourcentage(Artiste A[],int n) {
    pourcentagetype(A, n, "chanteur");
    pourcentagetype(A, n, "danseur");
    pourcentagetype(A, n, "peintre");
    pourcentagetype(A, n, "acteur");
}