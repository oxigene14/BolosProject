#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

void forkexample()
{
    // Declaration of the two process p and a
    pid_t process_p, process_a;

    // Fork from the program and creation of the process_p
    process_p = fork();

    // Switch case for the process_p
    // PID of the child is 0
    switch(process_p)
    {
        // If an error ocurred while forking then print an error message to stderr
        case -1:
            perror("fork failed for the process p");  
            break;
        // If this is the process_p code
        // PID of the child is 0
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
                    
                    sleep(10);
                    printf("The pid of the parent p is %d\n", (int)getppid());
                    printf("Child exiting...\n");
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
            wait(NULL);
    }
}

int main(int argc, char* argv[])
{
    forkexample();
    return 0;
}