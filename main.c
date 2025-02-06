#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define MAX_ITER 10000
#define TOLERANCE 1e-10
#define PAS 0.2
#define PI 3.141592653589793
#define g(x) 1



int main()
{
     setlocale(LC_CTYPE,"");

    afficherMenu();
    choixMenu();
    return 0;
}

