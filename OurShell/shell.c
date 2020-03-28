#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
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
char line[256];

char *sh_readline(){
    size_t buffer_sz = 0;	
    getline(line, &buffer_sz, stdin);
    line[strlen(line) - 1] = '\0';
	//char *pos = strchrnul(line, '\n');
	//pos = '\0';

    return line;
}

/*This Splits the string and returns it as an array*/

char** split(char *str, char *tok){
	int num_toks = 1;
	for (int i = 0 ; str[i] != NULL ; i++){
		if (strcmp(&str[i] ,tok)== 0){ //TODO fix me not char
			num_toks++;
		}	
	}
	char **str_array = malloc((num_toks + 1) * sizeof(char*));
	str_array[num_toks + 1] = NULL;
	char *token = strtok(str, tok);
	int i = 0;

	while(token != NULL){
        //printf("TOKS %s\n", token);
        str_array[i] = malloc(strlen(token)+1);
	    strcpy(str_array[i], token);
        //str_array[i] = token;
        
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

int normal_execute(int argc, char **line){
	line[argc] = NULL;

	/**leave if parsed command is blank**/
	if (strcmp(line[0],"") == 0)	
		return 0;
        

    int fp = execvp(line[0],line);
    if (fp == -1){
        fprintf(stderr, "nenbarsh: %s \n", strerror(errno));
        return -1;
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
    int status = REGULAR; /*Assume regular command*/

    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], ">") == 0){
			printf("Output redirection\n");
            status = OUTPUT_REDIRECT;
            break;
		} else if (strcmp(argv[i],"<") == 0){
            status = INPUT_REDIRECT;
			printf("Input redirection\n");
            break;
		} else if (strcmp(argv[i], "|") == 0){
            status = PIPE;
			printf("pipe!\n");
            break;
		}else if (strcmp(argv[i], "&") == 0){
            /* https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
             */
            status = BACKGROUND;
			printf("Background\n");
            break;
		}

    }

    return status;
}

/**Returns the index of the delimiter that is to be found in the array*/

int getIndxOf(char *delim, int argc, char **argv){
    
    for (int i = 0; i < get_size(argv); i++){
        printf("Checking %s against %s\n", argv[i], delim);
        if (strcmp(delim, argv[i]) == 0){
            return i;
        }

    }

   return -1; 

}


int output_redir(char *line){
    printf("Output redirection currently not finished\n\n");
    int status = -1; //assume it never ran
    int mode = 0;
    char **line_split = split(line, ">"); /* The last index would be the recieving file */
    char cmd_to_run[250];
    char file_name[255];
     
    strncpy(cmd_to_run, line_split[0],strlen(line_split[0]) -1);
    
    printf("Copied str: :%s:\n", cmd_to_run);
    strncat(cmd_to_run, line_split[1],strlen(line_split[1]));
    printf("Unified string: %s\n",cmd_to_run);
    /* TODO split cmd string and dumpoutput into file_name */

    

    return status; 

}
