#include	"definition.hpp"

void receiver(double (*signal)[2], int (*bit)){
	#if DIFF == 1
		QPSK_demodulator_dd(signal, bit);
	#else
		QPSK_demodulator_cd(signal, bit);
	#endif
		
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
	int sym2bin[4][2] = {
		{0,0},
		{0,1},
		{1,1},
		{1,0}
	};
	double temp[2], dd_signal[2];

	for(n=1; n<SYMBOLN; n++){

		temp[0] = signal[n][0] * signal[n-1][0] + signal[n][1] * signal[n-1][1];
		temp[1] = signal[n][1] * signal[n-1][0] - signal[n][0] * signal[n-1][1];

		dd_signal[0] = temp[0] * OneBySqrt2 - temp[1] * OneBySqrt2;
		dd_signal[1] = temp[0] * OneBySqrt2 + temp[1] * OneBySqrt2;

		if(dd_signal[0] >= 0.0) {
			symbol = (dd_signal[1] >= 0.0) ? 0 : 3;
		}else {	
			symbol = (dd_signal[1] >= 0.0) ? 1 : 2;
		}		
		
		bit[(n-1)*2] = sym2bin[symbol][0];
		bit[(n-1)*2+1] = sym2bin[symbol][1];
	}
}