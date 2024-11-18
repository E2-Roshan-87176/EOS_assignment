/*
  Create a thread to sort given array of "n" integers using bubble sort. Main thread should print the result after sorting is completed.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

struct arr_n{
  int size;
  int *arr;
};

void* sort_arr(void *param)
{
  int i,j,temp;
  struct arr_n *arr_n = (struct arr_n *)param;
  for(i=0;i<(arr_n->size)-1;i++)
  {  
    for(j=i+1;j<arr_n->size;j++)
	{
       if(arr_n->arr[i] > arr_n->arr[j])
	   {
         temp = arr_n->arr[i];
		 arr_n->arr[i] = arr_n->arr[j];
		 arr_n->arr[j] = temp;
	   }
	}
  }
  return NULL;
}

int main()
{
  struct arr_n arr_sort;
  pthread_t th1;
  int ret;
  printf("Enter the size of array: ");
  scanf("%d",&arr_sort.size);
 
  arr_sort.arr = (int *)malloc(arr_sort.size * sizeof(int));

  printf("Enter the %d elements in array: \n",arr_sort.size);
  for(ret = 0; ret < arr_sort.size; ret++)
  {
    scanf("%d",&arr_sort.arr[ret]);
  }
  for(ret = 0; ret < arr_sort.size; ret++)
  { 
    printf("arr[%d]: %d\n",ret,arr_sort.arr[ret]);
  }

  ret = pthread_create(&th1, NULL, sort_arr, &arr_sort);
  if(ret != 0)
  {
     perror("pthread_create() failed..!!\n");
	 _exit(2);
  }
  pthread_join(th1,NULL);
  printf("Sorted array: \n");
  for(ret=0;ret<arr_sort.size;ret++)
  { 
    printf("arr[%d]: %d\n",ret,arr_sort.arr[ret]);
  } 
  return 0;
}
