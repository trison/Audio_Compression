#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>

/* pwlog2 = piecewise log2 */
/* first optimization - reverse order of intervals */
unsigned long pwlog2(unsigned long x){

	if( x >= 32768){/* range 2^25 to 2^16 */
		return( (15<<12) + ((x-32768)>>3));
	}
	if( x >= 16384){
		return( (14<<12) + ((x-16384)>>2));
	}
	if( x >= 8192){
		return( (13<<12) + ((x-8192)>>1));
	}
	if( x >= 4096){
		return( (12<<12) + ((x-4096)));
	}
	if( x >= 2048){
		return( (11<<12) + ((x-2048)<<1) );
	}
	if( x >= 1024){
		return( (10<<12) + ((x-1024)<<2));
	}
	if( x >= 512){
		return( (9<<12) + ((x-512)<<3));
	}
	if( x >= 256){
		return( (8<<12) + ((x-256)<<4));
	}
	if( x >= 128){
		return( (7<<12) + ((x-128)<<5));
	}
	if( x >= 64){
		return( (6<<12) + ((x-64)<<6));
	}
	if( x >= 32){
		return( (5<<12) + ((x-32)<<7));
	}
	if( x >= 16){
		return((4<<12) + ((x-16)<<8));
	}
	if( x >= 8){
		return((3<<12) + ((x-8)<<9));
	}
	if( x >= 4){
		return((2<<12) + ((x-4)<<10));
	}
	if( x >= 2){
		return((1<<12) + ((x-2)<<11));
	}
	if( x >= 1){
		return((x-1) << 12);
	}
	if( x == 0){
		return( 0); /* error */
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
    struct timeb stop, start;
    ftime(&start);

    unsigned int samples[] = {25, 300, 6500, 4000000, 16777215};
    unsigned int results[5];
    int i, j;
    for(j = 0; j<100000000;j++){
        for(i =0; i<5; i++){
            results[i] = func(samples[i]);
            // printf("samples[i] = %d\n", samples[i]);
            // printf("results[i] = %d\n\n", results[i]);
        }
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
    short time_result = (1000.0 *(stop.time - start.time) + (stop.millitm-start.millitm));
    printf("time_result = %hu\n", time_result);

    return 0;
}