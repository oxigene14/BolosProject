#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
        int argv0size = strlen(argv[0]);

        sleep(3);

        strncpy(argv[0],"main",argv0size);

        sleep(3);
        pid_t p = fork();
        if(p) {
                strncpy(argv[0],"parent",argv0size);
        } else {
                strncpy(argv[0],"child",argv0size);
        }
        if(argc>1){
                /* The point of this is to show that the child thread still has
                 * the full original size of argv[0] available for use, even
                 * though we reduced the size of argv[0] prior to the fork */
                printf("argv[0] at 0x%lX and argv[1] at 0x%lX (difference %d bytes)\n",
                        argv[0],argv[1],argv[1]-argv[0]);
        }
        sleep(3);

        if(!p) _exit(0); //child exits here
        waitpid(p);
        exit(EXIT_SUCCESS); //parent exits here
}
