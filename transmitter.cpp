

#include "definition.hpp"

void transmitter(int (*bit), double (*signal)[2]){
	if(MOD == 0){
		QPSK_modulator(bit, signal);
	}else if(MOD == 1){
		DQPSK_modulator(bit, signal);
	}
}

//QPSK変調
void QPSK_modulator(int (*bit), double (*signal)[2]){
	int n, bit1, bit2, symbol;
	int bin2sym[2][2] = {
		{ 0, 1},
		{ 3, 2}
	};
	double sym2sgnl[4][2] = {
		{ OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2,-OneBySqrt2},
		{ OneBySqrt2,-OneBySqrt2}
	};
	
	for(n=0; n<SYMBOLN; n++){
		bit1 = bit[n*2];
		bit2 = bit[n*2+1];
		symbol = bin2sym[bit1][bit2];
		signal[n][0] = sym2sgnl[symbol][0];
		signal[n][1] = sym2sgnl[symbol][1];
	}
}

//DQPSK変調
void DQPSK_modulator(int (*bit), double (*signal)[2]){
	int n, bit1, bit2, symbol;
	int bin2sym[2][2] = {
		{ 0, 1},
		{ 3, 2}
	};
	double sym2sgnl[4][2] = {
		{ OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2,-OneBySqrt2},
		{ OneBySqrt2,-OneBySqrt2}
	};
	
	signal[0][0] = OneBySqrt2;
	signal[0][1] = OneBySqrt2;

	/*最初の位相*/
	int now_phase = 0;

	for(n=0; n<SYMBOLN; n++){
		bit1 = bit[n*2];
		bit2 = bit[n*2+1];
		symbol = bin2sym[bit1][bit2];
		now_phase = (now_phase + symbol) % 4;
		signal[n+1][0] = sym2sgnl[now_phase][0];
		signal[n+1][1] = sym2sgnl[now_phase][1];
	}
}