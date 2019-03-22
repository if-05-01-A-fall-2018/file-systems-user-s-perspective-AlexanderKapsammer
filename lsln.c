#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <time.h>

int main(int argc, char const *argv[]) {
	DIR * dir;
	if (argc == 1)
	{
		dir = opendir(".");
	}
	else {
		dir = opendir(argv[1]);
	}
	struct dirent * entr;
	while ((entr = readdir(dir)) != NULL)
	{
		struct stat fileStat;
		if (stat(entr->d_name, &fileStat) < 0) return 1;
		char mode;

		if (S_ISREG(fileStat.st_mode))mode = '-';
		else if (S_ISDIR(fileStat.st_mode))mode = 'd';
		else if (S_ISCHR(fileStat.st_mode))mode = 'c';
		else if (S_ISBLK(fileStat.st_mode))mode = 'b';
		else if (S_ISLNK(fileStat.st_mode))mode = 'l';
		else mode = 'X';
		printf("%c", mode);
		
		printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
		printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
		printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
		printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
		printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
		printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
		printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
		printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
		printf((fileStat.st_mode & S_IXOTH) ? "x " : "- ");
		
		printf("%d ", fileStat.st_nlink);
		printf("%-5d ", fileStat.st_uid);
		printf("%-5d ", fileStat.st_gid);
		printf("%6d ", fileStat.st_size);
		
		char time[18];
		strftime(time, 18, "%Y-%m-%d-%H-%M", localtime(&fileStat.st_mtime));
		printf("%s ", time);
		printf("%s\n", entr->d_name);

	}
	
	closedir(dir);
	return 0;
}