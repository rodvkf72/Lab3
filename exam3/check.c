#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void check(char* c, int i);

void check(char* c, int i){
DIR *dp;
struct dirent *dir;
struct stat stat;

if((dp=opendir(c)) == NULL){
perror("디렉토리를 열 수 없습니다.\n");
exit(EXIT_FAILURE);
}
chdir(c);

while(dir = readdir(dp)){
memset(&stat, 0, sizeof(struct stat));
lstat(dir->d_name,&stat);

if(S_ISDIR(stat.st_mode))
{
if(strncmp(".", dir->d_name,1) == 0 || strncmp("..", dir->d_name, 2) == 0)
continue;
printf("%*s[DIRECTORY] %s \n", i, "", dir->d_name);
check(dir->d_name, i+4);
}
else
printf("%*s[FILE] %s \n", i, "", dir->d_name);
}
closedir(dp);
}

int main(int argc, char* argv[])
{
if(argc>2){
perror("Usage :: 디렉토리 확인 \n");
exit(EXIT_FAILURE);
}
char* position;
position = argv[1];
check(position, 0);
exit(0);
}
