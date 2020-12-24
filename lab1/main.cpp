#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;



double funkcja(const double lambda, const double y) {
    return lambda * y;
}

double rozwiazanie(const double lambda, const double t) {
    return exp(lambda * t);
}

double napiecie(const double w, const double t) {
    return 10.0 * sin(w*t);
}

void metodaJE(const double y0,const double lambda, int n, const double krok, FILE *file) {
    double yn = y0;
    double yn_1 = 0.0;
    double tn = 0.0;

    for (int i = 0; i < n; i++) {
        tn = krok * i;
        yn_1 = yn + krok * funkcja(lambda, yn);
        fprintf(file, "%.2lf  %lf  %lf  %lf \n",tn, yn, rozwiazanie(lambda, tn), abs(yn -  rozwiazanie(lambda, tn)));
        yn = yn_1;
        
    }
    fprintf(file, "\n \n");
}


void rk2(const double y0,const double lambda, int n, const double krok, FILE *file) {
    double yn = y0;
    double yn_1 = 0.0;
    double tn = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;

    for (int i = 0; i < n; i++) {
        tn = krok * i;
        k_1 = funkcja(lambda, yn);
        k_2 = funkcja(lambda,yn + krok * k_1);
        yn_1 = yn + (krok/2) * (k_1 + k_2);
        fprintf(file, "%.2lf  %lf  %lf  %g \n",tn, yn, rozwiazanie(lambda, tn), abs(yn -  rozwiazanie(lambda, tn))); 
        yn = yn_1;
         
    }  
    fprintf(file, "\n \n");  
}


void rk4(const double y0,const double lambda, int n, const double krok, FILE *file) {
    double yn = y0;
    double yn_1 = 0.0;
    double tn = 0.0;
    double k_1 = 0.0;
    double k_2 = 0.0;
    double k_3 = 0.0;
    double k_4 = 0.0; 

    for (int i = 0; i < n; i++) {
        tn = krok * i;
        k_1 = funkcja(lambda, yn);
        k_2 = funkcja(lambda, yn + (krok/2)*k_1);
        k_3 = funkcja(lambda, yn + (krok/2)*k_2);
        k_4 = funkcja(lambda, yn + krok*k_3);
        yn_1 = yn + (krok/6) * (k_1 + 2*k_2 + 2*k_3 + k_4); 
        fprintf(file, "%.2lf  %lf  %lf  %g \n",tn, yn, rozwiazanie(lambda, tn), abs(yn -  rozwiazanie(lambda, tn)));
        yn = yn_1;
        
    }  
    fprintf(file, "\n \n");   
}

void rlc(const double i0, const double q0, const double w_v, const double R, const double L, const double C, const double n, const double krok, FILE *file) {
    double In = i0;
    double Qn = q0; 
    double In_1 = 0.0;
    double Qn_1 = 0.0;
    double tn = 0.0;
    double k1q = 0.0;
    double k1i = 0.0;
    double k2q = 0.0;
    double k2i = 0.0;
    double k3q = 0.0;
    double k3i = 0.0;
    double k4q = 0.0;
    double k4i = 0.0;

    for (int i = 0; i < n; i++) {
        tn = krok * i;
        k1q = In;
        k1i = (napiecie(w_v, tn)/L) - (1.0/(L * C))*Qn - (R/L)*In; 
        k2q = In + (krok/2.0)*k1i;
        k2i = (napiecie(w_v, krok*(0.5 + i))/L) - (1.0/(L * C))*(Qn + (krok/2.0)*k1q) - (R/L)*(In + (krok/2.0)*k1i); 
        k3q = In + (krok/2.0)*k2i;
        k3i = (napiecie(w_v, krok*(0.5 + i))/L) - (1.0/(L * C))*(Qn + (krok/2.0)*k2q) - (R/L)*(In + (krok/2.0)*k2i); 
        k4q = In + krok*k3i;
        k4i = (napiecie(w_v, krok*(1.0 + i))/L) - (1.0/(L * C))*(Qn + krok*k3q) - (R/L)*(In + krok*k3i); 
        Qn_1 = Qn + (krok/6.0) * (k1q + 2*k2q + 2*k3q + k4q);
        In_1 = In + (krok/6.0) * (k1i + 2*k2i + 2*k3i + k4i);
        fprintf(file, "%.4lf  %lf  %g \n",tn, In, Qn);
        Qn = Qn_1;
        In = In_1;
    }
    fprintf(file, "\n \n"); 
}

int main() {
    // task 1
    FILE *file1;
	    file1 = fopen("mje.dat", "w");
    
    FILE *file2;
	    file2 = fopen("rk2.dat", "w");

    FILE *file3;
	    file3 = fopen("rk4.dat", "w");

    FILE *file4;
	    file4 = fopen("rlc.dat", "w");

    const double y0 = 1.0;
    const double lambda = -1.0;
    const double startT = 0.0;
    const double endT = 5.0;
    const double krok_1 = 0.01;
    const double krok_2= 0.1;
    const double krok_3 = 1.0;

    const int n1 = (endT - startT) / krok_1;
    const int n2 = (endT - startT) / krok_2;
    const int n3 = (endT - startT) / krok_3;


    // task 1
    metodaJE(y0, lambda, n1, krok_1, file1);
    metodaJE(y0, lambda, n2, krok_2, file1);
    metodaJE(y0, lambda, n3, krok_3, file1);
    // task 2
    rk2(y0, lambda, n1, krok_1, file2);
    rk2(y0, lambda, n2, krok_2, file2);
    rk2(y0, lambda, n3, krok_3, file2);
    // task 3
    rk4(y0, lambda, n1, krok_1, file3);
    rk4(y0, lambda, n2, krok_2, file3);
    rk4(y0, lambda, n3, krok_3, file3);
    // task 4

    const double krok = 0.0001;
    const double R = 100.0;
    const double L = 0.1;
    const double C = 0.001;
    const double w_0 = 1.0/sqrt(L*C);
    const double T_0 = (2*PI) / w_0;
    const int n_4 = (4 * T_0) / krok;
    const double Q_0 = 0.0; 
    const double I_0 = 0.0;
    const double w_v1 = 0.5 * w_0;
    const double w_v2 = 0.8 * w_0;
    const double w_v3 = 1.0 * w_0;
    const double w_v4 = 1.2 * w_0;

    rlc(I_0, Q_0, w_v1, R, L, C, n_4, krok, file4);
    rlc(I_0, Q_0, w_v2, R, L, C, n_4, krok, file4);
    rlc(I_0, Q_0, w_v3, R, L, C, n_4, krok, file4);
    rlc(I_0, Q_0, w_v4, R, L, C, n_4, krok, file4);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    return 0;
}