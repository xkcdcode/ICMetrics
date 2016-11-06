#include <stdio.h>
#include <string.h>

#include "cyassl/ctaocrypt/random.h"
#include "cyassl/ctaocrypt/sha256.h"

// Print contents of buff in hexa-decimal
void print_buffer(byte* buff, int size) {
	int i;
	for(i=0; i < size; i++) {
		printf("%02x",buff[i]);
	}
}

// Print the SHA hash
void print_hash(byte* hash) {
	int i;
	printf("\nStrong ICMetrics Private key (256 bits): ");

	for(i=0; i <SHA256_DIGEST_SIZE; i++) {
		printf("%02x",hash[i]);
	}
}

int main(void)
{
	RNG rng;
	InitRng(&rng);
	//byte b = RNG_GenerateByte(&rng);
	//printf("Random No is: %02x", b);  // Initialize random number generator
	//printf("\nSize of byte: %d", sizeof(b));  // Initialize random number generator
	byte icmetrics_basis[]="82965";
	byte buffer[16];
	byte* icm_rand;

	RNG_GenerateBlock(&rng, &buffer, 16);
	print_buffer(&buffer, 16);

	icm_rand = malloc(strlen(icmetrics_basis) + strlen(buffer)+1);
	strcpy(icm_rand,icmetrics_basis);
	strcat(icm_rand,buffer);

	//    printf("\nSize of conc: %d", sizeof(icm_rand));


	byte shaSum[SHA256_DIGEST_SIZE];
	byte *temp;
	Sha256 sha;

	InitSha256(&sha);

	Sha256Update(&sha, icm_rand, sizeof(icm_rand ));  // can be called again and again

	// print_hash1(shaSum);
	Sha256Final(&sha, shaSum);
	temp=malloc(strlen(shaSum)+1);
	strcpy(temp,shaSum);

	byte* icm_rand2;
	int i,j;
	for (j=1;j<=15;j++)
	{
		icm_rand2=malloc(strlen(icmetrics_basis) + strlen(shaSum)+1);
		strcpy(icm_rand2,icmetrics_basis);
		strcat(icm_rand2,shaSum);
		Sha256Update(&sha, icm_rand2, sizeof(icm_rand2));  // can be called again and again
		Sha256Final(&sha, shaSum);

		int len=strlen(shaSum);
		for (i=0;i<len;i++){
			*(temp+i)=(*(temp+i)^(*(shaSum+i)));
		}
	}

	print_hash(shaSum);

	return 0;

}

