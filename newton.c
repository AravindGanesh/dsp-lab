#include <stdio.h>
#include <stdint.h>

int16_t float2fixed(double x, uint8_t m){
	// Converts double value to 16 bit fixed point value
	int16_t fixed_val;
	fixed_val = (int16_t)(x * (1<<m));
	return fixed_val;
} 

double fixed2float(int16_t x,  uint8_t m){
	// Converts 16 bit fixed point value to floating point value
	double float_val;
	float_val = ((double)x)/(1<<m);
	return float_val;
}

double division(double a, double b){

	int16_t A = float2fixed(a, 4), B = float2fixed((1.0/b), 5);
	int16_t AB = A * B;
	double ab = fixed2float(AB, 9);
	return AB;
}

// f(x) = x^3 - x - 1
double f(double x){
	return (x*x*x)-x-1; 
}

// f'(x) = 3x^2 - 1
double df(double x){
	return (3*x*x)-1;
}

// f(x) in fixed point 
double F(double x){
	int16_t X3 = float2fixed(x, 3)*float2fixed(x, 3)*float2fixed(x, 3);
	int16_t X1 = float2fixed((-x-1), 9);
	int16_t Y = X3 + X1;
	return fixed2float(Y, 9);
}

// f'(x) in fixed point
double dF(double x){
	int16_t Y = 3*float2fixed(x,5)*float2fixed(x,5) - float2fixed(1, 10);
	return fixed2float(Y, 10);
}

int main(){
	// initialize the error
	double float_err=2.5, fixed_err = 2.5; 

	// reduce the error iteratively
	while(float_err > 1e-5)
		float_err -= f(float_err)/df(float_err);
	
	while(fixed_err > 1e-5)
		fixed_err -= division(F(fixed_err),dF(fixed_err));

	printf("Floating point result = %lf\nFixed point result = %lf",float_err, fixed_err);
	return 0;
}