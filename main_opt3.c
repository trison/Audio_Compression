#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 
#define SAMPLE_LENGTH 65536
//#define SAMPLE_LENGTH 16777216

/* 2^24 = 16777216 */
/* 2^16 = 65536 */

/* pwlog2 = piecewise log2 */

/* third optimization - return constant values */
unsigned long pwlog2(unsigned long x){

	if( x < 65536){/* 2^16 */
		return 16;
	}
	if( x < 32768){
		return 15;
	}
	if( x < 16384){
		return 14;
	}
	if( x < 8192){
		return 13;
	}
	if( x < 4096){
		return 12;
	}
	if( x < 2048){
		return 11;
	}
	if( x < 1024){
		return 10;
	}
	if( x < 512){
		return 9;
	}
	if( x < 256){
		return 8;
	}
	if( x < 128){
		return 7;
	}
	if( x < 64){
		return 6;
	}
	if( x < 32){
		return 5;
	}
	if( x < 16){
		return 4;
	}
	if( x < 8){
		return 3;
	}
	if( x < 4){
		return 2;
	}
	if( x < 2){
		return 1;
	}
	if( x < 1){
		return 0; /* error */
	}
}

unsigned long func(unsigned long val){

	unsigned long compressed = pwlog2(val >> 8);
	unsigned long rem = val >> ((compressed >> 12) +2);
	unsigned long final = compressed | rem;
	return final;
}

unsigned long table[17];

int main()
{
	unsigned long i=0;
	unsigned long samples[SAMPLE_LENGTH];
	unsigned long results[SAMPLE_LENGTH];
	unsigned long result;
	
	/***GENERATE SAMPLES***/
	for(unsigned long i =0; i<=SAMPLE_LENGTH; i++){
		samples[i] = i;
	}

	table[0] = samples[1288];


	/***RUN ALGORITHM, GET RESULTS***/
	for(unsigned long j =0; j<=SAMPLE_LENGTH;j++){
		results[j] = func(samples[j]);
	}

	/***PRINT TO FILE***
	// FILE *fp;
	// char output[]="output.txt";
	// unsigned long n;

	// fp=fopen(output,"w");
	// for(n=0;n<SAMPLE_LENGTH;n++){
	// 	fprintf(fp,"%lu\n",results[n]);
	// }
	// fclose(fp);*/

	printf("table[0] = %lu\n",table[0]);



  return 0;
}