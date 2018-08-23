

#include "definition.hpp"

void transmitter(int (*bit), double (*signal)[2]){
	#if DIFF == 1
		QPSK_modulator_de(bit, signal);

	#else
		QPSK_modulator(bit, signal);

	#endif
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

void QPSK_modulator_de(int (*bit), double (*signal)[2]){
	int n, bit1, bit2, phase4tx, phase4info;
	int bin2sym[2][2] = {
		{ 0, 1},
		{ 3, 2}
	};
	double sym2sgnl[4][2] = {
		{OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2, OneBySqrt2},
		{-OneBySqrt2, -OneBySqrt2},
		{OneBySqrt2, -OneBySqrt2}
	};
	
	signal[0][0] = OneBySqrt2;
	signal[0][1] = OneBySqrt2;
	phase4tx = 0;

	for(n=0; n<SYMBOLN-1; n++){
		bit1 = bit[n*2];
		bit2 = bit[n*2+1];
		phase4info = bin2sym[bit1][bit2];
		phase4tx = (phase4tx + phase4info) % 4;

		signal[n+1][0] = sym2sgnl[phase4tx][0];
		signal[n+1][1] = sym2sgnl[phase4tx][1];
	}
}