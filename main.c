#include <math.h>
#include <stdio.h>
#include <stdlib.h>
 
#define SAMPLE_LENGTH 65536

// 2^24 = 16777216
// 2^16 = 65536

/* pwlog2 = piecewise log2 */
unsigned long pwlog2(unsigned long x){

	if( x < 1){
		return( 0); /* error */
	}
	if( x < 2){
		return((x-1) << 12);
	}
	if( x < 4){
		return((1<<12) + ((x-2)<<11));
	}
	if( x < 8){
		return((2<<12) + ((x-4)<<10));
	}
	if( x < 16){
		return((3<<12) + ((x-8)<<9));
	}
	if( x < 32){
		return((4<<12) + ((x-16)<<8));
	}
	if( x < 64){
		return( (5<<12) + ((x-32)<<7));
	}
	if( x < 128){
		return( (6<<12) + ((x-64)<<6));
	}
	if( x < 256){
		return( (7<<12) + ((x-128)<<5));
	}
	if( x < 512){
		return( (8<<12) + ((x-256)<<4));
	}
	if( x < 1024){
		return( (9<<12) + ((x-512)<<3));
	}
	if( x < 2048){
		return( (10<<12) + ((x-1024)<<2));
	}
	if( x < 4096){
		return( (11<<12) + ((x-2048)<<1) );
	}
	if( x < 8192){
		return( (12<<13) + ((x-4096)));
	}
	if( x < 16384){
		return( (13<<12) + ((x-8192)>>1));
	}
	if( x < 32768){
		return( (14<<12) + ((x-16384)>>2));
	}
	if( x < 65536){//2^16
		return( (15<<12) + ((x-32768)>>3));
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
	unsigned long i=0;
	unsigned long samples[SAMPLE_LENGTH];
	unsigned long results[SAMPLE_LENGTH];
	unsigned long result;
	
	//generate samples
	for(unsigned long i =0; i<=SAMPLE_LENGTH; i++){
		samples[i] = i;
	}

	for(unsigned long j =0; j<=SAMPLE_LENGTH;j++){
		results[j] = func(samples[j]);
	}

	//**PRINT TO FILE
	FILE *fp;
	char output[]="output.txt";
	unsigned long n;

	fp=fopen(output,"w");
	for(n=0;n<SAMPLE_LENGTH;n++) {
		fprintf(fp,"%lu\n",results[n]);
	}
	fclose(fp);

	// unsigned long b = 8<<15;
	// long a = (3<<12);
	// printf("b = %u\n", b);

  return 0;
}