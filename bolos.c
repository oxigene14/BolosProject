#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <time.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

// Declaration of all the processes in the program
pid_t process_p, process_a, process_b, process_h, process_e, process_i, process_c, process_d, process_g, process_f, process_j;

// Boolean for knowing when certain process are finished
// bool boolprocess_h = false; 
// bool boolprocess_e = false;
// bool boolprocess_i = false;
// bool boolfinished = false;

// Struct for the current time that will be used later on with the variable gettimeofday
struct timeval current_time;

// Sig_handler that will be able to catch de SIGTERM signal to the process.
// In this function, nothing happens when the signal is caught
// We should not printf values in this function because it can lead to unwanted results
void sig_handler_1(int signum)
{
    signal(SIGTERM, sig_handler_1); /* reset signal */
}


// Function that takes a string and an integer in parameter
// This function will create the process that we want
void forkoneprocess(char* name, pid_t *process, pid_t pArgc, char **pArgv)
{
    // Use to get the size of the variable pargv given in parameter (used to rename the process)
    int argv0size = strlen(pArgv[0]);
    // Fork from the program and creation of the process
    *process = fork();

    // Switch case for the process created
    // PID of the child is 0
    switch(*process)
    {
        // If an error ocurred while forking then print an error message to stderr
        // Break is necessary if we have entered this condition
        case -1:
            perror("fork failed for the process");
            break;
        // If this is the process code
        // PID of the child is 0 
        case 0:
            strncpy(pArgv[0], name, argv0size);
            printf("The pid of the %s is %d\n", name, (int)getpid());
            kill(getpid(), SIGSTOP);
            printf("The %s has received the unpause signal from the process %s \n", name, "process_a");
            printf("The %s with the pid %d has been killed \n", name, (int)getpid());
            exit(0);
            break;
        // If this is not the process code
        // Nothing happens and we just break the process
        default:
            break;
    }
}


// Function that takes 3 process in parameter and that will create the chain BDG
// The 3 process will be created right after the other 
void forkthreeprocess(char* name1, pid_t* process_1, char* name2, pid_t* process_2, char* name3, pid_t* process_3, int pArgc, char **pArgv)
{
    int argv0size = strlen(pArgv[0]);
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
            // Function used to copy in the pArgv[0] the name variable (to change the name of the process)
            strncpy(pArgv[0], name1, argv0size);
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
                    // Function used to copy in the pArgv[0] the name variable (to change the name of the process)
                    strncpy(pArgv[0], name2, argv0size);
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
                            // Function used to copy in the pArgv[0] the name variable (to change the name of the process)
                            strncpy(pArgv[0], name3, argv0size);
                            printf("The pid of the %s is %d\n", name3, (int)getpid());
                            // We send a sigstop signal to this program in order to wait for the parent to send a resume signal
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name3, name2);
                            printf("The %s with the pid %d has been killed \n", name3, (int)getpid());
                            exit(0);
                            break;
                        // If this is not the process code
                        default:
                            // We could have used the wait variable, but we are using SIGSTOP so that we can resume the process later on
                            //wait(NULL);
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name2, name1);
                            // This will be used to retrieve the current_time gettimeofday using the struct created at the beginning
                            gettimeofday(&current_time, NULL);
                            // We create a srand variable so that each time the result will be different (seed)
                            srand ( time(NULL) );
                            // Create a random between 0 and 20
                            int rd = rand() % 20;
                            // rest variable where the current time and the rand will be added so that not the same number is sent to all the process
                            int rest = (current_time.tv_sec + rd) % 4;
                            printf("seconds : %ld\n", (current_time.tv_sec + rd));
                            printf("The rest of the current_time modulo 4 is %d for the process %s \n", rest, name2);

                            // Variable status equal to -1, the value will most likely change
                            int status = -1;
                        
                            // Switching depending on the result of the rest calculated
                            switch(rest)
                            {
                                    // If the rest is equal to 0, then nothing happens
                                    // We break to quit the switchcase
                                case 0:
                                    break;
                                    // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                                case 1:
                                    // TO DO
                                    break;

                                // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                                case 2:
                                    if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    {
                                        // We send to the *process_3 the sigcont signal so that it can resume the processs
                                        kill(*process_3, SIGCONT);
                                        sleep(1);
                                    }
                                    break;

                                // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                                case 3:
                                    if ( waitpid(process_c, &status, WNOHANG) == 0)
                                    {
                                        // TO do
                                    }

                                    if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    {
                                        kill(*process_3, SIGCONT);
                                        sleep(1);
                                    }
                                    break;
                                default:
                                    printf("");
                            }
                                //kill(*process_3, SIGCONT);
                                // The process has been killed and we exit de process
                                printf("The %s with the pid %d has been killed \n", name2, (int)getpid());
                                exit(0);
                                break;
                        }
                    break;
                // If this is not the process code
                default:
                    // We pause the current process with SIGSTOP so that we can resume it later
                    kill(getpid(), SIGSTOP);
                    printf("The %s has received the unpause signal from the process A \n", name1);
                    //wait(NULL);
                    //kill(*process_2, SIGCONT);

                    // Same as before with the gettimeofday using the struct created earlier
                    gettimeofday(&current_time, NULL);
                    // srand to have a different seed and a different result
                    srand ( time(NULL) );
                    //  Create a random between 0 and 20
                    int rd = rand() % 20;
                    int rest = (current_time.tv_sec + rd) % 4;
                    printf("seconds : %ld\n", (current_time.tv_sec + rd));
                    printf("The rest of the current_time modulo 4 is %d for the process %s \n", rest, name1);

                    int status = -1;
                        
                    switch(rest)
                    {
                        // If the rest is equal to 0, then nothing happens
                        // We break to quit the switchcase
                        case 0:
                            break;
                        // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                        case 1:
                            // TO DO
                            break;

                        // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                        case 2:
                            if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            {
                                kill(*process_2, SIGCONT);
                                sleep(1);
                                //kill(process_b, SIGKILL);
                                //printf("The process_b with the pid %d has been killed \n", process_b);
                            }
                            break;

                        // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                        case 3:

                            if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            {
                                //kill(process_b, SIGKILL);
                                kill(*process_2, SIGCONT);
                                sleep(1);
                                //printf("The process_b with the pid %d has been killed \n", process_b);                    
                            }
                            break;
                        default:
                            printf("");
                    }
                    // If we get to this point, then we just kill the process
                    printf("The %s with the pid %d has been killed \n", name1, (int)getpid());
                    exit(0);
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

