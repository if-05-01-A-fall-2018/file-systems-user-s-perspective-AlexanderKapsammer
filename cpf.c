#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	if (argc == 0 || argc == 1)
	{
		printf("Too few arguments");
		return 1;
	}
	const char* oldPath = argv[1];
	const char* newPath = argv[2];
	int oldFile = open(oldPath, O_RDONLY);
	if (oldFile < 0)
	{
		printf("File not found\n");
		return 1;
	}
	int count = lseek(oldFile, 0, SEEK_END);
	lseek(oldFile, 0, SEEK_SET);
	char buffer[count];
	read(oldFile, &buffer, count);

	int newFile = open(newPath, O_TRUNC);
	newFile = open(newPath, O_WRONLY);
	if (write(newFile, &buffer, sizeof(buffer)) < 0)
	{
		printf("write error\n");
	}
	close(oldFile);
	close(newFile);
	return 0;
}