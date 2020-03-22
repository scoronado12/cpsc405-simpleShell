#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
#include <unistd.h>
#include "shell.h"

#define pass (void)0

int main(){
    
    char **argv;
    char *cmd;
    while (1){
        char *dir = pwd();
        printf("[%s@nenbarsh %s]$ ", getenv("USER"), dir);

        int status = NULL;
        cmd = sh_readline();
        
        argv = split(cmd, " ");
        /*TODO catch signal 130 here (ctrl+ c) and pass to status*/
        if (strcmp(argv[0], "exit") == 0){
                free(cmd);
                exit(0);    
         }
        int fork_rc = fork();

        if(fork_rc < 0){
            printf("Fork Failed!\n");
		}
        if (fork_rc == 0){
            printf("Forked to parse\n");
            int argc = get_size(argv);
            
                


            int cmd_type = what_command(argc, argv);
            if (cmd_type == REGULAR){
                status = normal_execute(argc, argv); /*status depends on if this command ran okay*/
            } else if (cmd_type == OUTPUT_REDIRECT){
                pass;
            }else if (cmd_type == INPUT_REDIRECT){
                pass;
            }else if (cmd_type == PIPE){
                pass;
            }else if (cmd_type == BACKGROUND){
                pass;
            }
            
        }

        wait(NULL);

        if (status == 0){
            printf("✓ ");
        } else{
            printf("x ");
        }


        

        free(cmd);
        free(argv);


    }
}
