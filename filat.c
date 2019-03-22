#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	if (argc == 1)
	{
		printf("Too few arguments\n");
		return 1;
	}
	const char* filePath = argv[1];

	struct stat fileStat;
	if (stat(filePath, &fileStat) < 0)
	{
		printf("File is not existing\n");
		return 1;
	}
		

	char * mode;

	if (S_ISREG(fileStat.st_mode))
	{
		mode = "Regular file";
	}
	else if (S_ISDIR(fileStat.st_mode))
	{
		mode = "Directory";
	}
	else if (S_ISCHR(fileStat.st_mode))
	{
		mode = "Character special file";
	}
	else if(S_ISBLK(fileStat.st_mode))
	{
		mode = "Block special file";
	}
	else if (S_ISLNK(fileStat.st_mode))
	{
		mode = "Symbolic link";
	}
	else
	{
		mode = "Not defined";
	}

	printf("-------------------- %s --------------------\n", filePath);

	printf("File type \t\t: %s\n", mode);


	printf("Access privileges \t: ");
	printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n");
	
	printf("inode-Number \t\t: %d\n", fileStat.st_ino);

	printf("Device numbers \t\t: \n");

	printf("Links count \t\t: %d\n", fileStat.st_nlink);

	printf("UID \t\t\t: %d\n", fileStat.st_uid);

	printf("GID \t\t\t: %d\n", fileStat.st_gid);

	printf("File Size \t\t: %d\n", fileStat.st_size);

	printf("Last access \t\t: %s", asctime(gmtime(&fileStat.st_atime)));

	printf("Last modification \t: %s", asctime(gmtime(&fileStat.st_mtime)));

	printf("Last inode change \t: %s", asctime(gmtime(&fileStat.st_ctime)));
	return 0;
}