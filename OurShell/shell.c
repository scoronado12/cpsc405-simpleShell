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

char** split(char *str, char *tok){
	int num_spaces = 0;
	for (int i = 0 ; str[i] != '\n' ; i++){
		if (str[i] == ' '){
			num_spaces++;
		}	
	}
	char **str_array = malloc(num_spaces *sizeof(char));
	str_array[num_spaces + 1] = NULL;
	char *token = strtok(str, tok);
	int i = 0;
	while(token != NULL){
		str_array[i] = token;
		//*str_array[i] = token;
		token = strtok(NULL, tok);
	        i++;	
	}

	return str_array;


}
