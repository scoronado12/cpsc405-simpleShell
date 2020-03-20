#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h> 
#include "shell.h"


int main(){

    while (1){

        printf("[%s@nenbarsh]$ ", getenv("USER"));
        char *cmd = sh_readline();



	    char **cmd_arr = split(cmd, " ");


        int status = parseNrun(get_size(cmd_arr), cmd_arr);

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
