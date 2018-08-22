#include "definition.hpp"

extern double CNR;

void awgn(double (*transmitted_signal)[2], double (*received_signal)[2]){
	int n;
	double r1, r2;
	double amp, phase;
	double gamma, noise[2];

	gamma = pow(10.0, CNR / 10.0);

	for(n=0; n<SYMBOLN+1; n++) {
		r1 = (double)rand()/RAND_MAX;
		r2 = (double)rand()/RAND_MAX;
		if(r1 <= 1.0e-6) {
			r1 = 1.0e-6;
		}
		
		amp = sqrt(-log(r1) / gamma);
		phase = 2.0 * PI * r2;
		noise[0] = amp * cos(phase);
		noise[1] = amp * sin(phase);

		received_signal[n][0] = transmitted_signal[n][0] + noise[0];
		received_signal[n][1] = transmitted_signal[n][1] + noise[1];
	}
}

