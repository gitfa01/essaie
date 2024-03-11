#include <stdio.h>

// ... (le reste du code que vous avez fourni)

void modifierRetardQuotaPourTousLesEtudiants(Classe* classe, int nouveauQuota) {
    for (int i = 0; i < classe->nbEtudiants; i++) {
        ETUDIANT* etudiant = &classe->etudiants[i];
        for (int j = 0; j < etudiant->nbPresences; j++) {
            etudiant->retard[j].retardQuota = nouveauQuota;
        }
    }
    printf("Les quotas de retard de tous les étudiants ont été mis à jour avec succès.\n");
}

int main() {
    // ... (le reste du code que vous avez fourni)

    // Exemple d'utilisation de la fonction modifierRetardQuotaPourTousLesEtudiants
    modifierRetardQuotaPourTousLesEtudiants(&classe, 30); // Modifier le quota de retard de tous les étudiants à 30

    return 0;
}