#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024*1024*7

int main(int argc, char **argv)
{
	int f, i, readed;
	unsigned char result = 0; 
	unsigned char buf[BUF_SIZE];

	if (argc != 2) {
        fprintf(stderr, "Использование: %s \n", argv[0]);
        exit(EXIT_FAILURE);
    }

	f = open(argv[1], O_RDONLY);

	if (f == -1)
	{
		printf("Can't open file %s", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((readed = read(f, buf, sizeof(buf))) > 0) 
        for (i=0; i < readed; i++) 
            result += buf[i];

    close(f);

    printf("Чтение завершено, сумма равна %u \n", result);

	return 0;
}