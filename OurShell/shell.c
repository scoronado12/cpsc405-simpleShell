#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"
char *sh_readline(){
    char *line = NULL;
    ssize_t buffer_sz = 0;
    getline(&line, &buffer_sz, stdin);
    return line;
}

char **split(char *str, char *tok){
	char arr[15];
	int i = 0;
	arr[i] = strtok(str, tok);
	
	while (arr[i] != NULL){
		arr[i++] = strtok (NULL, " ");
	}

	return arr;	

}
