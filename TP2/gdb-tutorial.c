/* Tutorial developpe par Matthieu Moy */
/* modifie par Olivier Muller, 2012*/

#include <stdio.h>

void f(void);
void calcul_et_imprime_fact(int n);
int fact(int n);

 /*
    Ce fichier est un tutorial pas-a-pas pour utiliser le deboggeur gdb.
    Un debogueur est un outil precieux pour comprendre ce qui ne va pas
    dans vos programmes. Les quelques minutes que vous allez passer a
    apprendre a l'utiliser seront largement rentabilisees par la suite !
 
    Commencez par le compiler. Pour pouvoir utiliser gdb, il faut
    utiliser l'option -g de gcc a la compilation :
 
    $ gcc -g gdb-tutorial.c -o gdb-tutorial
 
    Vous pouvez lancer l'executable gdb-tutorial dans gdb en ligne de 
    commande comme ceci :
 
    $ gdb ./gdb-tutorial
 
    Commencons par quelque chose de simple : demarrer le programme. On
    tape "run", ou simplement la lettre "r" dans la ligne de commande gdb.
    */

int main (void) 
{
        unsigned i;
        int j;
        int *ptr = NULL; /* NULL est une adresse invalide, on n'a pas le
                            droit de dereferencer un pointeur NULL */
        printf ("Bonjour\n");
        printf ("Je vais faire un acces memoire interdit\n");
 /* 
    La ligne suivante va faire un "Segmentation fault".
    Le deboggeur va s'arreter sur cette ligne.
    */
        *ptr = 0;
 /*
    Le bug etait facile a trouver. 
    Vous pouvez le corriger en mettant en commentaire la ligne impliquée. 
    Evidemment le programme doit être recompilé pour corriger le bug. 
    A ce stade, on peut :
    - soit quitter gdb (quit), recompiler le programme, relancer gdb et
    reprendre le tutorial à ce stade.
    - soit continuer notre séance de débogage en sautant l'erreur. Pour se
    déplacer dans le programme sans avoir à le recompiler, utilisez la
    commande "jump". Ici un "jump gdb-tutorial.c:43", nous permettra de
    repartir juste après dans le programme.

    On va maintenant faire une execution pas-a-pas. Il faut commencer par
    donner a gdb un endroit du code ou on veut s'arreter : un point d'arret.

    Dans la ligne de commande gdb, on fait "break gdb-tutorial.c:62"
    (ou "b 62") pour s'arreter a la ligne 62 de gdb-tutorial.c. Relancez
    l'execution avec la commande "run".
    */
        printf ("On avance ...\n"); /* mettre le point d'arret ici */
 /*
    Maintenant, vous devriez avoir votre programme arrete sur la ligne
    qui precede. Tapez "next", ou simplement "n" pour avancer dans
    l'execution du programme, plusieurs fois. Petite astuce, apres
    avoir tape "n" une fois, il suffit d'appuyer sur Entree pour
    refaire un "next".
    */
        printf ("On avance encore ...\n");
        printf ("On avance encore un peu ...\n");
        printf ("On avance encore un peu ...\n");
        printf ("On avance une derniere fois ...\n");
        printf ("Et voila !\n");
 /*
    Il y a deux commandes pour executer un programme pas a pas :
    - next, pour executer completement l'instruction suivante
    - step, "rentre" dans la fonction si l'instruction suivante est un
    appel de fonction.

    Essayez successivement "step" et "next" sur les lignes suivantes.
    */
        f();
        f();
        f();
 /*
    Bon, l'execution pas a pas, c'est bien, mais c'est penible quand
    il y a beaucoup de code a executer. Par exemple, la boucle 
    suivante prendrait trop de temps, on veut la sauter.

    Pour cela, poser un point d'arret sur la ligne indiquee ci-dessous,
    puis faites "continue" (ou juste "c") dans gdb.
    */
        j = 0;
        for (i = 0; i <= 1000; ++i) {
                j = j + i;
        }
        printf ("Fin de la boucle\n"); /* mettre le point d'arret ici */
 /*
    On peut bien sur visualiser le contenu d'une variable,
    avec la commande "print", ou simplement "p". On peut
    maintenir l'affichage d'une variable avec "display".

    Par exemple, faites maintenant "display i", puis executez la
    boucle suivante pas a pas. Faites "p j" pour connaitre la valeur
    de j.
    */

        for (i = 1; i <= 1000; i = i * 2) {
                j = j + i;
        }
 /*
    On peut aussi afficher des expressions C un peu plus complexes.
    Essayez par exemple

    (gdb) p i+j
    (gdb) p &i
    (gdb) p &j
    (gdb) p dire_bonjour("Monsieur")

    (dans le dernier cas, gdb va effectivement appeler la fonction
    dire_bonjour, definie plus bas)

    On peut aussi s'amuser un peu avec les pointeurs. Faites:

    (gdb) p &i
    $2 = (unsigned int *) 0x12345678

    La valeur 0x12345678, adresse de i, sera a priori differente chez
    vous. Affichez maintenant l'expression *(unsigned int *)0x12345678
    (en remplacant 0x12345678 par la valeur que vous avez eu ci-dessus).
    Vous devriez avoir 1024, qui est bien la valeur de i.
    */
        printf ("i=%i\n", i);
 /*
    Tout ca se complique un peu quand on a des appels de fonctions.
    Entrez dans la fonction appelee a la ligne suivante avec la
    commande "s", on se retrouve la bas !
  */
    calcul_et_imprime_fact(10);

 /*
    Une derniere chose : il arrive que le programme parte dans une
    boucle infinie, et on voudrait savoir ou est cette boucle.

    Rien de plus simple : lancez le programme ("c" pour "continue"),
    puis tapez Control-c pour arreter son execution et reprendre la
    main dans gdb.

    Utilisez cette technique pour voir laquelle de ces boucles est une
    boucle infinie (et lesquelles sont juste tres longues !).

    La commande "jump" déjà vue peut être utilisée pour sauter une boucle
    trop longue. Il faut garder à l'esprit que le code sauté ne sera pas
    simulé par gdb et de fait, la simulation continuera dans certains cas
    avec de mauvaises valeurs.
    Autre information intéressante, certains compilateurs détectent les
    boucles infinies et suppriment le code les suivant. Dans ces cas, gdb
    vous indiquera que vous voulez sautez en dehors du programme...
    */
        j = 1;
        while (j > 0) {
                j++;
        }

        i = 10;
        while (i >= 0) {
                i--;
        }

        i = 0; j = 0;
        while (i == j) {
                i++; j++;
        }

 /*
    Voila, vous avez termine et vous savez a peu pres tout ce que vous
    devez savoir pour une utilisation courante. La commande help vous
    permettra d'en apprendre encore plus.
    Les plus curieux pourront lire le manuel de gdb : 
    http://sourceware.org/gdb/download/onlinedocs/
    */
}

