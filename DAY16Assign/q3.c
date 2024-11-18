/*
One thread prints "SUNBEAM" continuously, and other thread prints "INFOTECH" continhously. Only one should print at a time starting with
"SUNBEAM".
*/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>

int count,fir;
pthread_mutex_t m;
pthread_cond_t c;

void sigint_handler(int sig)
{
  printf("signal received: %d\n",sig);
  printf("Final count: %d\n",count);
  pthread_mutex_destroy(&m);
  pthread_cond_destroy(&c);
  _exit(0);
}

void* fir_func(void *param)
{
  char *str = "INFOTECH\n";
  while(1)
  {
  	pthread_mutex_lock(&m);	
    while(fir == 0)
	  pthread_cond_wait(&c, &m);
  	count--;
  	write(1,str,strlen(str)+1);
	fir=0;
    pthread_cond_signal(&c);
  	pthread_mutex_unlock(&m);
    sleep(1);
  }
  return NULL;
}

void* sec_func(void *param)
{
  char *str = "SUNBEAM\n";
  while(1)
  {
  	pthread_mutex_lock(&m);
    while(fir == 1)
	  pthread_cond_wait(&c, &m);
  	count++;
  	write(1,str,strlen(str)+1);
	fir=1;
    pthread_cond_signal(&c);
  	pthread_mutex_unlock(&m);
    sleep(1);
  }
  return NULL;
}

int main()
{
  int ret;
  pthread_t th1,th2;
  pthread_cond_init(&c,NULL);
  struct sigaction sa;
  memset(&sa,0,sizeof(sa));
  sa.sa_handler = sigint_handler;
  sigaction(SIGINT,&sa,NULL);

  pthread_mutex_init(&m,NULL);
  ret = pthread_create(&th2,NULL,sec_func,NULL);
  if(ret != 0)
  {
     perror("pthread_create(th1) failed..!!\n");
	 _exit(1);
  }
  
  ret = pthread_create(&th1,NULL,fir_func,NULL);
  if(ret != 0)
  {
     perror("pthread_create(th2) failed..!!\n");
	 _exit(1);
  }
  printf("Enter to exit from process..!!");
  getchar();
  pthread_kill(th1, SIGINT);
  return 0;
}
