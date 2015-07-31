#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

int main(){

	float num[65536], numLog2[65536];
	int i, y, n;

	/* Generate numbers and their log2 */
	num[0] = 0;
	numLog2[0] = 0;
	for(i =1; i<=65535;i++){
		num[i] = i;
		numLog2[i] = ( log(num[i]) / log(2) );
	}

    /* PRINT TO FILE */
    FILE *fp;
    char outputLog[]="log2Nums.txt";

    fp=fopen(outputLog,"w");
    for(n=0;n<=65535;n++){
            fprintf(fp,"%f\n",numLog2[n]);
    }
    fclose(fp);

    /* PRINT TO FILE */
    char outputNum[]="nums.txt";

    fp=fopen(outputNum,"w");
    for(n=0;n<=65535;n++){
            fprintf(fp,"%f\n",num[n]);
    }
    fclose(fp);

	return 0;
}