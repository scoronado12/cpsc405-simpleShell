#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
#include <unistd.h>
#include "shell.h"

#define pass (void)0


char cmd[255];

void handler(int sig){
    signal(SIGINT, handler);
    printf("\n");
    printf("[%s@nenbarsh %s]$ ", getenv("USER"), pwd());

    fflush(stdout);
}


int main() {

    signal(SIGINT, handler); 

        while (1){
            char **argv;
            char *dir = pwd();
            printf("[%s@nenbarsh %s]$ ", getenv("USER"), dir);

            int status = NULL;

            fgets(cmd, 100, stdin);
            cmd[strcspn(cmd, "\n")] = '\0';
           


            printf("Readline %s done, splitting\n", cmd);
            char cmd_cpy[255];
            strcpy(cmd_cpy, cmd);
            argv = split(cmd, " ");
            int argc = get_size(argv);

            //printf("Debug loop\n");
            int indx = 0;
            /*    
            while (argv[indx] != NULL){
                printf("argv[%d] = %s\n", indx, argv[indx]);
                indx++;
            }*/




            /*TODO catch signal 130 here (ctrl+ c) and pass to status*/
            if (strcmp(cmd_cpy, "exit") == 0){
                    free(argv);
                    exit(0);    
            }

             if (feof(stdin)){
                printf("Ctrl + D\n");
                exit(0); 
            }
     



            int fork_rc = fork();

            if(fork_rc < 0){
                printf("Fork Failed!\n");
                exit(-1);
            }
            if (fork_rc == 0){
                //printf("Forked to parse\n");
                int cmd_type = -1;
                cmd_type = what_command(argc, argv);
                printf("CMD %s\n", cmd_cpy);
                printf("cmd_type: %d\n", cmd_type);



                if (cmd_type == REGULAR){
                    
                    status = normal_execute(argc, argv); /*status depends on if this command ran okay*/
                                   //free(cmd);
                } else if (cmd_type == OUTPUT_REDIRECT){
                    /*could be reused*/
                    //int delimIndx = getIndxOf(">", argc, argv);
                   status = output_redir(cmd_cpy);
                                  
                    
                }else if (cmd_type == INPUT_REDIRECT){
                   status = input_redir(cmd_cpy);
                }else if (cmd_type == PIPE){
                    //TODO
                    pass;
                }else if (cmd_type == BACKGROUND){
                    //TODO
                    pass;
                }else if (cmd_type == -1){
                    printf("Something went wrong\ncmd_type: %d\n", cmd_type);
                }
                
            }

            wait(NULL);

            if ((status == 0) && (strcmp(cmd,"exit") != 0)){
                printf("✓ ");
            } else if ((status != 0) && (strcmp(cmd,"exit") != 0)){
                printf("x ");
            }
            free(argv);
    }
    //free(cmd);
    return 0;
}
