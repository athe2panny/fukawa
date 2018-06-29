#include "definition.hpp"

extern double CNR;


void make_graph(int loop, size_t decpn, int hop){
	int n, error = 0;
	double Pe;
	static double AveragePER = 0.0;
	FILE *fp;

	Pe = 1.0 - (double) decpn / SensorN;
	AveragePER += (double) Pe /	LOOPN;
	// printf("# %5d: Eb/N0 = %f, %e\t%e\n", loop, (CNR - 3.0), Pe, AverageBER);

	if(loop==LOOPN-1){
		printf("Eb/N0 = %f, Average PER = %e, HOP = %d\n",(CNR - 3.0), AveragePER, hop);
		fp = fopen(FILENAME,"a");
		fprintf(fp,"%f\t%e\t%d\n",(CNR - 3.0), AveragePER, hop);
		fclose(fp);

		AveragePER = 0.0;
	}
}