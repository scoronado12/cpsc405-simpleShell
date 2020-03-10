#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
int main(){

    while (1){
        char *cmd;

        printf("%s@nenoShell $", getenv("USER"));
        cmd = sh_readline();

    }


}
