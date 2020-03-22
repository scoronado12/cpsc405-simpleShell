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
	char *dir = malloc(sizeof(buff) + 1);
	strcpy(dir, buff);
	return dir;

}
/*This is used to read a string without assigning a buffer size*/

char *sh_readline(){
    char *line = NULL;
    size_t buffer_sz = 0;	
    getline(&line, &buffer_sz, stdin);
	char *pos = strchrnul(line, '\n');
	pos = '\0';

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
	/*clean each string of newlines*/
	for (int i = 0; i < get_size(str_array); i++){//each string in array
		for (int j = 0; j < strlen(str_array[i]); j++){ //each char in string
			if (str_array[i][j] == '\n')
				str_array[i][j] = '\0';
		}
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

int normal_execute(int argc, char **line){
	line[argc] = NULL;

	/**leave if parsed command is blank**/
	if (strcmp(line[0],"") == 0)	
		return 0;
	

        int rc = fork();

        if(rc < 0){
            printf("Fork Failed!\n");
            return 2;
        }

        int fp = 0;
        if (rc == 0){
            //printf("forked\n");
            /*safe to exec within child*/
            fp = execvp(line[0],line);
            if (fp == -1){
                fprintf(stderr, "nenbarsh: %s \n", strerror(errno));
                return 2;
            }
            

			wait(NULL);

		}


	return 0;

}

/* *
 * what_command() return statuses correspond with what should be done
 *
 * 0 - for regular command
 * 1 - redirect output
 * 2 - redirect input
 * 3 - pipe
 * 4 - run in background */
int what_command(int argc, char **argv){
    int status = 0; /*Assume regular command*/

    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], ">") == 0){
			printf("Output redirection\n");
            status = 1;
            break;
		} else if (strcmp(argv[i],"<") == 0){
            status = 2;
			printf("Input redirection\n");
            break;
		} else if (strcmp(argv[i], "|") == 0){
            status = 3;
			printf("pipe!\n");
            break;
		}else if (strcmp(argv[i], "&") == 0){
            /* https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
             */
            status = 4;
			printf("Background\n");
            break;
		}

    }

    return status;
}

/**Returns the index of the delimiter that is to be found in the array*/

int getIndxOf(char *delim, int argc, char **argv){

    for (int i = 0; i < get_size(argv); i++){
        if (strcmp(delim, argv[i])== 0)
            return i;
    }

   return -1; 

}
