#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024*1024*7

int main(int argc, char **argv)
{
	int f, i, readed;
	unsigned char sum_result = 0; 
	unsigned char buf[BUF_SIZE];
	long initializer[] = {0, 0};
	unsigned char result[16];

	f = open(argv[1], O_RDONLY);

	if (f == -1)
	{
		printf("Can't open file %s", argv[1]);
		exit(EXIT_FAILURE);
	}

	memset((void*)result, 0, 16);
	memset((void*)buf, 0, BUF_SIZE);

	asm("vmovdqa %0, %%xmm0" :: "m"(initializer));

	while ((readed = read(f, buf, sizeof(buf))) > 0) {
		for (i=0; i < readed; i += 32)
			asm("vmovdqa %0, %%xmm1\n\t"
				"paddb %%xmm1, %%xmm0\n\t"
				"vmovdqa %1, %%xmm2\n\t"
				"paddb %%xmm2, %%xmm0" :: "m" (buf[i]), "m" (buf[i+16]));
	}
          
    close(f);

	asm("vmovdqa %%xmm0, %0" : "=m" (result));

	for (int i = 0; i < 16; i++)
		sum_result += result[i];

    printf("Reading has done, sum is %u \n", sum_result);

	return 0;
}