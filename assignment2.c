#include <stdio.h>
#include <stdint.h>

int16_t float2fixed(double x, uint8_t m){
	// Converts float value to 16 bit fixed point value
	int16_t fixed_val;
	fixed_val = x * (1<<m);
	return fixed_val;
} 

double fixed2float(int16_t x,  uint8_t m){
	// Converts 16 bit fixed point value to floating point value
	double float_val;
	float_val = ((double)x)/(1<<m);
	return float_val;
}

double add(double x, double y, uint8_t m){
	
	printf("Converting to fixed point:\n");
	int16_t X = float2fixed(x,m);
	printf("x = %lf  =>  X = %d\n", x, X);
	int16_t Y = float2fixed(y,m);
	printf("y = %lf  =>  Y = %d\n", y, Y);
	int16_t Z = X + Y;
	printf("Fixed point addition, Z = X + Y = %d + %d = %d\n", X,Y,Z);
	double z = fixed2float(Z, m);
	printf("Converting the result back to floating point: Z = %d => z = %lf\n", Z, z);
	return z;
}

double subtract(double x, double y, uint8_t m){
	
	printf("Converting to fixed point:\n");
	int16_t X = float2fixed(x,m);
	printf("x = %lf  =>  X = %d\n", x, X);
	int16_t Y = float2fixed(y,m);
	printf("y = %lf  =>  Y = %d\n", y, Y);
	int16_t Z = X - Y;
	printf("Fixed point subtraction, Z = X - Y = %d - %d = %d\n", X,Y,Z);
	double z = fixed2float(Z, m);
	printf("Converting the result back to floating point: Z = %d => z = %lf\n", Z, z);
	return z;
}

int main(){

	double x, y, sum, diff;
	uint8_t m;
	printf("Value of x and y:\n");
	scanf("%lf %lf", &x, &y);
	printf("Select m:\n");
	scanf("%u",&m);
	sum = add(x, y, m);
	diff = subtract(x, y, m);
	return 0;
}

