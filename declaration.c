#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#include "declaration.h"

#define MAX_ITER 10000
#define TOLERANCE 1e-10
#define PAS 0.1
#define H 1e-5
#define PI 3.141592653589793
#define g(x) 1


double fonctionG (double x)
{
    return (x * x - 5)/2;
}

double f (double x)
{
    return x * x * x - x * x * 2 - x * 5 + 6;
}

// Dérivée de la fonction
/*double df(double x)
{
    return x * x * 3 - x * 4 - 5  ;
}*/

double df(double x) {
    return (f(x + H) - f(x - H)) / (2 * H);
}


void afficherMenu()
{
    printf("*******************\n");
    printf("********MENU*******\n");
    printf("*******************\n");
    printf("\nVeuillez choisir la méthode\n");
    printf("\n1: Bissection\n");
    printf("2: Point Fixe\n");
    printf("3: Newton\n");
    printf("4: Sécante\n");
}

void choixMenu()
{
    // Valeur initiale
    double x0 = -3, x1 = 4;
    int choix;
    do {
        printf("\nVeuillez entrer votre choix (1-4): ");
        scanf("%d", &choix);
        if (choix < 1 || choix > 4) {
            printf("Choix invalide. Veuillez entrer un nombre entre 1 et 4.\n");
        }
    } while (choix < 1 || choix > 4);

    switch (choix) {
        case 1:
            // Apelle du balayage
            balayage(x0, x1, PAS);
            relancer();
            break;
        case 2:
            // Appel Point Fixes
            pointfixes(x0, TOLERANCE, MAX_ITER);
            relancer();
            break;
        case 3: {
            // Appel Newton
            double rootN = newton(x0, TOLERANCE, MAX_ITER);
            if (!isnan(rootN)) {
            printf("\tLa racine approchée est : %lf\n", rootN);
            }
            relancer();
            break;
            }
        case 4: {
            // Appel Secante
            double rootS = secante(x0, x1, TOLERANCE, MAX_ITER);
            if(!isnan(rootS)) {
            printf("\tLa racine approchée est : %lf\n", rootS);
            }
            relancer();
            break;
            }
        default:
            printf("Erreur inattendue.\n");
            choixMenu();
            break;
    }
}

void relancer(){
    int choix;

    printf("\nVoulez Vous utiliser une autre méthode?\n");
    printf("1. OUI\n");
    printf("2. NON\n");
    scanf("%d", &choix);

    switch(choix){
        case 1:{
            afficherMenu();
            choixMenu();
        break;
        }
        case 2:{
            printf("\nMerci de vous avoir été utile");
        break;
        }
        default:
            printf("\nChoix entré invalide!");
            relancer();
        break;
    }

}





// Méthode du balayage
void balayage(double x0, double x1, double pas) {
    printf("\nMéthode de Dichotomie\n");
    for (double x = x0; x <= x1; x += pas) {
        if (f(x) * f(x + pas) <= 0) {

            printf("\tUn zéro a été trouvé dans l'intervalle [%.1lf, %.1lf]\n", x, x + pas);
            bissection(x, x + pas);
        }
    }
}


void bissection(double x0, double x1) {
    double xm, fx0, fx1, fxm, ea = 1e-6;
    int i = 0;

    fx0 = f(x0);
    fx1 = f(x1);

    if (fx0 * fx1 > 0) {
        printf("\tCette fonction n'admet pas de zéro sur cet intervalle.\n");
        return;
    }

    while (fabs(x1 - x0) > ea) {
        xm = (x0 + x1) / 2;
        fxm = f(xm);
        i++;

        if (fxm == 0) {
            printf("\tLe critère d'arrêt est atteint après %d itérations.\n", i);
            printf("\tUn zéro exact a été trouvé : %f\n", xm);
            return;
        } else if (fx0 * fxm < 0) {
            x1 = xm;
        } else {
            x0 = xm;
        }
    }

    printf("\tAprès %d itérations, une approximation de la racine est : %f\n", i, xm);
}


void pointfixes (double x0, double tol, double max_iter)
{
    double x1;
    int i = 0;

    printf("\nMéthode des Points Fixes\n");

    x1 = g(x0);

    if (g(x0) == 0)
    {
        printf("\tLa solution de votre fonction est %lf\n", x1);
    }
    else
    {
        while (fabs(x1 - x0) >= tol && i < max_iter)
        {
            x0 = x1;
            x1 = fonctionG(x0);
            i++;
        }

        if (fabs(x1 - x0) < tol && i < max_iter)
        {
            printf("\tLe critère d'arrêt est atteint. Convergence atteinte et nombre d'itérations i = %d\n", i);
            printf("\tLa solution de la Fonction est x1 = %lf\n", x1);
        }
        else
        {
            printf("\tLa méthode n'a pas convergé après %lf itérations.\n", max_iter);
        }
    }
}

double newton(double x0, double tol, int max_iter) {
    printf("\nMéthode de Newton\n");
    double x = x0;
    int i = 0;

    for (i = 0; i < max_iter; i++) {
        double fx = f(x);
        double dfx = df(x);

        if (fabs(fx) < tol) {
            printf("\tLa méthode de Newton a convergé en %d itérations.\n", i + 1);
            return x;
        }

        x = x - fx / dfx;
    }

    printf("\tLa méthode de Newton n'a pas convergé en %d itérations.\n", max_iter);
    return NAN;
}

double secante(double x0, double x1, double tol, int max_iter) {
    printf("\nMéthode de la Secante\n");
    double xn, xn1;
    int i = 0;

    do {
        xn = x1;
        xn1 = xn - f(xn) * (xn - x0) / (f(xn) - f(x0));
        x0 = xn;
        x1 = xn1;
        i++;
    } while (fabs(xn1 - xn) >= tol && i < max_iter);

    if (i == max_iter) {

        printf("\tLa méthode de la sécante n'a pas convergé en %d itérations.\n", max_iter);
        return NAN;
    } else {
         printf("\tLe critère d'arrêt est atteint. Convergence atteinte et nombre d'itérations i = %d\n", i);
        return xn1;
    }
}

