#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>


const int nx = 40;
const int ny = 40;
const int N = (nx + 1) * (ny + 1);
const double delta = 1.0;
const double deltaT = 1.0;
const int Ta = 40;
const int Tb = 0;
const int Tc = 30;
const int Td = 0;
const double kb = 0.1;
const double kd = 0.6;
const int IT_MAX = 2000;

int l(const int i, const int j) {
    return i + j * (nx + 1);
}



void create_A_B_C_T(gsl_matrix *a, gsl_matrix *b, gsl_vector *c, gsl_vector *T) {
    for (int i = 1; i <= nx-1; i++) {
        for (int j = 1; j <= ny-1; j++) {
            gsl_matrix_set(a, l(i,j), l(i,j) - nx - 1, deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(a, l(i,j), l(i,j) - 1, deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(a, l(i,j), l(i,j) + 1, deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(a, l(i,j), l(i,j) + nx + 1, deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(a, l(i,j), l(i,j), -((2.0*deltaT)/pow(delta,2)) - 1.0);

            gsl_matrix_set(b, l(i,j), l(i,j)-nx-1, -deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(b, l(i,j), l(i,j)-1,    -deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(b, l(i,j), l(i,j)+1,    -deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(b, l(i,j), l(i,j)+nx+1, -deltaT / (2.0*pow(delta, 2)));
            gsl_matrix_set(b, l(i,j), l(i,j),      (2.0*deltaT)/(pow(delta,2)) - 1.0);
        }
    }

    for (int j = 0; j <= ny; j++) {
        gsl_matrix_set(a, l(0, j), l(0,j), 1.0);
        gsl_matrix_set(a, l(nx, j), l(nx,j), 1.0);

        gsl_matrix_set(b, l(0, j), l(0,j), 1.0);
        gsl_matrix_set(b, l(nx, j), l(nx,j), 1.0);
        

        gsl_vector_set(c, l(0, j), 0.0);
        gsl_vector_set(c, l(nx, j), 0.0);

        gsl_vector_set(T, l(0, j), Ta);
        gsl_vector_set(T, l(nx, j), Tc);
    }


    for(int i = 1; i <= nx - 1; i++) {
        gsl_matrix_set(a, l(i, ny), l(i, ny) - nx - 1, -1.0/(kb * delta));
        gsl_matrix_set(a, l(i, ny), l(i, ny), 1.0 + 1.0/(kb * delta));
        gsl_vector_set(c, l(i, ny), Tb);

        gsl_matrix_set(a, l(i, 0), l(i, 0), 1.0 + 1.0/(kd * delta));
        gsl_matrix_set(a, l(i, 0), l(i, 0) + nx + 1, -1.0/(kd * delta));
        gsl_vector_set(c, l(i, 0), Td);
    }

    for (int j = 0; j < N; j++) {
        for(int i = 1; i <= nx-1; i++) {
        gsl_matrix_set(b, l(i, ny), j, 0.0);
        gsl_matrix_set(b, l(i, 0), j, 0.0);
        }
    }

    for(int i = 1; i <= nx-1; i++){
        for(int j = 0; j <= ny; j++)
        gsl_vector_set(T, l(i, j), 0.0);
    }
}

void CN(FILE *file1, FILE *file2) {
    gsl_matrix *a = gsl_matrix_calloc(N, N);
    gsl_matrix *b = gsl_matrix_calloc(N, N);
    gsl_vector *c = gsl_vector_calloc(N);
    gsl_vector *d = gsl_vector_calloc(N);
    gsl_vector *T = gsl_vector_calloc(N);

    create_A_B_C_T(a, b, c, T);

    gsl_permutation* p = gsl_permutation_calloc(N);
    int signum = 0;
    gsl_linalg_LU_decomp(a, p, &signum);

    for (int it = 1; it <= IT_MAX; it++ ) {
        gsl_blas_dgemv(CblasNoTrans, 1, b, T, 0, d);
        gsl_blas_daxpy(1, c, d);
        gsl_linalg_LU_solve(a, p, d, T);    
            if (it == 100 || it == 200 || it == 500 || it == 1000 || it == 2000){
            for (int i = 1; i <= nx - 1; i++){
                for (int j = 1; j <= ny - 1; j++){
                    fprintf(file1, "%g ", gsl_vector_get(T, l(i,j)) );
                    double tmp = ((gsl_vector_get(T, l(i,j) + 1) - 2.0*gsl_vector_get(T, l(i,j)) + gsl_vector_get(T, l(i,j)-1))/pow(delta, 2)) + ((gsl_vector_get(T, l(i,j) + nx + 1) - 2.0*gsl_vector_get(T, l(i,j)) + gsl_vector_get(T, l(i,j)- nx -1) )/pow(delta, 2));
                    fprintf(file2, "%g ", tmp );
                }
                fprintf(file1, "\n");
                fprintf(file2, "\n");
            }
                fprintf(file1, "\n");
                fprintf(file2, "\n");
        }
    }


    gsl_matrix_free(a);
    gsl_matrix_free(b);
    gsl_vector_free(c);
    gsl_vector_free(d);
    gsl_vector_free(T);
    gsl_permutation_free(p);
}



int main() {
    FILE *file1;
	    file1 = fopen("T.dat", "w");
    FILE *file2;
	    file2 = fopen("nablaT.dat", "w");

    CN(file1, file2);

    fclose(file1);
    fclose(file2);

    
    return 0;
}