#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(){

    while (1){
        char *cmd;

        printf("%s@nenoShell$ ", getenv("USER"));
        cmd = sh_readline();

	char **cmd_arr = split(cmd, " ");
	for (int i = 0; i < 3 ; i++)
		printf("%s", cmd_arr[i]);


    }


}
