

#include "definition.hpp"

void transmitter(int (*bit), double (*signal)[2]){
	QPSK_modulator(bit, signal);
}


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