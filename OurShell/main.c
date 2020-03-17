#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
int main(){

    while (1){
        char *cmd;

        printf("%s@nenoShell$ ", getenv("USER"));
        cmd = sh_readline();

	char **cmd_arr = split(cmd, " ");
	for (int i = 0; i < 15; i++)
		printf("%s \n", cmd_arr[i]);


    }


}
