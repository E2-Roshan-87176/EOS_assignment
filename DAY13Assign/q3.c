//Write a program to ﬁnd the size of the pipe buﬀer.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int err,ret,arr[2],count=0,s;
  char buff[1] = "P";
  err = pipe(arr);
  if(err == -1)
  {
     perror("pipe() failed...!!\n");
	 _exit(1);
  }
  
  ret = fork();
  if(ret == 0)
  {
  	close(arr[0]);
  	while(1)
  	{ 
     	err = write(arr[1],&buff,sizeof(buff));
		if(err == -1)
		{
           printf("write() failed..!!\n");
		   _exit(1);
		}
	 	count++;
	 	printf("count: %d\n",count);
  	}
 	close(arr[1]);
  }
  waitpid(err,&s,0);

  return 0;
}

