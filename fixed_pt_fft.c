#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

double PI = 3.141592653589793;

int16_t FIX = (1<<7);

struct int_complex{
	int16_t re, im;
};

struct int_complex *fixed_recursive_FFT(struct int_complex *x, int N){

	if(N==1) return x;

	// double complex w = 1.0;
	// double complex wn = cexp(2*PI*I/N);
	struct int_complex w, wn;
	w.re = 1*FIX; w.im = 0;
	wn.re = (int16_t)(cos(-2*PI/N)*FIX); 
	wn.im = (int16_t)(sin(-2*PI/N)*FIX); 

	// double complex *X = (double complex*)malloc(N*sizeof(double complex));
	// double complex *x_even = (double complex*)malloc((N/2)*sizeof(double complex));
	// double complex *x_odd = (double complex*)malloc((N/2)*sizeof(double complex));
	struct int_complex *X = (struct int_complex*)malloc(N*sizeof(struct int_complex));
	struct int_complex *x_even = (struct int_complex*)malloc((N/2)*sizeof(struct int_complex));
	struct int_complex *x_odd = (struct int_complex*)malloc((N/2)*sizeof(struct int_complex));
	int i=0;
	for(i=0; i<(N/2); i++){
		x_even[i] = x[i];
		x_odd[i] = x[i+1];
	}
	// recursive function call
	x_even = fixed_recursive_FFT(x_even, N/2); 
	x_odd = fixed_recursive_FFT(x_odd, N/2); 
	int16_t wr, wi; int k;
	for(k=0; k<(N/2); k++){
		// X[k] = x_even[k] + w*x_odd[k];
		X[k].re = x_even[k].re + (((w.re)*(x_odd[k].re))/FIX) - (((w.im)*(x_odd[k].im))/FIX);
		X[k].im = x_even[k].im + (((w.re)*(x_odd[k].im))/FIX) + (((w.im)*(x_odd[k].re))/FIX);
		// X[k + (N/2)] = x_even[k] - w*x_odd[k];
		X[k+(N/2)].re = x_even[k].re - (((w.re)*(x_odd[k].re))/FIX) + (((w.im)*(x_odd[k].im))/FIX);
		X[k+(N/2)].im = x_even[k].im - (((w.re)*(x_odd[k].im))/FIX) - (((w.im)*(x_odd[k].re))/FIX);
		// w = w*wn;
		wr = (w.re*wn.re)/FIX - (w.im*wn.im)/FIX;
		wi = (w.re*wn.im)/FIX + (w.im*wn.re)/FIX;
		w.re = wr; w.im = wi;
	}
	return X;
}

int main(){
	int i=0, N = pow(2, 6);
	double complex x[] = { // random samples, (generated in python)
		0.34155064+0.47718692*I, -0.9372691 +0.0839553*I ,
		0.59090131-0.79169387*I, -0.52630126+0.00245764*I,
	   -0.31407274+0.85755859*I, -0.08713369-0.00215445*I,
	   -0.94735933-0.99306697*I,  0.59118581-0.13383305*I,
		0.36428754+0.15789499*I,  0.45482109-0.20079545*I,
	   -0.14742903-0.98319177*I, -0.36871847-0.93697043*I,
		0.08764919-0.99304392*I,  0.04381657-0.28778096*I,
		0.91110163+0.46515253*I, -0.24328939-0.46436491*I,
		0.48682587-0.02500917*I, -0.26414735+0.22709436*I,
		0.33793729-0.12342564*I,  0.15014047-0.94276812*I,
	   -0.67086204-0.87605378*I, -0.6518987 +0.99445895*I,
		0.14144934-0.89737475*I,  0.68193048-0.46939642*I,
	   -0.65846689-0.85914305*I,  0.88726076+0.82292328*I,
	   -0.28300467-0.28597436*I,  0.33469704-0.80204147*I,
	   -0.88368581-0.23399495*I, -0.33662485-0.9943176*I ,
	   -0.22102079+0.68637509*I,  0.25515612-0.69044318*I,
	   -0.43742975+0.56201235*I, -0.60554584+0.90751273*I,
		0.43601632-0.05247184*I,  0.34242969+0.8214785*I ,
		0.57253784-0.80182157*I,  0.80651154+0.24878194*I,
	   -0.28453391-0.2075316*I ,  0.17185579-0.45628332*I,
		0.98299962-0.03050341*I,  0.98076439+0.56572909*I,
	   -0.80149647+0.27431147*I,  0.75809182+0.05235964*I,
	   -0.12497317+0.91544201*I,  0.38776055+0.18509138*I,
		0.56813269-0.42440543*I,  0.42626683-0.66958425*I,
		0.0854878 -0.45434897*I,  0.24900675+0.7571507*I ,
	   -0.17828339+0.47215542*I, -0.06793108-0.87519033*I,
		0.05279933+0.11956354*I, -0.2536564 +0.61604181*I,
		0.86353799-0.70367065*I,  0.87605925-0.4990313*I ,
	   -0.55215723+0.52220017*I,  0.23091182-0.11101702*I,
	   -0.89370847+0.75244482*I, -0.61986572+0.18496364*I,
	   -0.97127898-0.37074068*I, -0.47768175-0.36223762*I,
	   -0.48361634+0.2283091*I , -0.60465942-0.68666106*I
	};

	struct int_complex x_fp[N];
	for(i=0; i<N; i++){
		x_fp[i].re = (int16_t)(creal(x[i])*FIX);
		x_fp[i].im = (int16_t)(cimag(x[i])*FIX);
	}

	struct int_complex *X = fixed_recursive_FFT(x_fp, N);

	for(i=0; i<N; i++) printf("%lf%+lfi\n", (X[i].re)/(double)FIX, (X[i].im)/(double)FIX);

	return 0;
}
