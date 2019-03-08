#include <stdio.h>

int main()
{
	FILE *fpr, *fpw;
	fpr = fopen("data/ATAX/ATAX_16to1.csv", "r");
	fpw = fopen("data/ATAX/ATAX_16to1_2000.csv", "w");
	long long int tick;
	int index, cpuLat, cpuReq, gpuLat, gpuReq, finalTick = 0;
	char debugStr[9];
	while(fscanf(fpr,"%lld,",&tick) != EOF) {
		fgets(debugStr, 9, fpr);
		fscanf(fpr,",%d,%d,%d,%d",&cpuLat,&gpuLat,&cpuReq,&gpuReq);
		long long int start = tick;
		long int cpuLatSum = cpuLat, cpuReqSum = cpuReq; 
		long int gpuLatSum = gpuLat, gpuReqSum = gpuReq; 
		while((tick - start) < 100000000) { 
			if(fscanf(fpr,"%lld,",&tick) == EOF)
				break;
			fgets(debugStr, 9, fpr);
			fscanf(fpr,",%d,%d,%d,%d",&cpuLat,&gpuLat,&cpuReq,&gpuReq);
			cpuLatSum += cpuLat;
			cpuReqSum += cpuReq;
			gpuLatSum += gpuLat;
			gpuReqSum += gpuReq;
		}
		long int cpuVal = (cpuReqSum == 0) ? cpuLatSum : cpuLatSum/cpuReqSum;
		long int gpuVal = (gpuReqSum == 0) ? gpuLatSum : gpuLatSum/gpuReqSum;
		fprintf(fpw, "%d,%ld,%ld\n", finalTick++, cpuVal, gpuVal);
	}
	fclose(fpr);
	fclose(fpw);
}
