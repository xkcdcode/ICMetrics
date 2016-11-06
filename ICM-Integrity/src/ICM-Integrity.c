#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "cyassl/ctaocrypt/aes.h"
#include "cyassl/ctaocrypt/sha256.h"
#include "cyassl/ctaocrypt/hmac.h"

unsigned long long get_usec()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (((unsigned long long)t.tv_sec) * 1000000) + t.tv_usec;
}

void print_buffer(byte* buff, int size) {
    int i;
    for(i=0; i < size; i++) {
            printf("%02x",buff[i]);
    }
    printf("\n");
}


void print_hash(byte* hash) {
    int i;
    for(i = 0; i < SHA256_DIGEST_SIZE; i++) {
            printf("%02x", hash[i]);
    }
    printf("\n");
}

int main(void) {

	unsigned long long start;
	unsigned long long duration;
	//int i;
	//int N = 100;

	char* str = "Hello Ruhma Ali";

	printf("Plaintext = %s\n", str);
	printf("Size of plaintext = %lu bits\n", sizeof(str)*8);


	// 128 bit Key
	const byte key[] = {0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1f};
	// 192 bit Key
	//const byte key[] = {0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1f,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a};
	// 256 bit Key
	//const byte key[] = {0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1f,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1f};

	const byte iv[] = {0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a,0xb4,0xaf,0x98,0x1a};


	byte plain[16], cipher[16], tag[8], a[20];

	memset(plain, 0, sizeof(plain));
	memset(cipher, 0, sizeof(cipher));
	memset(tag, 0, sizeof(tag));
	memset(a, 0, sizeof(a));

	print_buffer(plain, 16);
	print_buffer(cipher, 16);
	print_buffer(tag, 16);
	print_buffer(a, 20);

	Aes aes;

	start = get_usec();

	AesGcmSetKey(&aes, key, sizeof(key));
	AesGcmEncrypt(&aes, cipher, str, sizeof(cipher), iv, sizeof(iv), tag, sizeof(tag), a, sizeof(a));

	print_buffer(plain, 16);
	printf("Plain = %s\n", plain);
    print_buffer(cipher, 16);
    print_buffer(tag, 16);
    print_buffer(a, 20);

	AesGcmDecrypt(&aes, plain, cipher, sizeof(plain), iv, sizeof(iv), tag, sizeof(tag), a, sizeof(a));


	//for( i = 0; i < N; i++ )
	//{
	// encrypt
	//AesSetKey(&enc, key, sizeof(key), iv, AES_ENCRYPTION);
	//AesCbcEncrypt(&enc, cipher, str, sizeof(str));

	// decrypt
	//AesSetKey(&dec, key, sizeof(key), iv, AES_DECRYPTION);
	//AesCbcDecrypt(&dec, plain, cipher, sizeof(cipher));
	//}
	duration = get_usec() - start;

	printf("Time with %lu bit Key: %d micro seconds\n", sizeof(key)*8 , (int) (duration));
	printf("Ciphertext = %s\n", cipher);
	printf("Plaintext = %s\n", plain);
	printf("Plaintext = %s\n", str);

	return EXIT_SUCCESS;
}
