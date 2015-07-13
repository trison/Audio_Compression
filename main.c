#include <math.h>
#include <stdio.h>
 
int main()
{
	int i=0;
	unsigned int samples[65537];
	int result;
	
	//generate samples
	for(int i =0; i<=65536; i++){
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