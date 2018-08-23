#include "definition.hpp"

extern double h[PATH][SYMBOLN][2];

void multipath_propagation(double (*transmit_signal)[2], double (*received_signal)[2]){
	double a[PATH][COMPONENT], theta[PATH][COMPONENT], phi[PATH][COMPONENT];
	double path_power, component_power, amp, phase;
	int d, n, i;

	for(d = 0; d < PATH; d++){
		for(i = 0; i < SYMBOLN; i++){
			h[d][i][0] = 0.0;
			h[d][i][1] = 0.0;
		}
	}

	for(i = 0; i < BURST; i++){
		received_signal[i][0] = 0.0;
		received_signal[i][1] = 0.0;
	}

	for(d = 0; d < PATH; d++){
		for(n = 0; n < COMPONENT; n++){
			a[d][n] = (double)rand() / RAND_MAX;
			theta[d][n] = (double)rand() / RAND_MAX * 2.0 * PI;
			phi[d][n] = (double)rand() / RAND_MAX * 2.0 * PI;
			if(a[d][n] <= 1.0e-6) a[d][n] = 1.0e-6;
		}
	}

	path_power = sqrt(1.0/PATH);
	component_power = sqrt(1.0/COMPONENT);

	for(i = 0; i < SYMBOLN; i++){
		for(d = 0; d < PATH; d++){
			for(n = 0; n < COMPONENT; n++){
				amp = path_power * component_power * sqrt(-log(a[d][n]));
				phase = 2.0 * PI * FD * cos(theta[d][n]) * i * Ts + phi[d][n];
				h[d][i][0] += amp * cos(phase);
				h[d][i][1] += amp * sin(phase);
			}
			
			if((i+d) < BURST) {
				received_signal[i+d][0] += transmit_signal[i][0] * h[d][i][0] - transmit_signal[i][1] * h[d][i][1];
				received_signal[i+d][1] += transmit_signal[i][0] * h[d][i][1] + transmit_signal[i][1] * h[d][i][0];
			}
		}
	}
}
