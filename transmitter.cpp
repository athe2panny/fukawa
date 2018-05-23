

#include "definition.hpp"

void transmitter(int (*bit), double (*signal)[2])
{
	BPSK_modulator(bit, signal);
}


void BPSK_modulator(int (*bit), double (*signal)[2])
{
	int n, bit1, bit2, symbol;
	double sym2sgnl[2][2] = {
		{ 1, 0},
		{ -1,0}
	};
	
	for(n=0; n<SYMBOLN; n++){
		signal[n][0] = sym2sgnl[bit[n]][0];
		signal[n][1] = sym2sgnl[bit[n]][1];
	}
}
