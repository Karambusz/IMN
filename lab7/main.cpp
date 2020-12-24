#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>

const double delta = 0.01;
const double ro = 1.0;
const double mu = 1.0;
const int nx = 200;
const int ny = 90;
const int i_1 = 50;
const int j_1 = 55;
const int IT_MAX = 20000;


void WB_psi (double (&psi)[nx+1][ny+1], const double qwe, const double qwy, double x[nx+1], double y[ny+1]) {
    // A
    for (int j = j_1; j <= ny; j++) {
        psi[0][j] = (qwe/(2.0*mu)) * ( (pow(y[j], 3)/3.0) -  (pow(y[j], 2)/2.0)*(y[j_1] + y[ny]) + y[j] * y[j_1] * y[ny] );
    }
    // C
    for (int j = 0; j <= ny; j++) {
        psi[nx][j] = (qwy/(2.0*mu)) * ( (pow(y[j], 3)/3.0) -  (pow(y[j], 2)/2.0) * y[ny] ) + ( qwe * pow(y[j_1], 2) * (-y[j_1] + 3.0 * y[ny]) ) / (12.0 * mu);
    }
    // B 
    for (int i = 1; i <= nx-1; i++) {
        psi[i][ny] = psi[0][ny];
    }
    //D
    for (int i = i_1; i <= nx-1; i++) {
        psi[i][0] = psi[0][j_1];
    }
    //E    
    for (int j = 1; j <= j_1; j++) {
        psi[i_1][j] = psi[0][j_1];
    }
    //F
    for (int i = 1; i <= i_1; i++) {
        psi[i][j_1] = psi[0][j_1];
    }
}

void WB_dzeta(double (&dzeta)[nx+1][ny+1], double psi[nx+1][ny+1], const double qwe, const double qwy, double x[nx+1], double y[ny+1]) {
    //A
    for (int j = j_1; j <= ny; j++) {
        dzeta[0][j] = (qwe/(2.0*mu)) * (2.0 * y[j]  - y[j_1] - y[ny]);
    }
    //C
    for (int j = 0; j <= ny; j++) {
        dzeta[nx][j] = (qwy/(2.0*mu)) * (2.0 * y[j] - y[ny]);
    }
    //B
    for (int i = 1; i <= nx-1; i++) {
        dzeta[i][ny] = (2.0/pow(delta, 2)) * (psi[i][ny-1] - psi[i][ny]);
    }
    //D
    for (int i = i_1 + 1; i <= nx-1; i++)   
        dzeta[i][0] = (2.0/pow(delta, 2)) * (psi[i][1] - psi[i][0]);
    }
    //E
    for (int j = 1; j <= j_1-1; j++) {
        dzeta[i_1][j] = (2.0/pow(delta, 2)) * (psi[i_1 + 1][j] - psi[i_1][j]);
    }
    //F
    for (int i = 1; i <= i_1; i++) {
        dzeta[i][j_1] = (2.0/pow(delta, 2)) * (psi[i][j_1 + 1] - psi[i][j_1]);
    }
    dzeta[i_1][j_1] = (1.0/2.0) * (dzeta[i_1 - 1][j_1] + dzeta[i_1][j_1 - 1]);
}


