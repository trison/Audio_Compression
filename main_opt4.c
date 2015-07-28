#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* pwlog2 = piecewise log2 */
/* fourth optimization - function inlining and operator strength reduction */
static inline unsigned long pwlog2(unsigned long x){

	if( x < 1){
		return( 0); /* error */
	}
	if( x < 2){
		return((x-1) << 12);
	}
	if( x < 4){
		return((4096) + ((x-2)<<11));
	}
	if( x < 8){
		return(8192 + ((x-4)<<10));
	}
	if( x < 16){
		return((12288) + ((x-8)<<9));
	}
	if( x < 32){
		return((16384) + ((x-16)<<8));
	}
	if( x < 64){
		return( (20480) + ((x-32)<<7));
	}
	if( x < 128){
		return( (24576) + ((x-64)<<6));
	}
	if( x < 256){
		return( (28672) + ((x-128)<<5));
	}
	if( x < 512){
		return( (32768) + ((x-256)<<4));
	}
	if( x < 1024){
		return( (36864) + ((x-512)<<3));
	}
	if( x < 2048){
		return( (40960) + ((x-1024)<<2));
	}
	if( x < 4096){
		return( (45056) + ((x-2048)<<1) );
	}
	if( x < 8192){
		return( (49152) + ((x-4096)));
	}
	if( x < 16384){
		return( (53248) + ((x-8192)>>1));
	}
	if( x < 32768){
		return( (57344) + ((x-16384)>>2));
	}
	if( x < 65536){//2^16
		return( (61440) + ((x-32768)>>3));
	}
}

unsigned long func(unsigned long val){

	unsigned long compressed = pwlog2(val >> 8);
	unsigned long rem = val >> ((compressed >> 12) +2);
	unsigned long final = compressed | rem;
	return final;
}

int main()
{
	int start, stop;
	ftime(&start);

	unsigned int samples[] = {25, 300, 6500, 4000000, 16777215};
	unsigned int results[5];
	int i, j;
	for(i =0; i<5; i++){
		results[i] = func(samples[i]);
		printf("samples[i] = %d\n", samples[i]);
		printf("results[i] = %d\n\n", results[i]);
	}

/*
	*PRINT TO FILE***

	FILE *fp;
	char output[]="output.txt";
	unsigned long n;

	fp=fopen(output,"w");
	for(n=0;n<SAMPLE_LENGTH;n++){
		fprintf(fp,"%lu\n",results[n]);
	}
	fclose(fp);*/
/*
	printf("table[0] = %lu\n",table[0]);
*/
	ftime(&stop);

	char time_result = stop-start;
	printf("time_result = %c\n", time_result);

	return 0;
}