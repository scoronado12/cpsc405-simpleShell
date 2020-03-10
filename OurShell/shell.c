#include <stdlib.h>
#include <stdio.h>
#include "shell.h"

char *sh_readline(){
    char *line = NULL;
    ssize_t buffer_sz = 0;
    getline(&line, &buffer_sz, stdin);
    return line;
}
