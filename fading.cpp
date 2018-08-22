#include "definition.hpp"
// h(i)*s(i)を返す関数
void fading(double (*input_signal)[2], double (*output_signal)[2], double h[SYMBOLN][2]){
	
	int n;/*シンボル数のカウンタ*/
	double amp[8], phase[8], theta[8];/*振幅，周波数，到来角*/	
	double r1, r2;/*ランダム*/

	for (int i = 0; i < 2; i++){
		for (n = 0; n < SYMBOLN; n++){		
			h[n][i] = 0;	/* 伝送路特性 初期化*/
		}
	}

	for (int k = 0; k < 8; k++){

		r1 = (double)rand()/RAND_MAX;
		r2 = (double)rand()/RAND_MAX;
		theta[k] = 2*PI*(double)rand()/RAND_MAX;
		if(r1 <= 1.0e-6) {
			r1 = 1.0e-6;
		}
		amp[k] = sqrt(-log(r1)/8);
		phase[k] = 2.0 * PI * r2;
	}
	// printf("%f %f %f\n",amp[0],theta[0],phase[0]);


	for(n=0; n<SYMBOLN+1; n++){
		for (int k = 0; k < 8; k++){
			/* 8波の足し合わせ */
			h[n][0] = h[n][0] + amp[k]*cos(2*PI*FD*cos(theta[k])*Ts*n + phase[k]);
			h[n][1] = h[n][1] + amp[k]*sin(2*PI*FD*cos(theta[k])*Ts*n + phase[k]);
		}

		output_signal[n][0] = input_signal[n][0]*h[n][0] - input_signal[n][1]*h[n][1];
		output_signal[n][1] = input_signal[n][0]*h[n][1] + input_signal[n][1]*h[n][0];
	}
	// printf("%f\n",h[n][0] );
}