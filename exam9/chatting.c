#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <unistd.h>

#define MAXBUF 512

typedef struct
{
long data_type;
char data[MAXBUF];
} t_data;

typedef struct
{
int number;
int fd;
} tide;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *snd_message(void *arg)
{
tide* num;
num = (tide*)arg;
pthread_t tid;
char buf[MAXBUF];
char buff[MAXBUF];
t_data datas;
int c;
while(1)
{
memset(buf,'\0',MAXBUF);
memset(buff,'\0',MAXBUF);
scanf("%d",&c);
getchar();
fgets(buf,MAXBUF,stdin);
*(buf+(strlen(buf)-1))='\0';
datas.data_type = c;
sprintf(buff,"[%d sned] : %s\n",(*num).number,buf);
strcpy(datas.data,buff);
pthread_mutex_lock(&mutex);
msgsnd((*num).fd,&datas,sizeof(datas)-sizeof(long),0);
pthread_mutex_unlock(&mutex);
}
}

void *rcv_message(void *arg)
{
tide* num;
num = (tide*)arg;
char buf[MAXBUF];
int i;
t_data datas;
while(1)
{
if((msgrcv((*num).fd,&datas,sizeof(datas)-sizeof(long),(*num).number,0))>0)
{
printf("%s\n",datas.data);
}
}
}


int main(int argc,char *argv[])
{
pthread_t snd_thread,rcv_thread;
int fd;
void *thread_result;
tide num;
num.fd = msgget((key_t)12345,IPC_CREAT|0666);
if(argc!=2)
{
printf("err : Invalid input.\n");   
exit(1);
}
num.number = atoi(argv[1]);
pthread_create(&snd_thread,NULL,snd_message,&num);
pthread_create(&rcv_thread,NULL,rcv_message,&num);
pthread_join(rcv_thread,&thread_result);
pthread_join(snd_thread,&thread_result);
return 0;
}
