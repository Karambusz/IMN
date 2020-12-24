#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <thread>

const double epsilon = 1.0;
const double delta = 0.1;
const int n_x = 150;
const int n_y = 100;
const double V_1  = 10.0;
const double V_2 = 0.0;
const double xmax = delta * n_x;
const double ymax = delta * n_y;
const double sigmax = 0.1 * xmax;
const double sigmay = 0.1 * ymax;

double ro1(const double x, const double y) {
    return (1.0) * exp( - ( (pow( x - 0.35 * xmax, 2) / pow(sigmax, 2))) - (pow( y - 0.5 * ymax, 2 ) / pow(sigmay, 2) ));
}

double ro2(const double x, const double y) {
    return (-1.0) * exp( - ( ( pow( x - 0.65 * xmax, 2) / pow(sigmax, 2))) - (pow( y - 0.5 * ymax, 2 ) / pow(sigmay, 2) ));
}

double ro(const double x, const double y) {
    return ro1(x, y) + ro2(x, y);
}

void relaksacja_globalna(const double wg, const double TOL, FILE *file1, FILE *file2) {
    double vs[n_x + 1][n_y + 1] = {};
    double vn[n_x + 1][n_y + 1] = {};
    double p[n_x + 1][n_y + 1] = {};
    double st = 0.0;
    double st_1 = 0.0;
    int it = 0;

    for (int i = 0; i <= n_x; i++) {
        for (int j = 0; j <= n_y; j++) {
            p[i][j] = ro(delta * i, delta * j);
        }            
    }

    for (int i = 0; i <= n_x; i++) {
        vs[i][0] = V_1;
        vn[i][0] = V_1;
        vs[i][n_y] = V_2;
        vn[i][n_y] = V_2;
    }

    do {
        for (int i = 1; i <= n_x - 1; i++) { 
            for (int j = 1; j <= n_y - 1; j++) {
               vn[i][j] = (1.0/4.0) * ( vs[i+1][j] + vs[i-1][j] + vs[i][j+1] + vs[i][j-1] + (pow(delta,2)/epsilon)*p[i][j] );  
            }
        }

        for (int j = 1; j <= n_y - 1; j++) {
            vn[0][j] = vn[1][j];
            vn[n_x][j] = vn[n_x - 1][j];
        }


        for (int i = 0; i <= n_x; i++) {
            for (int j = 0; j <= n_y; j++) {
                vs[i][j] = ((1.0 - wg ) * vs[i][j]) + (wg * vn[i][j]);
            }
        }

        st_1 = st;
        st = 0.0;
        for (int i = 0; i <= n_x - 1; i++) {
            for (int j = 0; j <= n_y - 1; j++)  {
                st += pow(delta, 2) * (0.5 * pow((vs[i + 1][j] - vs[i][j]) / (delta), 2) + 0.5 * pow((vs[i][j + 1] - vs[i][j]) / (delta), 2) - p[i][j] * vs[i][j]);
            }
        } 
        fprintf(file1, "%d %g \n", it, st);
        it++;        
    } while (fabs((st - st_1)/st_1) > TOL);

    double error[n_x + 1][n_y + 1] = {};

    for (int i = 1; i <= n_x - 1; i++) {
        for (int j = 1; j <= n_y - 1; j++) {
            error[i][j] = ( (vn[i+1][j] - 2*vn[i][j] + vn[i-1][j]) / (pow(delta,2)) ) + ( (vn[i][j+1] - 2*vn[i][j] + vn[i][j-1]) / (pow(delta,2)) ) + (p[i][j]/epsilon);
            fprintf(file2, "%g  ", error[i][j]);
            }
        fprintf(file2, "\n");
    }   
}

void relaksacja_lokalna(const double wl, const double TOL, FILE *file1) {
    double v[n_x + 1][n_y + 1] = {}; 
    double p[n_x + 1][n_y + 1] = {};
    double st = 0.0;
    double st_1 = 0.0;
    int it = 0; 

    for (int i = 0; i <= n_x; i++) {
        for (int j = 0; j <= n_y; j++) {
            p[i][j] = ro(delta * i, delta * j);
        }            
    }

    for (int i = 0; i <= n_x; i++) {
        v[i][0] = V_1;
        v[i][n_y] = V_2;
    } 

    do {
        for (int i = 1; i <= n_x - 1; i++) { 
            for (int j = 1; j <= n_y - 1; j++) {
               v[i][j] = (1 - wl) * v[i][j] + (wl/4.0) * ( v[i+1][j] + v[i-1][j] + v[i][j+1] + v[i][j-1] + (pow(delta,2)/epsilon)*p[i][j] ); 
            }
        }

        for (int j = 1; j <= n_y - 1; j++) {
            v[0][j] = v[1][j];
            v[n_x][j] = v[n_x - 1][j];
        }

        st_1 = st;
        st = 0.0;
        for (int i = 0; i <= n_x - 1; i++) {
            for (int j = 0; j <= n_y - 1; j++)  {
                st += pow(delta, 2) * (0.5 * pow((v[i + 1][j] - v[i][j]) / (delta), 2) + 0.5 * pow((v[i][j + 1] - v[i][j]) / (delta), 2) - p[i][j] * v[i][j]);
            }
        } 
        fprintf(file1, "%d %g \n", it, st);
        it++;        
    } while (fabs((st - st_1)/st_1) > TOL);

}

int main() {

    FILE *file1;
	    file1 = fopen("relaksacja_globalna_0.6.dat", "w");
    FILE *file2;
	    file2 = fopen("relaksacja_globalna_1.0.dat", "w");
    FILE *file3;
	    file3 = fopen("mapa_relaksacja_globalna_0.6.dat", "w");
    FILE *file4;
	    file4 = fopen("mapa_relaksacja_globalna_1.0.dat", "w");
    FILE *file5;
	    file5 = fopen("relaksacja_lokalna_1.0.dat", "w");
    FILE *file6;
	    file6 = fopen("relaksacja_lokalna_1.4.dat", "w");
    FILE *file7;
	    file7 = fopen("relaksacja_lokalna_1.8.dat", "w");
    FILE *file8;
	    file8 = fopen("relaksacja_lokalna_1.9.dat", "w");


    
    const double wg1 = 0.6;
    const double wg2 = 1.0;
    const double wl1 = 1.0;
    const double wl2 = 1.4;
    const double wl3 = 1.8;
    const double wl4 = 1.9;
    const double TOL = pow(10, -8);

    std::thread tg1 {relaksacja_globalna, wg1, TOL, file1, file3};
    std::thread tg2 {relaksacja_globalna, wg2, TOL, file2, file4};
    std::thread tl1 {relaksacja_lokalna, wl1, TOL, file5};
    std::thread tl2 {relaksacja_lokalna, wl2, TOL, file6};
    std::thread tl3 {relaksacja_lokalna, wl3, TOL, file7};
    std::thread tl4 {relaksacja_lokalna, wl4, TOL, file8};

    tg1.join();
    tg2.join();
    tl1.join();
    tl2.join();
    tl3.join();
    tl4.join();

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