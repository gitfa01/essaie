int bissextile(int annee) {
    if ( !( annee % 4) && ( ( annee % 100 ) || !( annee % 400 ) ) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int valide_date(int a, int m, int j) {
    int j_m = 31;

    if (m == 2) {

        j_m = bissextile(a) ? 29 : 28;

    } else if (m == 4 || m == 6 || m == 9 || m == 11) {

        j_m = 30;

    }
    return j <= j_m;
}
void date_suivante(int *jour, int *mois, int *annee)
{
    (*jour)++;
    if (*jour > 30 && (*mois == 4 || *mois == 6 || *mois == 9 || *mois == 11)) {
        *jour = 1;
        *mois = *mois + 1;
    } else if (*jour > 31 && (*mois == 1 || *mois == 3 || *mois == 5 || *mois == 7 || *mois == 8 || *mois == 10 || *mois == 12)) {
        *jour = 1;
        *mois = *mois + 1;
    } else if (*jour > 28 && *mois == 2 && (*annee % 4) != 0) {
        *jour = 1;
        *mois = *mois + 1;
    } else if (*jour > 29 && *mois == 2 && (*annee % 4) == 0) {
        *jour = 1;
        *mois = *mois + 1;
    }
    if (*mois > 12) {
        *mois = 1;
        *annee = *annee + 1;
    }
}