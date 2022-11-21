#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

void forkexample()
{
    // Declaration of all the processes in the program
    pid_t process_p, process_a, process_b, process_h, process_e, process_i, process_c, process_d, process_g, process_f, process_j;

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
                            // Fork of the process_d based on the process_b
                            process_d = fork();
                            // Switch case for the process_d
                            // PID of the child is 0
                            switch(process_d)
                            {
                                // If an error ocurred while forking then print an error message to stderr
                                case -1:
                                    perror("fork failed for the process d");  
                                    break;
                                // If this is the process_d code
                                // PID of the child is 0
                                case 0:
                                    printf("I am the child d from the parent b with pid %d\n", (int)getpid());
                                    // Fork of the process_g based on the process_d
                                    process_g = fork();
                                    // Switch case for the process_g
                                    // PID of the child is 0
                                    switch(process_g)
                                    {
                                        // If an error ocurred while forking then print an error message to stderr
                                        case -1:
                                            perror("fork failed for the process g");  
                                            break;
                                        // If this is the process_g code
                                        // PID of the child is 0 
                                        case 0:
                                            printf("I am the child g from the parent d with pid %d\n", (int)getpid());
                                            pause();
                                            printf("The pid of the parent d is %d\n", (int)getppid());
                                            break;
                                        // If this is not the process_g code then it is the process_d code
                                        default:
                                            wait(NULL);
                                    }
                                    
                                    pause();
                                    printf("The pid of the parent b is %d\n", (int)getppid());
                                    break;
                                // If this is not the process_d code then it is the process_b code
                                default:
                                    wait(NULL);
                            }
                            pause();
                            printf("The pid of the parent a is %d\n", (int)getppid());
                            break;
                        // If this is not the process_b code then it is the process_a code
                        default:
                            // Fork of the process_h based on the process_a
                            process_h = fork();
                            // Switch case for the process_h
                            // PID of the child is 0
                            switch(process_h)
                            {
                                // If an error ocurred while forking then print an error message to stderr
                                case -1:
                                    perror("fork failed for the process h");
                                    break;
                                // If this is the process_h code
                                // PID of the child is 0
                                case 0:
                                    printf("I am the child h from the parent a with pid %d\n", (int)getpid());
                                    pause();
                                    printf("The pid of the parent a is %d\n", (int)getppid());
                                    break;
                                // If this is not the process_h code then it is the process_a code
                                default:
                                    // Fork of the process_e based on the process_a
                                    process_e = fork();
                                    // Switch case for the process_e
                                    // PID of the child is 0
                                    switch(process_e)
                                    {
                                        // If an error ocurred while forking then print an error message to stderr
                                        case -1:
                                            perror("fork failed for the process h");
                                            break;
                                        // If this is the process_e code
                                        // PID of the child is 0
                                        case 0:
                                            printf("I am the child e from the parent a with pid %d\n", (int)getpid());
                                            pause();
                                            printf("The pid of the parent a is %d\n", (int)getppid());
                                            break;
                                        // If this is not the process_e code then it is the process_a code
                                        default:
                                            // Fork of the process_i based on the process_a
                                            process_i = fork();
                                            // Switch case for the process_i
                                            // PID of the child is 0
                                            switch(process_i)
                                            {
                                                // If an error ocurred while forking then print an error message to stderr
                                                case -1:
                                                    perror("fork failed for the process h");
                                                    break;
                                                // If this is the process_i code
                                                // PID of the child is 0
                                                case 0:
                                                    printf("I am the child i from the parent a with pid %d\n", (int)getpid());
                                                    pause();
                                                    printf("The pid of the parent a is %d\n", (int)getppid());
                                                    break;
                                                // If this is not the process_i code then it is the process_a code
                                                default:
                                                    // Fork of the process_c based on the process_a
                                                    process_c = fork();
                                                    // Switch case for the process_c
                                                    // PID of the child is 0
                                                    switch(process_c)
                                                    {
                                                       // If an error ocurred while forking then print an error message to stderr
                                                        case -1:
                                                            perror("fork failed for the process h");
                                                            break; 
                                                        case 0:
                                                            printf("I am the child c from the parent a with pid %d\n", (int)getpid());
                                                            pause();
                                                            printf("The pid of the parent a is %d\n", (int)getppid());
                                                            break;
                                                        // If this is not the process_c code then it is the process_a code
                                                        default:
                                                            wait(NULL);

                                                    }
                                            }
                                    }
                                    wait(NULL);
                            }
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