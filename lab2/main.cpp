#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

double funkcja(const double beta, const int N, const double gamma, const double u) {
    return (beta * (double)N - gamma)*u - beta*pow(u,2);
}

double alfa(const double beta, const int N, const double gamma) {
    return beta*(double)N - gamma;
}

void picarda (const double beta, const int N, const double gamma, const double tmax, const  double krok, const double u0, const double TOL,  double mu, FILE *file) {
    const int n = (int)(tmax / krok);
    double un = u0;
    double umu = u0;
    double un_1 = 0.0;
    double muindex;
    double t = 0.0;
    for(int i = 0; i < n; i++) {
        t = krok*i;
        muindex = 0.0;

        while (true) {
            un_1 = un + (krok/2.0) * ( (alfa(beta, N, gamma)*un  - beta*pow(un, 2))  + ( alfa(beta, N, gamma)*umu -beta*pow(umu, 2) ) );
            if (fabs(un_1 - umu) < TOL || muindex > mu) {
                break;
            } else {
                umu = un_1;
                muindex++;   
            }
        }
        fprintf(file, "%g %g %g \n", t, un_1, N - un_1);
        un = un_1;
        umu = un_1;
    }
}

void newtona (const double beta, const int N, const double gamma, const double tmax, const double krok, const double u0, const double TOL,  double mu, FILE *file) {
    const int n = (int)(tmax / krok);
    double un = u0;
    double umu = u0;
    double un_1 = 0.0;
    double muindex;
    double t = 0.0;
    for(int i = 0; i < n; i++) {
        t = krok*i;
        muindex = 0.0;

        while (true) {
            double up = umu - un - (krok/2.0) * ( (alfa(beta, N, gamma) * un - beta*pow(un,2)) + (alfa(beta, N, gamma)*umu - beta*pow(umu,2)) );
            double down = 1 - (krok/2.0) * (alfa(beta, N, gamma) - 2*beta*umu);
            un_1 = umu - (up/down);
            if (fabs(un_1 - umu) < TOL || muindex > mu) {
                break;
            } else {
                umu = un_1;
                muindex++;   
            }
        }
        fprintf(file, "%g %g %g \n", t, un_1, N - un_1);
        un = un_1;
        umu = un_1;
    }    
}

void rk2 (const double beta, const int N, const double gamma, const double tmax, const  double krok, const double u0, const double TOL,  double mu, FILE *file) {
    const int n = (int)(tmax / krok);
    double startU1 = u0;
    double startU2 = u0;
    double un = u0;
    double un_1 = 0.0;
    double U1 = 0.0;
    double U2 = 0.0;
    double muindex;

    double m[2][2] = {0};
    const double a[2][2] = {1/4.0, 1/4.0 - (sqrt(3)/6.0), 1/4.0 + (sqrt(3)/6.0), 1 / 4.0};
    const double b[2] = {1 / 2.0, 1 / 2.0};

    double F1 = 0.0;
    double F2 = 0.0;
    double dU1 = 0.0;
    double dU2 = 0.0;
    double t = 0.0;
    for (int i = 0; i < n; i++) {
        t = krok*i;
        muindex = 0.0;
        F1 = startU1 - un - krok* (a[0][0]* ( alfa(beta, N, gamma)*startU1 - beta*pow(startU1,2) ) + a[0][1]*( alfa(beta, N, gamma)*startU2 - beta*pow(startU2,2) ) );
        F2 = startU2 - un - krok* (a[1][0]* ( alfa(beta, N, gamma)*startU1 - beta*pow(startU1,2) ) + a[1][1]*( alfa(beta, N, gamma)*startU2 - beta*pow(startU2,2) ) );

        m[0][0] = 1.0 - krok*a[0][0]* (alfa(beta, N, gamma) - 2*beta*startU1);
        m[0][1] = -krok*a[0][1]*(alfa(beta, N, gamma) - 2*beta*startU2);
        m[1][0] = -krok*a[1][0]*(alfa(beta, N, gamma) - 2*beta*startU1);
        m[1][1] = 1 - krok*a[1][1]*(alfa(beta, N, gamma) - 2*beta*startU2);

        dU1 = (F2 * m[0][1] - F1 * m[1][1]) / (m[0][0]*m[1][1] - m[0][1]*m[1][0]);    
        dU2 = (F1 * m[1][0] - F2 * m[0][0]) / (m[0][0]*m[1][1] - m[0][1]*m[1][0]); 
        while(true) {
            U1 = startU1 + dU1;
            U2 = startU2 + dU2;
            if ( (fabs(U1 - startU1) < TOL && fabs(U2 - startU2)) || muindex > mu) {
                break;
            } else {
                startU1 = U1;
                startU2 = U2;
                muindex++;
            }
        }
        un_1 = un + krok * (b[0]*funkcja(beta,N, gamma, U1) + b[1]*funkcja(beta,N,gamma, U2));
        un = un_1;
        startU1 = un;
        startU2 = un; 
        fprintf(file, "%g %g %g \n", t, un, N - un);       
    }

}


int main() {
    FILE *file1;
	    file1 = fopen("picard.dat", "w");
    FILE *file2;
	    file2 = fopen("newton.dat", "w");
    FILE *file3;
	    file3 = fopen("rk2.dat", "w");
    const double beta = 0.001;
    const int N = 500;
    const double gamma = 0.1;
    const double tmax = 100.0;
    const double krok = 0.1; 
    const double u0 = 1.0;
    const double TOL = pow(10, -6);
    const double mu = 20.0;

    picarda(beta, N, gamma, tmax, krok, u0, TOL, mu, file1);
    newtona(beta, N, gamma, tmax, krok, u0, TOL, mu, file2);
    rk2(beta, N, gamma, tmax, krok, u0, TOL, mu, file3);


    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 0;
}