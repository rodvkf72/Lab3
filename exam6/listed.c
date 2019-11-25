#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

void main(int argc, char *argv[])
{
char s[20];
char o[20];
strcpy(s, argv[1]);
if(argc >= 3)
{
strcpy(o, argv[2]);
strcat(s, " ");
strcat(s, o);
}
listed(s);
}

int listed(char *c)
{
int status;
switch(fork())
{
case 0:
execl("/bin/bash", "bin/bash", "-c", c, NULL);
break;
case -1:
perror("fork");
exit(0);
default:
wait(&status);
break;
}
return status;
}
