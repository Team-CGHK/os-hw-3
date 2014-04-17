#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int uid = atoi(argv[1]);
	int result = setuid(uid);
	if (result != 0)
	{
		printf("could not set uid %i\n", uid);
		exit(1);
	}
	printf("uid %i set.\n", uid);
	for (int i = 2; i+1<argc; i+=2)
	{
		int read = 0;
		for (int j = 0; argv[i+1][j]; ++j) {
			if (argv[i+1][j] == 'r')
				read = 1;
			else
			if (argv[i+1][j] == 'w' && read)
				argv[i+1][j] = '+';
		}
		result = fopen(argv[i], argv[i+1]);
		if (!result) {
			printf("%s cannot be open for %s.\n", argv[i], argv[i+1]);
			exit(1);
		}
		printf("%s can be open for %s.\n", argv[i], argv[i+1]);
	}
	return 0;
}
