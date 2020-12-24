#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "mgmres.c"
#include "mgmres.h"

const double delta = 0.1;

double ro1(const double x, const double y, const double xmax, const double ymax, const double sigma) {
    return (1.0) * exp( - ( (pow( x - 0.25 * xmax, 2) / pow(sigma, 2))) - (pow( y - 0.5 * ymax, 2 ) / pow(sigma, 2) ));
}

double ro2(const double x, const double y, const double xmax, const double ymax, const double sigma) {
    return (-1.0) * exp( - ( ( pow( x - 0.75 * xmax, 2) / pow(sigma, 2))) - (pow( y - 0.5 * ymax, 2 ) / pow(sigma, 2) ));
}

double epsilon(const int l, const double epsilon1, const double epsilon2, const int n_x) {
    int j = (l/(n_x + 1));
    int i = l - (j * (n_x + 1));
    if (i<=n_x/2) {
        return epsilon1;
    } else {
        return epsilon2; 
    }
}

void poisson(const int n_x, const int n_y,const double epsilon1, const double epsilon2, const double V1, const double V2, const double V3, const double V4, const bool ro,FILE *file1, FILE *file2, FILE *file3) {
    const double xmax = n_x * delta;
    const double ymax = n_y * delta;
    const double sigma = xmax/10.0;

    const int N = (n_x + 1) * (n_y + 1);
    double a[5 * N] = {};
    int ja[5 * N] = {};
    int ia[N + 1] = {};

    for (int i = 0; i < N + 1; i++) {
        ia[i] = -1;
    }
            
    double b[N] = {};
    double V[N] = {};

    

    fprintf(file1, "Wyniki dla nx = %d, ny = %d \n", n_x, n_y);
    fprintf(file2, "Wyniki dla nx = %d, ny = %d \n", n_x, n_y);
    int k = -1;
    for (int l = 0; l < N; l++) {
        int brzeg = 0;
        double vb = 0.0;
        int j = (l/(n_x + 1));
        int i = l - (j * (n_x + 1));

        if (i == 0) {
            brzeg = 1;
            vb = V1;
        }

        if (j == n_y) {
            brzeg = 1;
            vb = V2;
        }

        if (i == n_x) {
            brzeg = 1;
            vb = V3;
        }

        if (j == 0) {
            brzeg = 1;
            vb = V4;
        }

        if(ro) {
            b[l] = -(ro1(i*delta, j*delta, xmax, ymax,sigma) + ro2(i*delta, j*delta, xmax, ymax,sigma));
        } else {
            b[l] = 0.0;
        }
        

        if (brzeg == 1) {
            b[l] = vb;
        }

        ia[l] = -1;

        if (l- n_x -1 >= 0 && brzeg == 0) {
            k++;
            if(ia[l] < 0) {
                ia[l] = k;
            }
            a[k] = epsilon(l, epsilon1, epsilon2, n_x) / pow(delta,2);
            ja[k] = l - n_x - 1;
        }

        if (l - 1 >= 0 && brzeg == 0) {
            k++;
            if(ia[l] < 0) {
                ia[l] = k;
            }
            a[k] = epsilon(l, epsilon1, epsilon2, n_x)  / pow(delta,2);
            ja[k] = l - 1;
        }

        k++;
        if(ia[l] < 0) {
            ia[l] = k;
        }
        if(brzeg == 0) {
            a[k] = -(2*epsilon(l, epsilon1, epsilon2, n_x) + epsilon(l+1, epsilon1, epsilon2, n_x) + epsilon(l+ n_x + 1, epsilon1, epsilon2, n_x)) / (pow(delta,2));
        } else {
            a[k] = 1.0;
        }
        ja[k] = l;


        if(l < N && brzeg == 0) {
            k++;
            a[k] = epsilon(l+1, epsilon1, epsilon2, n_x) / (pow(delta,2));
            ja[k] = l+1;
        }

        if (l < (N - n_x - 1) && brzeg ==0) {
            k++;
            a[k] = epsilon(l + n_x + 1, epsilon1, epsilon2, n_x) / (pow(delta,2));
            ja[k] = l + n_x + 1;
        }

        if (a[l] != 0) {
            fprintf(file1, "%d %d %d  %g \n",l,i,j, a[l]);
        }

        if (b[l] != 0) {
            fprintf(file2, "%d %d %d %g \n", l, i, j, b[l]);
        }
    }
    fprintf(file1, "\n \n");
    fprintf(file2, "\n \n");

    int nz_num = k + 1;
    ia[N] = nz_num;

    const int itr_max = 500;
    const int mr = 500;
    const double tot_abs = pow(10, -8);
    const double tol_rel = pow(10, -8);
    pmgmres_ilu_cr(N, nz_num, ia, ja, a, V, b, itr_max, mr, tot_abs, tol_rel);


    if (n_x != 4) {
        for (int l = 0; l < N; l++) {
            fprintf(file3, "%g ", V[l]);
            if ( (l+1)%(n_x + 1)  == 0) {
                fprintf(file3, "\n");
            }
        }
    }

}

