#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(){

    while (1){

        printf("[%s@nenbarsh]$ ", getenv("USER"));
        char *cmd = sh_readline();

	    char **cmd_arr = split(cmd, " ");
	    for (int i = 0; cmd_arr[i] != NULL ; i++){
            //printf("%s\n", cmd_arr[i]);
            if (strcmp(cmd_arr[i],">") == 0){
                printf("Output redirection\n");
            }else if (strcmp(cmd_arr[i],"<") == 0){
                printf("input redirection\n");
            } else if (strcmp(cmd_arr[i],"|") == 0){
                printf("pipe!\n");
            } else if (strcmp(cmd_arr[i], "&")== 0){
                printf("Background\n");
            }
        }
		    





        //TODO detection if we have & > or < and |
        //else fork() and exec()
        

        free(cmd);
        free(cmd_arr);


    }


}