// Function that takes 3 process in parameter and that will create the chain BDG and CFJ
// The 3 process will be created right after the other 
void forkthreeprocessbis(char* name1, pid_t* process_1, char* name2, pid_t* process_2, char* name3, pid_t* process_3, int pArgc, char **pArgv)
{
    int argv0size = strlen(pArgv[0]);
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
            // Function used to copy in the pArgv[0] the name variable (to change the name of the process)
            strncpy(pArgv[0], name1, argv0size);
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
                    strncpy(pArgv[0], name2, argv0size);
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
                            // Function used to copy in the pArgv[0] the name variable (to change the name of the process)
                            strncpy(pArgv[0], name3, argv0size);
                            printf("The pid of the %s is %d\n", name3, (int)getpid());
                            // We stop the process
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name3, name2);
                            printf("The %s with the pid %d has been killed \n", name3, (int)getpid());
                            // We exit the process because we've arrived at the end
                            exit(0);
                            break;
                        // If this is not the process code
                        default:
                            // used for the child to finish its process
                            //wait(NULL);
                            // We stop the current process so that it can be resumed later
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name2, name1);
                            //kill(*process_3, SIGCONT);
                            
                            // We get the time of day with the structure current_time
                            gettimeofday(&current_time, NULL);
                            srand ( time(NULL) );
                            // We add a random +20 so that it does not give the same random
                            int rd = rand() % 20;
                            int rest = (current_time.tv_sec + rd) % 4;
                            printf("seconds : %ld\n", (current_time.tv_sec + rd));
                            printf("The rest of the current_time modulo 4 is %d for the processs %s \n", rest, name2);

                            int status = -1;
                        
                            // Switch that will decide what to do with this process
                            switch(rest)
                            {
                                    // If the rest is equal to 0, then nothing happens
                                    // We break to quit the switchcase
                                case 0:
                                    break;
                                    // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                                case 1:
                                    // If the process_3 is still active and is not dead
                                     if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                     {
                                         kill(*process_3, SIGCONT);
                                         sleep(1);
                                         //kill(process_c, SIGKILL);
                                         //printf("The process_c with the pid %d has been killed \n", process_c);
                                     }
                                    break;

                                // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                                case 2:
                                    // TO DO
                                    break;

                                // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                                case 3:
                                    if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                     {
                                         kill(*process_3, SIGCONT);
                                         sleep(1);
                                         //kill(process_c, SIGKILL);
                                         //printf("The process_c with the pid %d has been killed \n", process_c);
                                     }
                                    // TO DO
                                    break;
                                default:
                                    printf("");
                            }
                            printf("The %s with the pid %d has been killed \n", name2, (int)getpid());
                            exit(0);
                            break;
                    }
                    break;
                // If this is not the process code
                default:
                    // Used for the child to finish its process
                    
                    
                    kill(getpid(), SIGSTOP);
                    printf("The %s has received the unpause signal from the process A \n", name1);
                    //wait(NULL);
                    //kill(*process_2, SIGCONT);

                    gettimeofday(&current_time, NULL);
                    srand ( time(NULL) );
                    int rd = rand() % 20;
                    int rest = (current_time.tv_sec + rd) % 4;
                    printf("seconds : %ld\n", (current_time.tv_sec + rd));
                    printf("The rest of the current_time modulo 4 is %d for the process %s \n", rest, name1);

                    int status = -1;
                        
                    switch(rest)
                    {
                        // If the rest is equal to 0, then nothing happens
                        // We break to quit the switchcase
                        case 0:
                            break;
                        // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                        case 1:
                            if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            {
                                kill(*process_2, SIGCONT);
                                sleep(1);
                                //kill(process_c, SIGKILL);
                                //printf("The process_c with the pid %d has been killed \n", process_c);
                            }
                            break;

                        // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                        case 2:
                            // TO DO
                            break;

                        // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                        case 3:
                            if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            {
                                kill(*process_2, SIGCONT);
                                sleep(1);
                                //kill(process_c, SIGKILL);
                            }
                            // TO DO
                            break;
                        default:
                            printf("");
                    }

                    
                    printf("The %s with the pid %d has been killed \n", name1, (int)getpid());
                    exit(0);
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


