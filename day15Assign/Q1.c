#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>


struct input{
	int n_strt;
	int n_end;
};

struct output{
	//int sum;
	int res;
	int err;
};

void* sumofnum(void *param){
	int sum=0, i;
	struct input *ip = (struct input *)param;
	struct output *op =(struct output *)malloc(1*sizeof(struct output));
		if(ip->n_end == ip->n_strt){
		
			sum=ip->n_end + ip->n_strt;
			op->res=sum;
			}
		else if(ip->n_strt > ip->n_end){
			
			 for(i=ip->n_end; i>=ip->n_strt; i--){
			 
 				sum = sum +i;
 				op->res =sum;
 				op->err = 0;
			}
			}
		else{

			for(i=ip->n_strt; i<=ip->n_end; i++){

				sum = sum +i;
				op->res =sum;
				op->err = 0;
		}
	}
	printf("sum of %d from %d = %d\n",ip->n_strt,ip->n_end,op->res);
	return op;
}

int main(){
	
	int a, b;
	
	printf("Give the start point of num:");
	scanf("%d",&a);
	printf("Enter the end point of num:");
	scanf("%d",&b);

	pthread_t th;
	struct input in ={ .n_strt =a, .n_end =b };
	struct output *out;
	pthread_create(&th, NULL, sumofnum, &in);


	pthread_join(th, (void**)&out);
	if(out->err==0){
		printf("main: sum= %d\n", out->res);
	}
	else
		printf("main: sum cannot be happen\n");
		free(out);
		return 0;
	}



