#include <stdio.h>
#include <stdlib.h>
#include <cmath>

const int nx = 150;
const int nt = 1000;
const double delta = 0.1;
const double deltaT = 0.05;
const double xA = 7.5;
const double sigma = 0.5;
const double xF = 2.5;
const double tmax = deltaT * nt;

double delta_kroneckera(const double x) {
    return  fabs(x - xF) < pow(10, -8)  ? 1 : 0;
} 

double aF(const double x, const double t) {
    return cos((50.0 * t) / tmax) * delta_kroneckera(x);
}

void verleta (const double beta, const double alfa, FILE * file1, FILE * file2) {
    double u0[nx+1] = {};
    double u [nx+1] = {};
    double v [nx+1] = {};
    double vp[nx+1] = {};
    double a [nx+1] = {};
    double E = 0;

    if (beta != 1.0 || alfa != 1.0) {
        for (int i = 1; i < nx; i++) {
            u[i] = exp (- (pow((i * delta) - xA, 2) / (2.0* pow(sigma,2))));
        }
    }

    for (int i = 0; i <= nx; i++) {
        u0[i] = u[i];
    } 

    for (int i = 1; i < nx; i++) {
        a[i] = (u[i+1] - 2.0 * u[i] + u[i-1]) / (pow(delta,2)) - beta * ( (u[i] - u0[i]) / deltaT) + alfa * aF(delta * i, 0);
    }

    for (int n = 1; n <= nt; n++) {
        for (int i = 1; i < nx; i++) {
            vp[i] = v[i] + (deltaT/2.0)*a[i];
            u0[i] = u[i];
            u[i] = u[i] + deltaT * vp[i];
        }
        for (int i = 1; i < nx; i++) {
            a[i] = (u[i+1] - 2.0 * u[i] + u[i-1]) / (pow(delta,2)) - beta * ( (u[i] - u0[i]) / deltaT) + alfa * aF(delta * i, deltaT * n);
            v[i] = vp[i] + (deltaT/2.0)*a[i];
        }
        E = (delta / 4.0) * ( pow((u[1] - u[0])/delta, 2) + pow((u[nx] - u[nx-1])/delta, 2));
        double tmp = 0;
        for (int i = 1; i <= nx - 1; i++) {
            tmp += delta/2.0 * (pow(v[i],2) + ( pow((u[i+1] - u[i-1])/(2.0*delta), 2)));
        }
        E += tmp;
        fprintf(file1, "%g %g \n",deltaT * n, E);
        for (int i = 0; i <= nx; i++) {
            fprintf(file2, "%g ", u[i]);
        }
        fprintf(file2, "\n");
    } 
    fprintf(file1, "\n"); 
}


int main() {
    FILE *file1;
	    file1 = fopen("E.dat", "w");
    FILE *file2;
	    file2 = fopen("mapa1.dat", "w");
    FILE *file3;
	    file3 = fopen("mapa2.dat", "w");
    FILE *file4;
	    file4 = fopen("mapa3.dat", "w");
    FILE *file5;
	    file5 = fopen("E_1.dat", "w");
    FILE *file6;
	    file6 = fopen("mapa4.dat", "w");
    const double beta1 = 0.0;
    const double beta2 = 0.1;
    const double beta3 = 1.0;
    const double alfa = 0.0;
    const double alfa1 = 1.0;

    verleta(beta1, alfa, file1, file2);
    verleta(beta2, alfa, file1, file3);
    verleta(beta3, alfa, file1, file4);
    verleta(beta3, alfa1, file5, file6);
    

    fclose(file1);
    fclose(file2);  
    fclose(file3); 
    fclose(file4);
    fclose(file5); 
    fclose(file6);    

    return 0;
}