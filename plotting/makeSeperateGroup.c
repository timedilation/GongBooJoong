#include <stdio.h>

int main()
{
	FILE *fpr, *fpw;
	fpr = fopen("data/BICG/BICG_16to1_tickadj_CPU.csv", "r");
	fpw = fopen("data/BICG/BICG_16to1_Sep_LatReq_CPU_200.csv", "w");
	long int tick;
	int index = 0, cpuLat, cpuReq, finalTick = 0;
	while(index < 48816148) {
		fscanf(fpr,"%d,%ld,%d,%d",&index,&tick,&cpuLat,&cpuReq);
		long int start = tick;
		long int cpuLatSum = cpuLat, cpuReqSum = cpuReq; 
		while(tick - start < 1000000000) { 
			if(fscanf(fpr,"%d,%ld,%d,%d",&index,&tick,&cpuLat,&cpuReq) == EOF)
				break;
			cpuLatSum += cpuLat;
			cpuReqSum += cpuReq;
		}
		fprintf(fpw, "%d,%ld,%ld\n", finalTick++, cpuLatSum, cpuReqSum);
	}
	fclose(fpr);
	fclose(fpw);
}
