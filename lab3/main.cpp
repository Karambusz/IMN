#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <functional>
#include <algorithm>


void trapezy (const double x0, const double v0, const double krok, const double alfa, double &xntrapezy, double &vntrapezy) {
    
    double xn1 = x0;
    double vn1 = v0;
    double dx = 0.0;
    double dv = 0.0;
    double a[2][2] = {1.0, -krok/2.0, 0.0, 0.0};
    double F = 0.0;
    double G = 0.0;

    do {
        F = xn1 - x0 - (krok/2.0) * (v0 + vn1);
        G = vn1 - v0 - (krok/2.0) * ( (alfa*(1.0 - pow(x0, 2))*v0 -x0) + (alfa*(1.0 - pow(xn1, 2))*vn1 -xn1));

        a[1][0] = -(krok/2.0) * (-2.0*alfa*xn1*vn1 - 1.0);
        a[1][1] = 1.0 - ( (krok/2.0) * alfa * (1.0 - pow(xn1,2)));

        dx = ( (-F * a[1][1]) - (-G * a[0][1]) ) / (a[0][0] * a[1][1] - a[0][1] *  a[1][0]);
        dv = ( (-G * a[0][0]) - (-F * a[1][0]) ) / (a[0][0] * a[1][1] - a[0][1] *  a[1][0]);

        xn1+=dx;
        vn1+=dv;
    } while ( fabs(dx) > pow(10,-10) && fabs(dv) > pow(10,-10));

    xntrapezy = xn1;
    vntrapezy = vn1;
}

void rk2 (const double x0, const double v0, const double krok, const double alfa, double &xnrk, double &vnrk) {
    double k1x, k1v, k2x, k2v;

    k1x = v0;
    k1v = alfa*(1.0 - pow(x0, 2))*v0 -x0;

    k2x = v0 + krok*k1v;
    k2v = (alfa* (1.0 - pow((x0 + krok*k1x),2) ) * (v0 + krok*k1v)) - (x0 + krok*k1x);

    xnrk = x0 + (krok/2.0)*(k1x + k2x);
    vnrk = v0 + (krok/2.0)*(k1v + k2v);
}


void kontrola(const double x0, const double v0, const double krok1, const double alfa, const double tmax, const double S, const double TOL, const int p, std::function<void(const double, const double, const double, const double, double &, double&)> fun, FILE *file) {

    double xn = x0;
    double vn = v0;
    double xn12, vn12, xn22, vn22, xn21, vn21;
    double Ex = 0.0;
    double Ev = 0.0;
    double t = 0.0;
    double krok = krok1;

    do {
        fun(xn, vn, krok, alfa, xn12, vn12);
        fun(xn12, vn12, krok, alfa, xn22, vn22);

        fun(xn, vn, 2.0*krok, alfa, xn21, vn21);

        Ex = (xn22 - xn21) / (pow(2.0, p) - 1.0);
        Ev = (vn22 - vn21) / (pow(2.0, p) - 1.0);

        double max1 = std::max(fabs(Ex), fabs(Ev));
        if (max1 < TOL) {
            t = t + 2.0*krok;
            xn = xn22;
            vn = vn22;
            fprintf(file, "%g %g %g %g \n", t, krok, xn, vn);
        }
        krok = pow( ((S*TOL) / max1), 1.0/((double)p + 1) ) * krok;

    } while (t < tmax);

}


int main() {
    FILE *file1;
	    file1 = fopen("trapezy_tol_2.dat", "w");
    FILE *file2;
	    file2 = fopen("trapezy_tol_5.dat", "w");
    FILE *file3;
	    file3 = fopen("rk2_tol_2.dat", "w");
    FILE *file4;
	    file4 = fopen("rk2_tol_5.dat", "w");

    const double x0 = 0.01;
    const double v0 = 0.0;
    const double krok = 1.0;
    const double S = 0.75;
    const double tmax = 40.0;
    const int p = 2;
    const double alfa = 5.0;
    const double TOL1 = pow(10, -2);
    const double TOL2 = pow(10, -5);

    kontrola(x0, v0, krok, alfa, tmax, S, TOL1, p, trapezy, file1);
    kontrola(x0, v0, krok, alfa, tmax, S, TOL2, p, trapezy, file2);
    kontrola(x0, v0, krok, alfa, tmax, S, TOL1, p, rk2, file3);
    kontrola(x0, v0, krok, alfa, tmax, S, TOL2, p, rk2, file4);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    return 0;
}