int main() {

    //nx, ny, eps1, eps2, v1, v2, v3, v4, file1 - a,file2 -  b, file3 - mapa
    FILE *file1;
	    file1 = fopen("macierz_a.dat", "w");
    FILE *file2;
	    file2 = fopen("wektor_b.dat", "w");
    FILE *file3;
	    file3 = fopen("mapa_50.dat", "w");
    FILE *file4;
	    file4 = fopen("mapa_100.dat", "w");
    FILE *file5;
	    file5 = fopen("mapa_200.dat", "w");
    const int n_x1 = 4;
    const int n_y1 = 4;
    const int n_x2 = 50;
    const int n_y2 = 50;
    const int n_x3 = 100;
    const int n_y3 = 100;
    const int n_x4 = 200;
    const int n_y4 = 200;
    const double eps1_1 = 1.0;
    const double eps2_1 = 1.0;
    const double V1_1 = 10.0;
    const double V2_1 = -10.0;
    const double V3_1 = 10.0;
    const double V4_1 = -10.0;
    bool ro1 = false;
    poisson(n_x1, n_y1, eps1_1, eps2_1, V1_1, V2_1, V3_1, V4_1, ro1, file1, file2, file3);


    FILE *file6;
	    file6 = fopen("mapa_1_1.dat", "w");
    FILE *file7;
	    file7 = fopen("mapa_1_2.dat", "w");
    FILE *file8;
	    file8 = fopen("mapa_1_10.dat", "w");

    poisson(n_x2, n_y2, eps1_1, eps2_1, V1_1, V2_1, V3_1, V4_1, ro1, file1, file2, file3);
    poisson(n_x3, n_y3, eps1_1, eps2_1, V1_1, V2_1, V3_1, V4_1, ro1, file1, file2, file4);
    poisson(n_x4, n_y4, eps1_1, eps2_1, V1_1, V2_1, V3_1, V4_1, ro1, file1, file2, file5);


    const double V1_2 = 0.0;
    const double V2_2 = 0.0;
    const double V3_2 = 0.0;
    const double V4_2 = 0.0; 
    bool ro2 = true;

    const double eps1_2 = 1.0;
    const double eps2_2 = 2.0;

    const double eps1_3 = 1.0;
    const double eps2_3 = 10.0;

    poisson(n_x3, n_y3, eps1_1, eps2_1, V1_2, V2_2, V3_2, V4_2, ro2, file1, file2, file6);
    poisson(n_x3, n_y3, eps1_2, eps2_2, V1_2, V2_2, V3_2, V4_2, ro2, file1, file2, file7);
    poisson(n_x3, n_y3, eps1_3, eps2_3, V1_2, V2_2, V3_2, V4_2, ro2, file1, file2, file8);


    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);
    fclose(file6);
    fclose(file7);
    fclose(file8);

    return 0;
}