void relaksacja(const double qwe, double x[nx+1], double y[ny+1], FILE *file1, FILE *file2,FILE *file3, FILE *file4) {
    double qwy = qwe * ( ( pow(y[ny], 3) - pow(y[j_1], 3) - 3.0 * y[j_1] * pow(y[ny], 2) + 3.0 * pow(y[j_1],2) * y[ny]) / (pow(y[ny],3)) );
    double psi[nx+1][ny+1] = {};
    double dzeta[nx+1][ny+1] = {};
    double u[nx+1][ny+1] = {};
    double v[nx+1][ny+1] = {};


    WB_psi(psi, qwe, qwy, x, y);
    double omega = 0.0;
    


    for (int it = 1; it < IT_MAX; it++) {
        if (it < 2000) {
            omega = 0.0;
        } else {
            omega = 1.0;
        }

        for (int i = 1; i <= nx-1; i++) {
            for (int j = 1; j <= ny-1; j++) {
                if (i > i_1 || j > j_1) {
                    psi[i][j] = (1.0/4.0) * (psi[i+1][j] + psi[i-1][j] + psi[i][j+1] + psi[i][j-1] - pow(delta, 2) * dzeta[i][j]);
                    dzeta[i][j] = (1.0/4.0) * (dzeta[i+1][j] + dzeta[i-1][j] + dzeta[i][j+1] + dzeta[i][j-1]) - omega * (ro/(16.0*mu)) * ( (psi[i][j+1] - psi[i][j-1]) * (dzeta[i+1][j] - dzeta[i-1][j]) - (psi[i+1][j] - psi[i-1][j])*(dzeta[i][j+1] - dzeta[i][j-1]) );
                }
                u[i][j] = (psi[i][j+1] - psi[i][j-1]) / (2.0 * delta);
                v[i][j] = -(psi[i+1][j] - psi[i-1][j]) / (2.0 * delta);
            }
        }



        WB_dzeta(dzeta, psi, qwe, qwy, x, y);

        double gamma = 0.0;
        for (int i = 1; i<= nx-1; i++) {
            gamma += (psi[i+1][j_1 + 2] + psi[i-1][j_1+2] + psi[i][j_1+3] + psi[i][j_1+1] - 4.0 * psi[i][j_1+2] - pow(delta,2) * dzeta[i][j_1+2]); 
        }

        if (it%1000 == 0) {
            printf("it = %d Q = %g gamma = %g \n",it, qwe, gamma);
        }
        

    } 
    for (int i = 0; i <= nx; i++){
        for (int j = 0; j <= ny; j++) {
            fprintf(file1, "%g ", psi[i][j]);
            fprintf(file2, "%g ", dzeta[i][j]);
            fprintf(file3, "%g ", u[i][j]);
            fprintf(file4, "%g ", v[i][j]);
        }
        fprintf(file1, "\n");
        fprintf(file2, "\n");
        fprintf(file3, "\n");
        fprintf(file4, "\n");
    }   
}

int main() {

    FILE *file1;
	    file1 = fopen("psi_-1000.dat", "w");
    FILE *file2;
	    file2 = fopen("dzeta_-1000.dat", "w");
    FILE *file3;
	    file3 = fopen("u_-1000.dat", "w");
    FILE *file4;
	    file4 = fopen("v_-1000.dat", "w");

    FILE *file5;
	    file5 = fopen("psi_-4000.dat", "w");
    FILE *file6;
	    file6 = fopen("dzeta_-4000.dat", "w");
    FILE *file7;
	    file7 = fopen("u_-4000.dat", "w");
    FILE *file8;
	    file8 = fopen("v_-4000.dat", "w");

    FILE *file9;
	    file9 = fopen("psi_4000.dat", "w");
    FILE *file10;
	    file10 = fopen("dzeta_4000.dat", "w");
    FILE *file11;
	    file11 = fopen("u_4000.dat", "w");
    FILE *file12;
	    file12 = fopen("v_4000.dat", "w");

    double x[nx+1] = {};
    double y[ny+1] = {};

    for (int i = 0; i <= nx; i++) {
        x[i]=  delta * i;
    }

    for (int j = 0; j <= ny; j++) {
        y[j] = delta * j;
    }
    const double Q1 = -1000.0;
    const double Q2 = -4000.0;
    const double Q3 = 4000.0;

    relaksacja(Q1, x, y, file1, file2, file3, file4);
    relaksacja(Q2, x, y, file5, file6, file7, file8);
    relaksacja(Q3, x, y, file9, file10, file11, file12);


    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);
    fclose(file6);
    fclose(file7);
    fclose(file8);  
    fclose(file9);
    fclose(file10);
    fclose(file11);
    fclose(file12);

    return 0;
}