#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nb_cases_occupees(Terrain *T)
{
	int occupee = 0;
	int x, y;
	for (x = 0; x < largeur(T); x++)
	{
		for (y = 0; y < hauteur(T); y++)
		{
			if (T->tab[x][y] != LIBRE)
				occupee++;
		}
	}
	return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv)
{
	int N, i, l, h;
	float dObst;
	FILE *resFile;
	Terrain T;

	if (argc < 6)
	{
		printf(
			"Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
			argv[0]);
		return 1;
	}

	N = strtol(argv[1], NULL, 10);
	l = strtol(argv[2], NULL, 10);
	h = strtol(argv[3], NULL, 10);
	dObst = strtof(argv[4], NULL);

	// test de l et h
	if (l > DIM_MAX || l % 2 == 0)
	{
		printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
		return 1;
	}
	if (h > DIM_MAX || h % 2 == 0)
	{
		printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
		return 1;
	}
	if ((dObst > 1) || (dObst < 0))
	{
		printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
		return 1;
	}
//on a commencer a completer 
	// Ouverture du fichier résultat
	resFile = fopen(argv[5], "w");
	// Écriture du nombre de terrains
	fprintf(resFile, "Il y a %d terrains en total.\n", N);

	// Initialisation de la fonction random
	// A compléter
	srand(time(NULL)); //on initialise le random avec le temps

	// A compléter
	// Génération aléatoire des terrains
	// Écriture des terrains générés dans le fichier resFile
	// Écriture/Affichage des statistiques
	
	int count_chemin_existe = 0;

	for (i = 0; i < N; i++)
	{
		generation_aleatoire(&T, l, h, dObst);
		int nb_occ = nb_cases_occupees(&T);//on compte le nombre de cases occupees
		int nb_chemin = existe_chemin_vers_sortie(&T);//on regarde si il existe chemin cad 1
		fprintf(resFile, "\nTerrain No.%d, ", i + 1);//on ecrit le numero du terrain
		fprintf(resFile, "Nombre d'obstacle:%d, la densite d'obstacle obtenue:%f \n", nb_occ, (float)nb_occ / (l * h));//on ecrit le nombre d'obstacle et la densite d'obstacle obtenue
		ecrire_terrain(resFile, &T, l, h);//on ecrit le terrain
		if (nb_chemin)// si il existe le chemin
		{
			fprintf(resFile, "Chemin vers sortie\n--------------------------\n");//on ecrit chemin vers sortie
			count_chemin_existe++;//on incremente le nombre de terrain qui a un chemin vers sortie
			printf("Terrain No.%d, Nombre d'obstacle:%d, Chemin vers sortie\n", i + 1, nb_occ);//on affiche le numero du terrain et le nombre d'obstacle
		}
		else
		{
			fprintf(resFile, "Pas de chemin vers sortie\n--------------------------\n");
		}
	}
	fprintf(resFile, "\nIl y a %d terrains qui ont un chemin vers sortie dans %d terrains.\n", count_chemin_existe, N);//on ecrit le nombre de terrain qui a un chemin vers sortie et le nombre de terrain total
	fprintf(resFile, "La probabilité de trouver un chemin vers sortie est %f.\n", (float)count_chemin_existe / N);//on ecrit la probabilite de trouver un chemin vers sortie

	// fermeture des fichiers
	fclose(resFile);
	return 0;
}
