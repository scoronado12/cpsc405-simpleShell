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
	int num_spaces = 0;
	for (int i = 0 ; strcmp(str[i], '\0'); i++){
		if (strcmp(str[i], " ")){
			num_spaces++;
		}	
	}

	char str_arr[num_spaces + 1];
	str_arr[num_spaces +1] = NULL;

}
