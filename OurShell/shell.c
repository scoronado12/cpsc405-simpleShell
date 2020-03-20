#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shell.h"

#define PIPE_BUFF 255

/*This is used to read a string without assigning a buffer size*/

char *sh_readline(){
    char *line = NULL;
    ssize_t buffer_sz = 0;	
    getline(&line, &buffer_sz, stdin);
    return line;
}

/*This Splits the string and returns it as an array*/

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
/**Get Size of String or Cmd Array*/

int get_size(char **line){
	int counter = 0;

	while(line[counter] != NULL)
		counter++;
	return counter;

}

/*Parses Through the array and decides what to do with it*/

int parseNrun(int argc, char **line){
	/*parse through words of the split string*/
	for (int i = 0; i < argc; i++){
		printf("Checking %s\n", line[i]);

		if (strcmp(line[i], ">") == 0){
			printf("Output redirection\n");
		} else if (strcmp(line[i],"<") == 0){
			printf("Input redirection\n");
		} else if (strcmp(line[i], "|") == 0){
			printf("pipe!\n");
		}else if (strcmp(line[i], "&") == 0){
			printf("Background\n");
		}

	}

	return 0;

}
