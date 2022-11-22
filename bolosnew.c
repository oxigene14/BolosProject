#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

// Function that takes a string and an integer in parameter
// This function will create the process that we want
void forkoneprocess(char* name, int *process)
{
    // Fork from the program and creation of the process
    *process = fork();

    // Switch case for the process created
    // PID of the child is 0
    switch(*process)
    {
        // If an error ocurred while forking then print an error message to stderr
        case -1:
            perror("fork failed for the process");
            break;
        // If this is the process code
        // PID of the child is 0 
        case 0:
            printf("The pid of the %s is %d\n", name, (int)getpid());
            pause();
            break;
        // If this is not the process code
        default:
            break;
    }
}


// Function that takes 3 process in parameter and that will create the chain BDG and CFJ
// The 3 process will be created right after the other 
void forkthreeprocess(char* name1, int* process_1, char* name2, int* process_2, char* name3, int* process_3)
{
    // Fork from the program and creation of the process_1
    *process_1 = fork();
    // Switch case for the process created
    // PID of the child is 0
    switch(*process_1)
    {
        // If an error ocurred while forking then print an error message to stderr
        case -1:
            perror("fork failed for the process");
            break;
        // If this is the process code
        // PID of the child is 0 
        case 0:
            printf("The pid of the %s is %d\n", name1, (int)getpid());

            // Fork from the program and creation of the process_2
            *process_2 = fork();
            switch(*process_2)
            {
                // If an error ocurred while forking then print an error message to stderr
                case -1:
                    perror("fork failed for the process");
                    break;
                // If this is the process code
                // PID of the child is 0 
                case 0:
                    printf("The pid of the %s is %d\n", name2, (int)getpid());

                    // Fork from the program and creation of the process_3
                    *process_3 = fork();
                    switch(*process_3)
                    {
                        // If an error ocurred while forking then print an error message to stderr
                        case -1:
                            perror("fork failed for the process");
                            break;
                        // If this is the process code
                        // PID of the child is 0 
                        case 0:
                            printf("The pid of the %s is %d\n", name3, (int)getpid());
                            pause();
                            break;
                        // If this is not the process code
                        default:
                            // used for the child to finish its process
                            wait(NULL);
                            break;
                            
                    }
                    break;
                // If this is not the process code
                default:
                    // Used for the child to finish its process
                    wait(NULL);
                    break;
                    
            }
            break;
        // If this is not the process code
        default:
            // No wait(NULL) because we are already waiting in the process when the function is called
            //wait(NULL);
            break;
            
    }

}



void mainfork()
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
        // If an error ocurred while forking then print an error message to stderr
        case -1:
            perror("fork failed for the process p");
            break;
        // If this is the process_p code
        // PID of the child is 0
        case 0:
            printf("The pid of the process_p is %d\n", (int)getpid());

            // Fork from the program and creation of the process_a
            process_a = fork();

            // Switch case for the process_a
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
                    printf("The pid of the process_a is %d\n", (int)getpid());
                    forkoneprocess("process_h", &process_h);
                    forkoneprocess("process_e", &process_e);
                    forkoneprocess("process_i", &process_i);
                    
                    forkthreeprocess("process_b", &process_b, "process_d", &process_d, "process_g", &process_g);
                    forkthreeprocess("process_c", &process_c, "process_f", &process_f, "process_j", &process_j);
                    // We wait because we have childs pending that can still be alive
                    // If we didn't have any child and we have wait(null) then it will automatically continue
                    // This is why now the process A will live as long as the process have child pending
                    // Otherwise we could have used the pause() method
                    wait(NULL);
                    break;
                // If this is not the process_a code then it is the process_p code
                // In this case, the goal is to kill it manually or we could let it die on its own
                default:
                    printf("The pid of the process_p dies %d\n", (int)getpid());
                    // We could let it die on its own, but we could also kill it manually with the sigterm signal
                    kill(getpid(), SIGTERM);
                    break;

            }

            break;
        // Else if it is the main program code
        default :
            printf("The pid of the main process is %d\n", (int)getpid());
            // Command that will wait for the signal of the child (which is p)
            // In this case, the p progress will die and will send the signal to the main program
            // Then an entry is prompted
            // If the p program was paused, then the main program will wait indefinitely and the scanf method will not be executed
            wait(NULL);
            scanf("%s" , word) ;
    }


}


int main(int argc, char* argv[])
{
    // Main function of the fork
    mainfork();
    return 0;
}