#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
int main(){

    while (1){
        char *cmd;

        printf("%s@nenoShell$ ", getenv("USER"));
        cmd = sh_readline();

	char **cmd_arr = split(cmd, " ");
	for (int i = 0; cmd_arr[i] == NULL; i++)
		printf("%s", cmd_arr[i]);


    }


}
