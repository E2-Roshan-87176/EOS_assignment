//1. Parent continously prints Sunbeam and Child continously prints Infotech. They should keep printing them one after another (not simultaneously).

#include<stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define sem_key 0x4877

int semid;

union semun {
  int val;   
  struct semid_ds *buf;
  unsigned short  *array;  
  struct seminfo  *__buf;                       
};
		  
void sigchld_handler(int sig)
{
  int s;
  waitpid(-1,&s,0);
}

void sigint_handler(int sig)
{
    semctl(semid, 0, IPC_RMID);
    _exit(0);
}

int main()
{
  int err,ret,i;
  union semun un;
  struct sembuf ops[1];
  struct sigaction sa;

  memset(&sa,0,sizeof(sa));
  sa.sa_handler = sigchld_handler;
  err = sigaction(SIGCHLD,&sa,NULL);
  if(err == -1)
  {
    perror("sigaction() failed..!!\n");
	_exit(1);
  }

  sa.sa_handler = sigint_handler;
  err = sigaction(SIGINT,&sa,NULL);
  if(err == -1)
  {
    perror("sigaction() failed..!!\n");
	_exit(1);
  }

  semid = semget(sem_key, 2, IPC_CREAT|0600);
  if(semid == -1)
  {
    perror("semget() failed..!!\n");
	_exit(1);
  }

  /*short init_cnts[] = {0,1};
  un.array=init_cnts;*/
  un.val=0;
  err = semctl(semid,0,SETVAL,un);
  un.val=1;
  err = semctl(semid,1,SETVAL,un);
  if(err == -1)
  {
    perror("semctl() failed..!!\n");
	_exit(1);
  }
  
  ret = fork();
  if(ret == 0)
  {
   char *str = "INFOTECH\n";
   while(1)
   {
	 ops[0].sem_num = 0;
	 ops[0].sem_op = -1;
	 ops[0].sem_flg = 0;

	 ops[1].sem_num = 1;
	 ops[1].sem_op = -1;
	 ops[1].sem_flg = 0;
  	 err = semop(semid,ops,2);
  	 if(err == -1)
     {
    	perror("semop() failed..!!\n");
		_exit(1);
     }

     write(1,&str[i],strlen(str));
	 
	 ops[1].sem_num = 1;
	 ops[1].sem_op = +1;
	 ops[1].sem_flg = 0;
  	 err = semop(semid,ops,1);
  	 if(err == -1)
     {
    	perror("semop() failed..!!\n");
		_exit(1);
     }
	 sleep(1);
   }
  }
  else
  {
   char *str = "SUNBEAM\n";
   while(1)
   {
	 ops[1].sem_num = 1;
	 ops[1].sem_op = -1;
	 ops[1].sem_flg = 0;
  	 err = semop(semid,ops,1);
  	 if(err == -1)
     {
    	perror("semop() failed..!!\n");
		_exit(1);
     }
	 
	 write(1,str,strlen(str));
     
	 ops[0].sem_num = 0;
	 ops[0].sem_op = +1;
	 ops[0].sem_flg = 0;
   
	 ops[1].sem_num = 1;
	 ops[1].sem_op = +1;
	 ops[1].sem_flg = 0;
  	 err = semop(semid,ops,2);
  	 if(err == -1)
     {
    	perror("semop() failed..!!\n");
		_exit(1);
     }
	 sleep(1);
	}
  }
  return 0;
}
