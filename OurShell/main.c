#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
#include <unistd.h>
#include "shell.h"

#define pass (void)0


char cmd[255];


int main(){
        while (strcmp(cmd, "exit") != 0){
        char **argv;
        char *dir = pwd();
        printf("[%s@nenbarsh %s]$ ", getenv("USER"), dir);

        int status = NULL;
        fgets(cmd, 100, stdin);
        cmd[strcspn(cmd, "\n")] = '\0'; 
        //cmd = sh_readline();
        printf("Readline %s done, splitting\n", cmd);
        char cmd_cpy[255];
        strcpy(cmd_cpy,cmd);
        argv = split(cmd, " ");
        //printf("Debug loop\n");
        //int indx = 0;
        /*  
        while (argv[indx] != NULL){
            printf("argv[%d] = %s\n", indx, argv[indx]);
            indx++;
        }*/




        /*TODO catch signal 130 here (ctrl+ c) and pass to status*/
        /*  if (strcmp(argv[0], "exit") == 0){
                free(cmd);
                exit(0);    
         } */
        int fork_rc = fork();

        if(fork_rc < 0){
            printf("Fork Failed!\n");
            exit(-1);
		}
        if (fork_rc == 0){
            //printf("Forked to parse\n");
            int argc = get_size(argv);
            
                


            int cmd_type = -1;
            cmd_type = what_command(argc, argv);
            printf("CMD %s\n", cmd_cpy);
            printf("cmd_type: %d\n", cmd_type);
            if ((cmd_type == REGULAR) && (strcmp(cmd, "exit") != 0)){
                //status = normal_execute(argc, argv); /*status depends on if this command ran okay*/
                execvp(argv[0],argv); //fpintf
                printf("Bad Command: %s\n", argv[0]);
                //free(cmd);
            } else if (cmd_type == OUTPUT_REDIRECT){
                /*could be reused*/
               /* *TODO Findo out why this array of chars are not getting passed correctly */
                //int delimIndx = getIndxOf(">", argc, argv);
                char **delim_split;
                delim_split = split(cmd_cpy, ">");
                
                for (int i = 0; i < get_size(delim_split); i++)
                    printf("DELIM_SPLIT: %s\n", delim_split[i]);

                //free(delim_split);

                

                char left_side[128];
                char right_side[128];

                strcpy(left_side, delim_split[0]);
                /* TODO right_side[0] has a space ' '  */
                strcpy(right_side, delim_split[1]);
                

                printf("To the left %s \n", left_side);
                printf("To the right %s \n", right_side);

                //printf("Index of > is: %d\n", delimIndx);

               
                free(delim_split); 
                
            }else if (cmd_type == INPUT_REDIRECT){
                pass;
            }else if (cmd_type == PIPE){
                pass;
            }else if (cmd_type == BACKGROUND){
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
