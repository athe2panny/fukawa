#include	"definition.hpp"

void receiver(double (*signal)[2], int (*bit)){

	QPSK_demodulator_cd(signal, bit);

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