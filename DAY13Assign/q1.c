/*
The child process send two numbers to the parent process via message queue. The parent process calculate the sum and return via same message queue.
The child process print the result and exit. The parent process wait for completion of the child and then exit.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define key 0x5678
#define id1 555
#define id2 666

typedef struct msgbuf{
  long id;
  int num1;
  int num2;
  int sum;
}msg_que;

int main()
{
  int msgid,err,ret,s;
  msgid = msgget(key,IPC_CREAT | 0600);
  if(msgid == -1)
  {
    perror("msgget() failed...!\n");
	_exit(1);
  }
  
  ret = fork();
  if(ret == 0)
  { 
    msg_que mq1;
	mq1.id = id1;
	printf("Enter the two numbers: ");
	scanf("%d %d",&mq1.num1,&mq1.num2);
    err = msgsnd(msgid, &mq1, sizeof(msg_que) - sizeof(long),0);
  	if(err == -1)
  	{
    	perror("msgsnd() failed...!\n");
		_exit(1);
  	}	
	else
	   printf("child:msg send sucessfully, num1: %d, num2= %d\n",mq1.num1,mq1.num2);
	
	err = msgrcv(msgid, &mq1, sizeof(msg_que) - sizeof(long), id2, 0);
  	if(err == -1)
  	{
    	perror("msgrcv() failed...!\n");
		_exit(1);
  	}
	else
	   printf("child:msg receive sucessfully, sum = %d\n",mq1.sum);
  }
  else
  {
    msg_que mq2;
	err = msgrcv(msgid, &mq2, sizeof(msg_que) - sizeof(long), id1, 0);
  	if(err == -1)
  	{
    	perror("msgrcv() failed...!\n");
		_exit(1);
  	}
	else
	   printf("Parent:msg send sucessfully, num1: %d, num2= %d\n",mq2.num1,mq2.num2);
	
	
	mq2.id = id2;
	mq2.sum = mq2.num1 + mq2.num2;
    err = msgsnd(msgid, &mq2, sizeof(msg_que) - sizeof(long),0);
  	if(err == -1)
  	{
    	perror("msgsnd() failed...!\n");
		_exit(1);
  	}	
	else
	   printf("Parent:msg send sucessfully, sum = %d\n",mq2.sum);
	
	waitpid(ret,&s,0);
     
  	err = msgctl(msgid, IPC_RMID, NULL);
  	if(err == -1)
  	{
    	perror("msgctl() failed...!\n");
		_exit(1);
  	}
  }

  return 0;
}