void f(void)
{
        printf ("Appel de f()\n");
        printf ("Fin de f()\n");
}

void calcul_et_imprime_fact(int n)
{
    /*
      Re-bonjour,
    
      A ce stade, n doit etre egal a 10. Verifiez avec un "p n". Entrez
      dans la fonction fact avec un "step".
    */
    int res = fact(n);
    printf ("fact(%i) = %i\n", n, res);  
}

int fact(int n)
{
    printf ("Calcul de fact(%i)\n", n);
    /*
      Si c'est la premiere fois que vous passez ici, n doit etre 
      egal a 10. Verifiez avec un "p n". Continuez l'execution pas a pas
      avec "step" (et non "next", pour rentrer dans les appels recursifs
      successifs de fact). Faites par exemple 5 appels puis lisez le
      commentaire suivant.
    */

    /*
      Voila, je suppose que vous en etes au 5eme appel recursif. Donc,
      "n" doit valoir 5. Verifiez avec "p n".

      Mais dans la pile, il y a toujours les autres appels, avec les
      valeurs de "n" comprises entre 10 et 5. Faites "where" pour voir
      l'etat de la pile (ou "backtrace").

      Pour naviguer dans la pile, utilisez les commandes "up" et "down".
      Par exemple, faites deux fois "up", puis "p n". Vous voyez la
      valeur de "n" au 3eme appel, c'est a dire 7.

      Faites deux fois "down", et vous voila revenu ou vous etiez.
      Faites maintenant "finish" pour terminer
      l'appel de fonction courante, jusqu'a revenir a la fonction
      "main".
    */
    if (n <= 1) {
        return 1;
    } else {
        return n * fact(n - 1);
    }
}

int dire_bonjour(char *nom)
{
        printf("Bonjour, %s\n", nom);
        return 42;
}

