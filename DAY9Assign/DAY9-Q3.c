#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int ret,s,cnt = 0;
    while(1) {
        ret = fork();
        if(ret == -1) { // parent
            printf("fork() failed.\n");
        }
        else if(ret == 0) {
            // child process
            sleep(0);
            _exit(7);
        }
        else {
            // parent process
            if(ret!=0){
            cnt++;
            printf("child count: %d\n", cnt);
	    while(waitpid(-1, &s, 0) > 0){
         printf("child exit status: %d\n", WEXITSTATUS(s));
       } 
            }
    }
  }
  	 //while(waitpid(-1, &s, 0) > 0){
        // printf("child exit status: %d\n", WEXITSTATUS(s));
     
    return 0;
}
