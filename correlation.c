/**********************************************************************************************************************
Correlation
a = [ -8.31662009587695e-13 0.634029328751641 -0.767445067471676
1.21423064425930 -0.398089786809545 0.577773754381422 0.836673932101677
-0.308971047587158 1.58778525229245 -0.182021563971272 ]

b = [ 0.256258710000824 -0.299311523023751 1.18013824251201 -0.724526570403471
0.963365491184473 0.0611683879836982 -0.126424722362053
1.08772832230303 -0.743741290000000 1.08772832230147 ]
size = 10
**********************************************************************************************************************/

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

double sum(double x, double y, uint8_t m){
	// Function to add two floating point numbers with 16 bit precesion.
	int16_t X = float2fixed(x,m), Y = float2fixed(y,m);
	int16_t Z = X + Y; // adding fixed point integers
	double z = fixed2float(Z, m);
	return z;
}

double product(double x, double y, uint8_t m){
    // Function to multiply two floating point numbers with 16 bit precesion
    int16_t X = float2fixed(x, m), Y = float2fixed(y,m);
    int16_t Z = (X*Y) >> m;
    double z = fixed2float(Z, m);
    return z;
}


int main(){
	static const uint8_t len_a = 10;
	static const uint8_t len_b = 10;
	const uint8_t len_ab = len_a + len_b - 1; 
	double a[10] = {-8.31662009587695e-13, 0.634029328751641,	-0.767445067471676,	1.21423064425930,	-0.398089786809545,	0.577773754381422,	0.836673932101677,	-0.308971047587158,	1.58778525229245,	-0.182021563971272  };

	double b[10] = {  0.256258710000824,    -0.299311523023751,	 1.18013824251201,	-0.724526570403471,	  0.963365491184473,  0.0611683879836982,   -0.126424722362053,	 1.08772832230303,	-0.743741290000000,	  1.08772832230147 };

	double ab[len_ab];
	double AB[len_ab];
	uint8_t i,j;

	for(i=0; i < len_ab; i++){
		ab[i]=0;
		for(j=0; j<=len_a; j++){
			if(i-j>=0 && i-j<len_b){
				ab[i] += a[j]*b[i-j]; // floating point 
				AB[i] = sum(AB[i], product(a[j],b[j-i], 14), 13); // fixed point
			}
		}
	}

	printf("Results:\n");
	printf("Floating point Convolution:\n");
	for(i=0; i<len_ab; i++) printf("%lf  ", ab[i]);
	printf("\nFixed point Convolution:\n");
	for(i=0; i<len_ab; i++) printf("%lf  ", AB[i]);


	return 0;
}
