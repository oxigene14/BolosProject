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

    // If this is the process_p code
    // PID of the child is 0
    if (process_p == 0)
    {
        // Fork of the process_a based on the process_p
        process_a = fork();
        // If this is the process_a code
        // PID of the child is 0
        if (process_a == 0)
        {
            printf("I am the child a from the parent p with pid %d\n", (int)getpid());
            sleep(10);
            printf("The pid of the parent p is %d\n", (int)getppid());
            printf("Child exiting...\n");
        }
        // If this is not the process_a code
        else
        {
            kill(getpid(), SIGTERM);
            printf("I am the child p from the parent program with pid %d\n", (int)getpid());
            printf("The pid of the program itself is %d\n", (int)getppid());
            wait(NULL);
        }
        
    }

    // Else the parent code of the program
    // PID of the parent is not 0
    else
    {
        wait(NULL);
    }

}

int main(int argc, char* argv[])
{
    forkexample();
    return 0;
}