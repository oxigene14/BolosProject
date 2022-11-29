#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// A zombie process : A child that terminates, but has not been waited for becomes a "zombie".

// Declaration of all the processes in the program
pid_t process_p, process_a, process_b, process_h, process_e, process_i, process_c, process_d, process_g, process_f, process_j;
bool boolprocess_h = false; 
bool boolprocess_e = false;
bool boolprocess_i = false;
bool boolfinished = false;

struct timeval current_time;

void sig_handler_1(int signum)
{

    signal(SIGTERM, sig_handler_1); /* reset signal */
    
}


// Function that takes a string and an integer in parameter
// This function will create the process that we want
void forkoneprocess(char* name, int *process, int pArgc, char **pArgv)
{
    int argv0size = strlen(pArgv[0]);
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
            strncpy(pArgv[0], name, argv0size);
            printf("The pid of the %s is %d\n", name, (int)getpid());
            kill(getpid(), SIGSTOP);
            printf("The %s has received the unpause signal from the process %s \n", name, "process_a");
            printf("The %s with the pid %d has been killed \n", name, (int)getpid());
            exit(0);
            break;
        // If this is not the process code
        default:
            break;
    }
}


// Function that takes 3 process in parameter and that will create the chain BDG and CFJ
// The 3 process will be created right after the other 
void forkthreeprocess(char* name1, int* process_1, char* name2, int* process_2, char* name3, int* process_3, int pArgc, char **pArgv)
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
                            strncpy(pArgv[0], name3, argv0size);
                            printf("The pid of the %s is %d\n", name3, (int)getpid());
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name3, name2);
                            printf("The %s with the pid %d has been killed \n", name3, (int)getpid());
                            exit(0);
                            break;
                        // If this is not the process code
                        default:
                            // used for the child to finish its process
                            //wait(NULL);
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name2, name1);

                            gettimeofday(&current_time, NULL);
                            srand ( time(NULL) );
                            int rd = rand() % 20;
                            int rest = (current_time.tv_sec + rd) % 4;
                            printf("seconds : %ld\n", (current_time.tv_sec + rd));
                            printf("The rest of the current_time modulo 4 is %d for the process %s \n", rest, name2);

                            int status = -1;
                        
                            switch(rest)
                            {
                                    // If the rest is equal to 0, then nothing happens
                                    // We break to quit the switchcase
                                case 0:
                                    break;
                                    // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                                case 1:
                                    // if ( waitpid(process_c, &status, WNOHANG) == 0)
                                    // {
                                    //     kill(process_c, SIGCONT);
                                    //     sleep(1);
                                    //     //kill(process_c, SIGKILL);
                                    //     //printf("The process_c with the pid %d has been killed \n", process_c);
                                    // }
                                    break;

                                // If the rest is equal to 2, then the signal sigterm is sent to the child on the left
                                case 2:
                                    if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    {
                                        kill(*process_3, SIGCONT);
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
                                        //kill(process_c, SIGCONT);
                                        sleep(1);
                                        //printf("The process_c with the pid %d has been killed \n", process_c);
                                    }

                                    if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    {
                                        //kill(process_b, SIGKILL);
                                        kill(*process_3, SIGCONT);
                                        sleep(1);
                                        //printf("The process_b with the pid %d has been killed \n", process_b);                    
                                    }
                                    break;
                                default:
                                    printf("");
                            }


                                //kill(*process_3, SIGCONT);
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
                            // boolprocess_e = true;
                            // kill(process_a, SIGCONT);
                            // if ( waitpid(process_c, &status, WNOHANG) == 0)
                            // {
                            //     kill(process_c, SIGCONT);
                            //     sleep(1);
                            //     //kill(process_c, SIGKILL);
                            //     //printf("The process_c with the pid %d has been killed \n", process_c);
                            // }
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
                            // boolprocess_e = true;
                            // kill(process_a, SIGCONT);

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
void forkthreeprocessbis(char* name1, int* process_1, char* name2, int* process_2, char* name3, int* process_3, int pArgc, char **pArgv)
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
                            strncpy(pArgv[0], name3, argv0size);
                            printf("The pid of the %s is %d\n", name3, (int)getpid());
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name3, name2);
                            printf("The %s with the pid %d has been killed \n", name3, (int)getpid());
                            exit(0);
                            break;
                        // If this is not the process code
                        default:
                            // used for the child to finish its process
                            //wait(NULL);
                            kill(getpid(), SIGSTOP);
                            printf("The %s has received the unpause signal from the process %s \n", name2, name1);
                            //kill(*process_3, SIGCONT);
                            
                            gettimeofday(&current_time, NULL);
                            srand ( time(NULL) );
                            int rd = rand() % 20;
                            int rest = (current_time.tv_sec + rd) % 4;
                            printf("seconds : %ld\n", (current_time.tv_sec + rd));
                            printf("The rest of the current_time modulo 4 is %d for the processs %s \n", rest, name2);

                            int status = -1;
                        
                            switch(rest)
                            {
                                    // If the rest is equal to 0, then nothing happens
                                    // We break to quit the switchcase
                                case 0:
                                    break;
                                    // If the rest is equal to 1, then the signal sigterm is sent to the child on the right
                                case 1:
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
                                    // if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    // {
                                    //     kill(*process_3, SIGCONT);
                                    //     sleep(1);
                                    //kill(process_b, SIGKILL);
                                    //printf("The process_b with the pid %d has been killed \n", process_b);
                                    //}
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

                                    // if ( waitpid(*process_3, &status, WNOHANG) == 0)
                                    // {
                                    //     //kill(process_b, SIGKILL);
                                    //     kill(*process_3, SIGCONT);
                                    //     sleep(1);
                                    //     //printf("The process_b with the pid %d has been killed \n", process_b);                    
                                    // }
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
                            // boolprocess_e = true;
                            // kill(process_a, SIGCONT);
                            // if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            // {
                            //     kill(process_d, SIGCONT);
                            //     sleep(1);
                            //     //kill(process_b, SIGKILL);
                            //     //printf("The process_b with the pid %d has been killed \n", process_b);
                            // }
                            break;

                        // If the rest is equal to 3, then the signal sigterm is sent to both child on the left abd on the right
                        case 3:
                            if ( waitpid(*process_2, &status, WNOHANG) == 0)
                            {
                                kill(*process_2, SIGCONT);
                                sleep(1);
                                //kill(process_c, SIGKILL);
                                //printf("The process_c with the pid %d has been killed \n", process_c);
                            }
                            // boolprocess_e = true;
                            // kill(process_a, SIGCONT);
                            // if ( waitpid(process_d, &status, WNOHANG) == 0)
                            // {
                            //     //kill(process_b, SIGKILL);
                            //     kill(process_d, SIGCONT);
                            //     sleep(1);
                            //     //printf("The process_b with the pid %d has been killed \n", process_b);                    
                            // }
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

    char word[256];
    int argv0size = strlen(pArgv[0]);
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
    
                    // kill(getpid(), SIGSTOP);
                    // while (!boolfinished)
                    // {
                    //     if (boolprocess_h)
                    //     {
                    //         kill(process_h, SIGCONT);
                    //     }

                       

                    // }
                    wait(NULL);
                    sleep(2);
                    wait(NULL);
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