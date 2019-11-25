#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define PASSWORDSIZE 20

int main() 
{
int f;
int aread; 
int count = 0;
int errcount = 0;
char ch; 
char text[] = "Too many assignments, no time. Do you agree?";
struct termios init_attr, new_attr;
time_t start, end;

f = open(ttyname(fileno(stdin)), O_RDWR);
tcgetattr(f, &init_attr);
new_attr = init_attr;
new_attr.c_lflag &= ~ICANON;
new_attr.c_lflag &= ~ECHO;
new_attr.c_cc[VMIN] = 1;
new_attr.c_cc[VTIME] = 0;
        
if (tcsetattr(f, TCSANOW, &new_attr) != 0) 
{
fprintf(stderr, "속성 설정 불가.\n");
}

printf("다음 문장을 입력하세요.\n%s\n", text);
start = time(NULL);

while ((aread = read(f, &ch, 1)) > 0 && ch != '\n') 
{
if (ch == text[count++])
write(f, &ch, 1);
else 
{
write(f, "*", 1);
errcount++;
}
}

end = time(NULL);
printf("\n오타 : %d\n", errcount);
printf("속도 : %.0f\n",((double)strlen(text)-errcount)/((double)(end-start))*60);
tcsetattr(f, TCSANOW, &init_attr);
close(f);
}
