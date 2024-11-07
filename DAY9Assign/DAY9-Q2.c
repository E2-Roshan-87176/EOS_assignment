#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int i, ret1, s1, ret2, s2, ret3, s3;
    ret1 = fork();
    if(ret1 == 0) { // child1
        ret2 = fork();
        if(ret2 == 0) { // child2
            ret3 = fork();
            if(ret3 == 0) { // child3
                for(i=1; i<=3; i++) {
                    printf("child3: %d\n", i);
                    sleep(1);
                }
                _exit(0);
            }
            else { // child2
                for(i=1; i<=3; i++) {
                    printf("child2: %d\n", i);
                    sleep(1);
                }
                waitpid(ret3, &s3, 0);
                _exit(0);
            }
        }
        else { // child1 continues
            for(i=1; i<=3; i++) {
                printf("child1: %d\n", i);
                sleep(1);
            }
            waitpid(ret2, &s2, 0);
            _exit(0);
        }
    }
    else { // parent
        for(i=1; i<=3; i++) {
            printf("parent: %d\n", i);
            sleep(1);
        }
        waitpid(ret1, &s1, 0);
    }
    return 0;
}
