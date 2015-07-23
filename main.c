#include <math.h>
#include <stdio.h>
 
#define SAMPLE_LENGTH 65535

/* pwlog2 = piecewise log2 */
unsigned char pwlog2(unsigned char x){

	if( x < 1){
		return( 0); /* error */
	}
	if( x < 2){
		return((x-1) << 12);
	}
	if( x < 4){
		return((1<<12) + ((x-2)<<4));
	}
	if( x < 8){
		return((2<<12) + ((x-4)<<3));
	}
	if( x < 16){
		return((3<<12) + ((x-8)<<2));
	}
	if( x < 32){
		return((4<<12) + ((x-16)<<1));
	}
	if( x < 64){
		return( (5<<12) + (x-32));
	}
	if( x < 128){
		return( (6<<12) + ((x-64)>>1));
	}
	if( x < 256){
		return( (7<<12) + ((x-128)>>2));
	}
		return 0;
}

int main()
{
	int i=0;
	unsigned int samples[SAMPLE_LENGTH];
	int result;
	
	//generate samples
	for(int i =0; i<=SAMPLE_LENGTH; i++){
		samples[i] = i;
	}

	//print samples
	int j;
	for(j=65536; j!=0; j--){
		result = log(samples[j])/log(2);
		printf("result: %d\n", result);
	}

  return 0;
}