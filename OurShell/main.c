#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
#include "shell.h"


int main(){

    while (1){

        printf("[%s@nenbarsh]$ ", getenv("USER"));
        int status = NULL;
        char *cmd = sh_readline();
        /*TODO catch signal 130 here (ctrl+ c) and pass to status*/
        int fork_rc = fork();
        char **cmd_arr;

        if(fork_rc < 0){
            printf("Fork Failed!\n");
		}
        if (fork_rc == 0){
            printf("Forked\n");
            cmd_arr = split(cmd, " ");

            status = parseNrun(get_size(cmd_arr), cmd_arr);

            
        }

        wait(NULL);

        if (status == 0){
            printf("✓ ");
        } else{
            printf("x ");
        }


		    





        //TODO detection if we have & > or < and |
        //else fork() and exec()
        

        free(cmd);
        free(cmd_arr);


    }


}
