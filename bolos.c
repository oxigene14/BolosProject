#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

void forkexample()
{
    // Declaration of all the processes in the program
    pid_t process_p, process_a, process_b, process_h, process_e, process_i, process_c;

    char word[256];
    // Fork from the program and creation of the process_p
    process_p = fork();

    // Switch case for the process_p
    // PID of the child is 0
    switch(process_p)
    {
        case 0:
            // Fork of the process_a based on the process_p
            process_a = fork();
            // Switch case for the process_p
            // PID of the child is 0
            switch(process_a)
            {
                // If an error ocurred while forking then print an error message to stderr
                case -1:
                    perror("fork failed for the process a");
                    break;
                // If this is the process_a code
                // PID of the child is 0
                case 0:
                    printf("I am the child a from the parent p with pid %d\n", (int)getpid());
                    // Fork of the process_b based on the process_a
                    process_b = fork();
                    // Switch case for the process_b
                    // PID of the child is 0
                    switch(process_b)
                    {
                        // If an error ocurred while forking then print an error message to stderr
                        case -1:
                            perror("fork failed for the process b");  
                            break;
                        // If this is the process_b code
                        // PID of the child is 0
                        case 0:
                            printf("I am the child b from the parent a with pid %d\n", (int)getpid());
                            pause();
                            printf("The pid of the parent a is %d\n", (int)getppid());
                            break;
                        // If this is not the process_b code then it is the process_a code
                        default:
                            wait(NULL);
                    }
                    pause();
                    printf("The pid of the parent p is %d\n", (int)getppid());
                    break;
                // If this is not the process_a code then it is the process_p code
                default:
                    kill(getpid(), SIGTERM);
                    //printf("I am the child p from the parent program with pid %d\n", (int)getpid());
                    //printf("The pid of the program itself is %d\n", (int)getppid());
                    //wait(NULL);
            }
        // if it is the main programm, then it will wait for the child process to finish
        default:
            scanf("%s" , word) ;
            wait(NULL);
    }
}

int main(int argc, char* argv[])
{
    forkexample();
    return 0;
}