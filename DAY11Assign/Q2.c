// Implement asynchronous execution in your shell i.e. if command suﬃxed with &, then shell should not wait for the child process. 
//Ensure that process isn't left zombie.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<signal.h>
//Implement signal handler fn
void sigchld_handler(int sig)
{
    int s;
	printf("SIGCHLD caught : %d\n",sig);
    waitpid(-1, &s, 0);
}

int main() 
{
    char cmd[512], *ptr, *args[32];
    int i, ret, err, s;
    
    signal(SIGCHLD,sigchld_handler);  //register signal handler fn

    while(1) 
    {

        printf("cmd> ");
        gets(cmd);
        i = 0;
        ptr = strtok(cmd, " ");
        args[i] = ptr;  i++;
        do 
        {
            ptr = strtok(NULL, " ");
            args[i] = ptr;  i++;
        } while(ptr != NULL);
       
        // implement logic for internal commands
        if(strcmp(args[0], "exit") == 0)
            _exit(0);
        else if(strcmp(args[0], "cd") == 0)
            chdir(args[1]);
        else 
        {
            ret = fork();
            if(ret == 0)
            {
                err = execvp(args[0], args);
                if(err < 0) 
                {
                    perror("exec() failed");
                    _exit(1);
                }
            }
        }
    }
    return 0;
}