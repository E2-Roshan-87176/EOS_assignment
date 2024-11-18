/*
 Write a program that will launch two programs (e.g. who and wc). 
 The output of ﬁrst program (e.g. who) should be given as input to second program (e.g.wc).
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  int ret1,ret2,err,arr[2],s;
  err = pipe(arr);
  if(err == -1)
  {
    perror("pipe() failed..!!\n");
    _exit(1);
  }

  ret1 = fork();
  if(ret1 == 0)
  { 
    close(arr[0]);
    dup2(arr[1],1);
	close(arr[1]);
	err = execlp("who","who",NULL);
  }

  ret2 = fork();
  if(ret2 == 0)
  {
    close(arr[1]);
	dup2(arr[0],0);
	close(arr[0]);
	err = execlp("wc","wc",NULL);
  }  

  close(arr[1]);
  close(arr[0]);
  waitpid(ret1,&s,0);
  waitpid(ret2,&s,0);
  return 0;
}
