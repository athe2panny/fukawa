#include "definition.hpp"

extern double CNR;


void make_graph(int loop, size_t decpn, int hop, int MIX){
	int n, error = 0;
	double Pe;
	static double AveragePER = 0.0;
	static double Averagehop = 0.0;	
	FILE *fp;

	Pe = 1.0 - (double) decpn / SensorN;
	AveragePER += (double) Pe /	LOOPN;
	Averagehop += (double) hop / LOOPN;
	// printf("# %5d: Eb/N0 = %f, %e\t%e\n", loop, (CNR - 3.0), Pe, AverageBER);

	if(loop==LOOPN-1){
		if(GRAPH == 0){
			printf("Eb/N0 = %f, Average PER = %e, HOP = %e\n",(CNR - 3.0), AveragePER, Averagehop);
			fp = fopen(FILENAME,"a");
			fprintf(fp,"%f\t%e\n",(CNR - 3.0), AveragePER);
			fclose(fp);
			fp = fopen(FILENAME2,"a");
			fprintf(fp,"%f\t%e\n",(CNR - 3.0), Averagehop);
			fclose(fp);
		}else{
			printf("MIX = %d, Average PER = %e, HOP = %e\n",MIX, AveragePER, Averagehop);
			fp = fopen(FILENAME3,"a");
			fprintf(fp,"%d\t%e\n",MIX, AveragePER);
			fclose(fp);
			fp = fopen(FILENAME4,"a");
			fprintf(fp,"%d\t%e\n",MIX, Averagehop);
			fclose(fp);
		}

			AveragePER = 0.0;
			Averagehop = 0.0;
		
	}
}