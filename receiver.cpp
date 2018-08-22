#include	"definition.hpp"

void receiver(double (*signal)[2], int (*bit)){
	if(MOD == 0){
		QPSK_demodulator_cd(signal, bit);
	}else if(MOD == 1){
		QPSK_demodulator_dd(signal, bit);
	}
}

void QPSK_demodulator_cd(double (*signal)[2], int (*bit)){
	int n, symbol;
	int sym2bin[4][2] = {
		{0,0},
		{0,1},
		{1,1},
		{1,0}
	};

	for(n=0; n<SYMBOLN; n++){
		if(signal[n][0] >= 0.0){
			symbol = (signal[n][1] >= 0.0) ? 0 : 3;
		}else{	
			symbol = (signal[n][1] >= 0.0) ? 1 : 2;
		}
		
		bit[n*2] = sym2bin[symbol][0];
		bit[n*2+1] = sym2bin[symbol][1];
	}
}

void QPSK_demodulator_dd(double (*signal)[2], int (*bit)){
	int n, symbol;

	int sym2bin[4][2] = {{0,0},{0,1},{1,1},{1,0}};

	double d[2],d2[2];

	for (int n = 0; n < SYMBOLN+1; n++){
		// 遅延検波したやつ
		if(n==0){
			d[0]=signal[n][0]*OneBySqrt2+signal[n][1]*OneBySqrt2;
			d[1]=signal[n][1]*OneBySqrt2-signal[n][0]*OneBySqrt2;
		}else{
			d[0]=signal[n][0]*signal[n-1][0]+signal[n][1]*signal[n-1][1];
			d[1]=signal[n][1]*signal[n-1][0]-signal[n][0]*signal[n-1][1];
		}
		
		/*exp(Δθ+π/4)*/
		d2[0] = (d[0]-d[1])*OneBySqrt2;
		d2[1] = (d[0]+d[1])*OneBySqrt2;

		if(d2[0]>=0.0){
			symbol = (d2[1] >= 0.0) ? 0 : 3;
		}else{
			symbol = (d2[1] >= 0.0) ? 1 : 2;
		}

		bit[(n-1)*2] = sym2bin[symbol][0];
		bit[(n-1)*2+1] = sym2bin[symbol][1];
	}

}