#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"
#include <linux/sched.h>  

#define SIZE_STACK  (1024 * 1024)

int main(){

    char *stack; // points to bottom of mem
    char *stackhead; // points to top of the mem
    pid_t clone_pid;
    stack = (char *) malloc(SIZE_STACK);

    if(!stack){
        printf("COULD NOT MALLOC STACK\n");
        exit(1);
    }
    stackhead = stack + SIZE_STACK -1;
    clone_pid = clone(shell_func, stackhead, SIGCHLD | CLONE_NEWUSER | CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWNS | CLONE_NS , NULL);
    if(clone_pid == -1){
        printf("UNABLE TO CLONE.\n");
        free(stack);
        exit(1);
    }
    wait(NULL);
    return 0;
}

// Shell func that runs the created shell

int shell_func(){
    char cmd[1024];
    char *argv[64];
    bzero(cmd, 128);
    printf(" ____________________________");
    printf("|      Omar's Shell          |");
    printf("|____________________________|");

    while(1){
        printf("O's Shell ->");
        fgets(cmd,30,stdin);
        parse(cmd, argv);
        if(strcmp("exit", argv[0]) == 0){
            exit(0);
        }
        // user change directory
        else if (strcmp("cd", argv[0]) == 0){
            if(chdir(argv[1]) == -1){
                printf("COULD NOT CHANGE DIRECTORY.\n");
            }
        }
        // set host name
        else if (strcmp("sethostname", argv[0]) == 0){
            if(sethostname(argv[1], sizeof(argv[1])) == -1){
                printf("COULD NOT SET HOST NAME.\n");
            }
        }
        // change root
        else if(strcmp("changeroot", argv[0]) == 0){
            if(chroot(".") == -1){
                printf("COULD NOT CHANGE ROOT.\n");
            }
        }
        // print the pid of the child
        else if(strcmp("showpid", argv[0]) == 0){
            printf("Clone PID: %ld\n", (long)getpid());
        }
        else{
            execute_cmd(argv);
        }
        
    }
}
// Execute functoin that executes the commands
void execute_cmd(char **argv){
    pid_t pid;
    pid = fork();
    if (pid == -1){
        printf("FORK FAILED.\n");
        exit(1);
    }
    else if(pid == 0){
        if(execvp(*argv,argv) < 0){
            printf("COMMAND NOT FOUND.\n");
        }
        exit(0);
    }
    else{
        wait(NULL);
    }   
}
// parsing function used to parse the cmd line in order to get the args
void parse(char *line, char **argv){
    while(*line != '\0'){
        while (*line == ' ' || *line == '\t' || *line == '\n'){
            *line++ = '\0';
        }

        *argv++ = line;
        while (*line != '\0' && *line != ' ' && *line != '\n' && *line != '\t'){
            line++;
        }
    }
    *argv = '\0';
    
}
