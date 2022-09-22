/*
 * @Author: ThearchyHelios
 * @Date: 2020-11-03 16:10:26
 * @LastEditTime: 2022-09-22 15:29:22
 * @LastEditors: ThearchyHelios
 * @Description: 
 * @FilePath: /TP2/TP2/tri.c
 */

#include "tri.h"

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_insertion(tableau_entiers *t)
{
    int i, j;
    int Clef;

    for (i = 1; i < t->taille; i++)
    {
        /* Assertion : le sous-tableau t->tab[0..i-2] est trié */
        Clef = t->tab[i];

        j = i - 1;

        /* Decalage des valeurs du tableau */
        while ((j >= 0) && (Clef < (t->tab[j] - 1)))
        {
            t->tab[j + 1] = t->tab[j];
            j = j - 1;
        }

        /* insertion de la clef */
        t->tab[j + 1] = Clef;
    }
}
