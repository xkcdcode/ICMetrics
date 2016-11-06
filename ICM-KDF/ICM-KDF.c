#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <wolfssl/wolfcrypt/pwdbased.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <wolfssl/wolfcrypt/sha512.h>

#define KEY_SIZE 256
#define HASH SHA256

unsigned long long get_usec()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (((unsigned long long)t.tv_sec) * 1000000) + t.tv_usec;
}

void print_buffer(byte* buff, int size) {
	int i;
	for(i=0; i < size; i++)
	{
		printf("%02x",buff[i]);
	}
}

int main(void)
{

	unsigned long long start;
	unsigned long long duration;
	int ret;

	char passwd[] = "password";
	const byte salt[] = { 0x78, 0x57, 0x8E, 0x5a, 0x5d, 0x63, 0xcb, 0x06 };
	int   iterations = 10000;
	int   kLen = KEY_SIZE;
	byte  derived[KEY_SIZE];

	const byte verify[] = {
			0x43, 0x6d, 0xb5, 0xe8, 0xd0, 0xfb, 0x3f, 0x35, 0x42, 0x48, 0x39, 0xbc,
			0x2d, 0xd4, 0xf9, 0x37, 0xd4, 0x95, 0x16, 0xa7, 0x2a, 0x9a, 0x21, 0xd1
	};

	start = get_usec();

	ret = wc_PBKDF2(derived, (byte*)passwd, (int)XSTRLEN(passwd), salt, 8, iterations, kLen, HASH);
	const char  new_passwd[KEY_SIZE];
	memcpy((void*)new_passwd, derived, sizeof(derived));
	ret = wc_PBKDF2(derived, (byte*)new_passwd, (int)XSTRLEN(new_passwd), salt, 8, iterations, kLen, HASH);

	duration = get_usec() - start;

	printf("Time with %lu bit Key: %d micro seconds\n", sizeof(derived)*8 , (int) (duration));

	if (ret != 0)
		return ret;

	if (XMEMCMP(derived, verify, sizeof(verify)) != 0)
		return -102;

	return 0;

}
