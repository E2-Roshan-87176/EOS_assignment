/*
 The child process send two numbers to the parent process via pipe. The parent process calculate the sum and return via another pipe. The child process
 print the result and exit. The parent process wait for completion of the child and then exit.
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
  int err,arr1[2],arr2[2],ret,num1,num2,sum,s;
  err = pipe(arr1);
  if(err == -1)
  {
    printf("pipe() failed...!!\n");
	_exit(1);
  }
  err = pipe(arr2);
  if(err == -1)
  {
    printf("pipe() failed...!!\n");
	_exit(1);
  }

  ret = fork();
  if(ret == 0)
  {
    close(arr1[0]);
	close(arr2[1]);

	printf("Enter num1, num2: ");
	scanf("%d %d",&num1,&num2);
	err = write(arr1[1],&num1,sizeof(num1));
  	if(err == -1)
  	{
    	printf("write() failed...!!\n");
		_exit(1);
  	}
	err = write(arr1[1],&num2,sizeof(num2));
  	if(err == -1)
  	{
    	printf("write() failed...!!\n");
		_exit(1);
  	}
	else
	{
		printf("child: msg sent successfully!! num1: %d, num2: %d\n",num1,num2);
		close(arr1[1]);
    }

	err = read(arr2[0],&sum,sizeof(sum));
  	if(err == -1)
  	{
    	printf("read() failed...!!\n");
		_exit(1);
  	}
	else
	{
		printf("child: msg receive successfully!! sum: %d\n",sum);
		close(arr2[0]);
    }

  }
  else
  {
    close(arr1[1]);
	close(arr2[0]);

	err = read(arr1[0],&num1,sizeof(num1));
  	if(err == -1)
  	{
    	printf("read() failed...!!\n");
		_exit(1);
  	}
	err = read(arr1[0],&num2,sizeof(num2));
  	if(err == -1)
  	{
    	printf("read() failed...!!\n");
		_exit(1);
  	}
	else
	{
		printf("Parent: msg receive successfully!! num1: %d, num2: %d\n",num1,num2);
		close(arr1[0]);
    }

    sum = num1 + num2;
	err = write(arr2[1],&sum,sizeof(sum));
  	if(err == -1)
  	{
    	printf("write() failed...!!\n");
		_exit(1);
  	}
	else
	{
	  printf("Parent: msg sent successfully!! sum: %d\n",sum);
      close(arr2[1]);
    } 

    waitpid(ret,&s,0);
  }
  return 0;
}
