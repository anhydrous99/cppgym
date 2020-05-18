#include "AcrobotCPP.h"

// From https://people.sc.fsu.edu/~jburkardt/cpp_src/rk4/rk4.html
// A modification, instead of having a function pointer as a way to bring in the function to approximate the
// ODE. It instead takes in a functon class. Modified May, 18 2020.

void rk4(const std::function<void (float, const float*, float*)> &dydt, const float tspan[2],
         const float y0[], int n, int m, float t[], float y[])
//****************************************************************************80
//
//  Purpose:
//
//    rk4 approximates an ODE using a Runge-Kutta fourth order method.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    22 April 2020
//
//  Author:
//
//    John Burkardt
//
//  Input:
//
//    float DYDT ( float T, float U ), a function which evaluates
//    the derivative, or right hand side of the problem.
//
//    float TSPAN[2]: the initial and final times
//
//    float Y0[M]: the initial condition
//
//    int N: the number of steps to take.
//
//    int M: the number of variables.
//
//  Output:
//
//    float t[n+1], y[(n+1)*m]: the times and solution values.
//
{
    float dt;
    float *f0;
    float *f1;
    float *f2;
    float *f3;
    int i;
    int j;
    float t0;
    float t1;
    float t2;
    float t3;
    float *u0;
    float *u1;
    float *u2;
    float *u3;

    f0 = new float[m];
    f1 = new float[m];
    f2 = new float[m];
    f3 = new float[m];
    u0 = new float[m];
    u1 = new float[m];
    u2 = new float[m];
    u3 = new float[m];

    dt = (tspan[1] - tspan[0]) / (float) (n);

    j = 0;
    t[0] = tspan[0];
    for (i = 0; i < m; i++) {
        y[i + j * m] = y0[i];
    }

    for (j = 0; j < n; j++) {
        t0 = t[j];
        for (i = 0; i < m; i++) {
            u0[i] = y[i + j * m];
        }
        dydt(t0, u0, f0);

        t1 = t0 + dt / 2.0f;
        for (i = 0; i < m; i++) {
            u1[i] = u0[i] + dt * f0[i] / 2.0f;
        }
        dydt(t1, u1, f1);

        t2 = t0 + dt / 2.0f;
        for (i = 0; i < m; i++) {
            u2[i] = u0[i] + dt * f1[i] / 2.0f;
        }
        dydt(t2, u2, f2);

        t3 = t0 + dt;
        for (i = 0; i < m; i++) {
            u3[i] = u0[i] + dt * f2[i];
        }
        dydt(t3, u3, f3);

        t[j + 1] = t[j] + dt;
        for (i = 0; i < m; i++) {
            y[i + (j + 1) * m] = u0[i] + dt * (f0[i] + 2.0f * f1[i] + 2.0f * f2[i] + f3[i]) / 6.0f;
        }
    }
/*
  Free memory.
*/
    delete[] f0;
    delete[] f1;
    delete[] f2;
    delete[] f3;
    delete[] u0;
    delete[] u1;
    delete[] u2;
    delete[] u3;
}