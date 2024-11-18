/*
  Create a thread to sort given array of 10 integers using selection sort. Main thread should print the result after sorting is completed.
*/

#include <stdio.h>
#include <pthread.h>
#include<unistd.h>

void* sort_arr(void *param)
{
  int i,j,temp;
  int *arr = (int *)param;
  for(i=0;i<9;i++)
  {  
    for(j=i+1;j<10;j++)
	{
       if(arr[i] > arr[j])
	   {
         temp = arr[i];
		 arr[i] = arr[j];
		 arr[j] = temp;
	   }
	}
  }
  return NULL;
}

int main()
{
  pthread_t th1;
  int ret,arr[10] = {55,88,11,66,99,22,44,33,77,11};
  ret = pthread_create(&th1, NULL, sort_arr, arr);
  if(ret != 0)
  {
     perror("pthread_create() failed..!!\n");
	 _exit(2);
  }
  pthread_join(th1,NULL);
  printf("Sorted array: \n");
  for(ret=0;ret<10;ret++)
  { 
    printf("arr[%d]: %d\n",ret,arr[ret]);
  } 
  return 0;
}
