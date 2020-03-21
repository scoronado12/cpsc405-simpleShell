#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

#define PIPE_BUFF 255

/** This is used to get the current working directory - just like bash*/

char *pwd(){
	char buff[100];
	getcwd(buff, sizeof(buff));
	char *dir = malloc(sizeof(buff));
	strcpy(dir, buff);
	return dir;

}
/*This is used to read a string without assigning a buffer size*/

char *sh_readline(){
    char *line = NULL;
    size_t buffer_sz = 0;	
    getline(&line, &buffer_sz, stdin);
    return line;
}

/*This Splits the string and returns it as an array*/

char** split(char *str, char *tok){
	int num_toks = 0;
	for (int i = 0 ; str[i] != '\n' ; i++){
		if (str[i] == tok){
			num_toks++;
		}	
	}
	char **str_array = malloc(num_toks * sizeof(char));
	str_array[num_toks + 1] = NULL;
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
	/**reset if parsed command is blank**/
	if (strcmp(line[0],"\n") == 0)	
		return 0;
	
	line[get_size(line) + 1] = NULL;
	/*parse through words of the split string don't run loop if simply pressed enter*/
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
		}else{
			printf("Regular command\n");

			int rc = fork();

			if(rc < 0){
				printf("Fork Failed!\n");
				return 2;
			}
			int fp = 0;
			if (rc == 0){
				printf("forked\n");
				/*safe to exec within child*/
				printf("execute %s\n", line[0]);
				fp = execvp(line[0],line);
				if (fp == -1){
					fprintf(stderr, "Error executing program - %s\n", strerror(errno));
					return 2;
				}
				
			}



			wait(NULL);
			break;

		}

	}

	return 0;

}
