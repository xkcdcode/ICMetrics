#include <stdio.h>
#include <string.h>

#include "cyassl/ctaocrypt/random.h"
#include "cyassl/ctaocrypt/sha512.h"

void print_buffer(byte* buff, int size) {
    int i;
    for(i=0; i < size; i++) {
            printf("%02x",buff[i]);
    }
}


void print_hash1(byte* hash) {
    int i;
    printf("\nStrong ICMetrics Private key-512bits:");

    for(i = 0; i < SHA512_DIGEST_SIZE; i++) {
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
	byte icmetrics_basis[ ]="82965";
	byte buffer[16];
	byte* icm_rand;

	RNG_GenerateBlock(&rng, &buffer, 16);
    print_buffer(&buffer, 16);

    icm_rand = malloc(strlen(icmetrics_basis) + strlen(buffer)+1);
    strcpy(icm_rand,icmetrics_basis);
    strcat(icm_rand,buffer);

//    printf("\nSize of conc: %d", sizeof(icm_rand));


    byte shaSum[SHA512_DIGEST_SIZE];
    byte *temp;
    Sha512 sha;

    InitSha512(&sha);

   	Sha512Update(&sha, icm_rand, sizeof(icm_rand ));  // can be called again and again

   // print_hash1(shaSum);
    Sha512Final(&sha, shaSum);
    temp=malloc(strlen(shaSum)+1);
    strcpy(temp,shaSum);

    byte* icm_rand2;
    int i,j;
    for (j=1;j<=15;j++)
    {
    icm_rand2=malloc(strlen(icmetrics_basis) + strlen(shaSum)+1);
    strcpy(icm_rand2,icmetrics_basis);
    strcat(icm_rand2,shaSum);
    Sha512Update(&sha, icm_rand2, sizeof(icm_rand2));  // can be called again and again
    Sha512Final(&sha, shaSum);

    int len=strlen(shaSum);
    for (i=0;i<len;i++){
    	*(temp+i)=(*(temp+i)^(*(shaSum+i)));
    }
    }

    print_hash1(shaSum);

	return 0;

}


