#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>

double PI = 3.14159;

// Reference: Intro to Algorithms by CLRS
double complex *recursive_FFT(double complex *x, int N){

	if(N==1) return x;

	double complex wn = cexp(2*PI*I/N);
	double complex w = 1.0;

	double complex *X = (double complex*)malloc(N*sizeof(double complex));
	double complex *x_even = (double complex*)malloc((N/2)*sizeof(double complex));
	double complex *x_odd = (double complex*)malloc((N/2)*sizeof(double complex));
	for(int i=0; i<(N/2); i++){
		x_even[i] = x[i];
		x_odd[i] = x[i+1];
	}
	double complex *X0 = recursive_FFT(x_even, N/2); 
	double complex *X1 = recursive_FFT(x_odd, N/2); 
		
	for(int k=0; k<(N/2); k++){
		X[k] = X0[k] + w*X1[k];
		X[k + (N/2)] = X0[k] - w*X1[k];
		w = w*wn;
	}
	return X;

}


int main(){
	int i=0, N = pow(2, 3);
	double complex x[] = {1,0,0,0,0,0,0,0};
	double complex *X = recursive_FFT(x, N);

	for(i=0; i<N; i++){
		printf("%lf%+lfi\n", creal(X[i]), cimag(X[i]));
	}

	return 0;
}
