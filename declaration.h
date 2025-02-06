#ifndef DECLARATION_H_INCLUDED
#define DECLARATION_H_INCLUDED


double fonctionG (double x);

double f (double x);

double fonctionG (double);

double df(double x);

void afficherMenu();

void choixMenu();

void relancer();


void bissection(double x0, double x1);

void balayage(double x0, double x1, double pas);

void pointfixes(double x0, double tol, double max_iter);

double newton(double x0, double tol, int max_iter);

double secante(double x0, double x1, double tol, int max_iter);


#endif