void mainfork(int pArgc, char **pArgv)
{

    // We set up the word variable with a size of 256
    char word[256];
    // This will be used to store into a variable the size of the first argument of the program
    int argv0size = strlen(pArgv[0]);
    // This will put into the variable pArgv[0] the name bolos. The size is also given
    strncpy(pArgv[0],"bolos",argv0size);
    
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
            
            signal(SIGTERM,sig_handler_1);
            
            // Fork from the program and creation of the process_a
            process_a = fork();
            //signal(SIGUSR1, sig_handler_parent);
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
                    //raise(SIGUSR1);
                    strncpy(pArgv[0],"p_a",argv0size);
                    printf("The pid of the process_a is %d\n", (int)getpid());
                    forkoneprocess("p_h", &process_h, pArgc, pArgv);
                    forkoneprocess("p_e", &process_e, pArgc, pArgv);
                    forkoneprocess("p_i", &process_i, pArgc, pArgv);
                    
                    forkthreeprocess("p_b", &process_b, "p_d", &process_d, "p_g", &process_g, pArgc, pArgv);
                    forkthreeprocessbis("p_c", &process_c, "p_f", &process_f, "p_j", &process_j, pArgc, pArgv);
                    // We wait because we have childs pending that can still be alive
                    // If we didn't have any child and we have wait(null) then it will automatically continue
                    // This is why now the process A will live as long as the process have child pending
                    // Otherwise we could have used the pause() method
                    //signal(SIGUSR1,sig_handler_2);
                    
                    
                    sleep(2);
                    printf("Please provide anything in the keyboard to try to send a sigterm signal to the process_a\n");
                    scanf("%s" , word);
                    kill(getpid(), SIGTERM);
                        
                    // Does not work ?
                    //signal(SIGTERM, sig_handler_2);
                    printf("\nprocess_a: %d\n", getpid());
                    printf("You cannot kill this process with the pid %d \n\n", getpid());
                        
                        
                    gettimeofday(&current_time, NULL);
                    printf("seconds : %ld\n",current_time.tv_sec);
                    int rest = current_time.tv_sec % 4;
                    printf("The rest of the current_time modulo 4 is %d for the process_a \n", rest);

                    int status = -1;
                        
                    switch(rest)
                    {
                        // If the rest is equal to 0, then nothing happens
                        // We break to quit the switchcase
                        case 0:
                            break;
                        // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                        case 1:
                            if ( waitpid(process_c, &status, WNOHANG) == 0)
                            {
                                kill(process_c, SIGCONT);
                                sleep(1);
                                //kill(process_c, SIGKILL);
                                //printf("The process_c with the pid %d has been killed \n", process_c);
                            }
                            break;

                        // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                        case 2:
                            if ( waitpid(process_b, &status, WNOHANG) == 0)
                            {
                                kill(process_b, SIGCONT);
                                sleep(1);
                                //kill(process_b, SIGKILL);
                                //printf("The process_b with the pid %d has been killed \n", process_b);
                            }
                            break;

                        // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                        case 3:
                            if ( waitpid(process_c, &status, WNOHANG) == 0)
                            {
                                //kill(process_c, SIGKILL);
                                kill(process_c, SIGCONT);
                                sleep(1);
                                //printf("The process_c with the pid %d has been killed \n", process_c);
                            }

                            if ( waitpid(process_b, &status, WNOHANG) == 0)
                            {
                                //kill(process_b, SIGKILL);
                                kill(process_b, SIGCONT);
                                sleep(1);
                                //printf("The process_b with the pid %d has been killed \n", process_b);                    
                            }
                            break;
                        default:
                            printf("");
                    }

                    // Here, we wait 2 times because if a child process sends a signaln the program will continue
                    // But we have 2 childs for this process, so we wait until both are over
                    wait(NULL);
                    sleep(2);
                    wait(NULL);
                    // We pause for the moment the program
                    pause();
               
                    break;
                // If this is not the process_a code then it is the process_p code
                // In this case, the goal is to kill it manually or we could let it die on its own
                default:
                    // We could let it die on its own, but we can also kill it manually with the sigterm signal
                    printf("The pid of the process_p dies %d\n", (int)getpid());
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
            pause();
    }

}

int main(int argc, char* argv[])
{
    // Main function of the fork
    mainfork(argc, argv);
    return 0;
}