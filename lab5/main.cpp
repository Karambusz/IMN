#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;
const double delta = 0.2;
const int n_x = 128;
const int n_y = 128;
const double xmax = delta * n_x;
const double ymax = delta *n_y;


void relaksacja (double (&v)[n_x + 1][n_y + 1], const int k, int &it, double &st, double &st_1, const double TOL, FILE *file1, FILE *file2) {
   do {
        for (int i = k; i <= n_x - k; i += k) {
            for (int j = k; j <= n_y - k; j += k) {
                v[i][j] = (1.0/4.0) *  (v[i+k][j] + v[i-k][j] + v[i][j+k] + v[i][j-k]); 
            }
        }

        st_1 = st;
        st = 0.0;
        for (int i = 0; i <= n_x - k; i+=k) {
            for (int j = 0; j <= n_y - k; j+=k) {
                st+= ( (pow(k*delta, 2)) / 2.0 ) * ( (  pow(( (v[i+k][j] - v[i][j])/(2.0 * k * delta) ) +  ( (v[i+k][j+k] - v[i][j+k]) / (2.0 * k * delta) ), 2) ) + (  pow(( (v[i][j+k] - v[i][j])/(2.0 * k * delta) ) +  ( (v[i+k][j+k] - v[i+k][j]) / (2.0 * k * delta) ), 2) )  );
            }
        }
        fprintf(file1, "%d %g \n", it, st);
        printf("%d %g \n", it, st);
        it++;
   } while (fabs((st - st_1)/st_1) > TOL);

   printf("\n\n\n");

    if (k != 1) {
        for (int i = 0; i <= n_x - k; i += k) {
            for (int j = 0; j <= n_y - k; j += k) {
                v[i + (k / 2)][j + (k / 2)] = (1.0/4.0) * (v[i][j] + v[i + k][j] + v[i][j + k] + v[i + k][j + k]);
                if (i != (n_x - k))
                v[i + k][j + (k / 2)] = (1.0/2.0) * (v[i + k][j] + v[i + k][j + k]);
                if (j != (n_y-k))
                v[i + (k / 2)][j + k] = (1.0/2.0) * (v[i][j + k] + v[i + k][j + k]);
                if ( j != 0)
                v[i + (k / 2)][j] = (1.0/2.0) * (v[i][j] + v[i + k][j]);
                if ( i != 0)
                v[i][j + (k / 2)] = (1.0/2.0) * (v[i][j] + v[i][j + k]);
            }
        }
    }

    for (int i = 0; i <= n_x; i += k) {
        for (int j = 0; j <= n_y; j += k) {
            fprintf(file2, "%g ", v[i][j]);
        }
        fprintf(file2, "\n");
    }
}

int main() {
     FILE *file1;
	    file1 = fopen("relaksacja_k.dat", "w");
    FILE *file2;
	    file2 = fopen("mapa_relaksacja_k_16.dat", "w");
    FILE *file3;
	    file3 = fopen("mapa_relaksacja_k_8.dat", "w");
    FILE *file4;
	    file4 = fopen("mapa_relaksacja_k_4.dat", "w");
    FILE *file5;
	    file5 = fopen("mapa_relaksacja_k_2.dat", "w");
    FILE *file6;
	    file6 = fopen("mapa_relaksacja_k_1.dat", "w");
    const int k1 = 16;
    const int k2 = 8;
    const int k3 = 4;
    const int k4 = 2;
    const int k5 = 1;
    const double TOL = pow(10, -8);
    int iterator = 0;
    double st = 0.0;
    double st_1 = 0.0;

    double v[n_x + 1][n_y + 1] = {};

    for (int y = 0; y <= n_x; y++) {
        v[0][y] = (1.0) * sin(PI * (y*delta/ymax));
        v[y][n_y] = (-1.0) * sin(2.0*PI * (y*delta/xmax));
        v[n_x][y] = (1.0) * sin(PI * (y*delta/ymax));
        v[y][0] = (1.0) * sin(2.0*PI * (y*delta/xmax));
    }

    relaksacja(v,k1, iterator, st, st_1, TOL, file1, file2);
    relaksacja(v,k2, iterator, st, st_1, TOL, file1, file3);
    relaksacja(v,k3, iterator, st, st_1, TOL, file1, file4);
    relaksacja(v,k4, iterator, st, st_1, TOL, file1, file5);
    relaksacja(v,k5, iterator, st, st_1, TOL, file1, file6);


    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);
    fclose(file6);


    return 0;
}