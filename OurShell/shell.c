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

//int normal_execute(int argc, char **line){
int normal_execute(char **cmd_cpy){
	//line[argc] = NULL; - eriq
    char cmd_cpy2[255];
    strcpy(cmd_cpy2, cmd_cpy);
    char **cmd_split = split(cmd_cpy2, " ");
    int i = 0;
    int built_in_status = -1;
	/**leave if parsed command is blank**/
	if (strcmp(cmd_split[0],"") == 0){
		return 0; 
    }



    if (strcmp(cmd_split[0], "cd") == 0){
      built_in_status = chdir(cmd_split[1]);
      if (built_in_status == -1)
         return -1;
     return built_in_status; 
    }

    int fp = execvp(cmd_split[0],cmd_split);

    if (fp == -1){
        fprintf(stderr, "nenbarsh: %s \n", strerror(errno));
        _exit(0);
        return -1;
    }
    free(line);    
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
//int what_command(int argc, char **argv){
int what_command(char **cmd_cpy){
    //printf("getting a NEW command\n");
    int status = REGULAR; /*Assume regular command*/
    char cmd_cpy2[255];
    strcpy(cmd_cpy2, cmd_cpy);
    char **cmd_split = split(cmd_cpy2, " ");
    int i = 0;
    // what command will take in cmd cpy and split inside here.
    /*for (int i = 0; i < argc; i++){
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
             ^/
            status = BACKGROUND;
			printf("Background\n");
            break;
		} 

    }*/
    while(cmd_split[i] != NULL){
        i++;
    }
    //printf("i was: %d\n", i);
    i = 0;
    while(cmd_split[i] != NULL){
        //printf("cmd_split[%d]: %s\n", i, cmd_split[i]);
        if(strcmp(cmd_split[i], ">")== 0){
            printf("Output redirection\n");
            status = OUTPUT_REDIRECT;
            break;
        }else if (strcmp(cmd_split[i],"<") == 0){
            status = INPUT_REDIRECT;
			printf("Input redirection\n");
            break;
		} else if (strcmp(cmd_split[i], "|") == 0){
            status = PIPE;
			printf("pipe!\n");
            break;
		}else if (strcmp(cmd_split[i], "&") == 0){
            /* https://stackoverflow.com/questions/8319484/regarding-background-processes-using-fork-and-child-processes-in-my-dummy-shel
             */
            status = BACKGROUND;
			printf("Background\n");
            break;
		}
        i++;
    }
    //printf("status is %d\n", status);
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

/* 
 * Output Redirection */

int output_redir(char *line){

    int status = -1; //assume it never ran
    int mode = 0;

    // start of eriq shitty code
    char **line_split = split(line, ">"); /* The last index would be the recieving file */
    char cmd_to_run[250];
    char file_name[255];
    strncpy(cmd_to_run, line_split[0],strlen(line_split[0]) -1);
    strcpy(file_name, line_split[get_size(line_split)-1]);
    memmove(&file_name[0], &file_name[1], strlen(file_name) - 0);
    //printf("Running '%s' on '%s'\n", cmd_to_run, pipe_txt);
    char **cmd_split = split(cmd_to_run, " ");
    char **pipe_split = split(file_name, " ");
    //end of eriq shitty code
    /*
    char **line_split = split(line, ">"); /* The last index would be the recieving file //
    char cmd_to_run[250];
    char file_name[255];
     
    strncpy(cmd_to_run, line_split[0],strlen(line_split[0]) -1);
    
    /* TODO split cmd string and dumpoutput into file_name //
    int str_size = 0;
    strcpy(file_name, line_split[get_size(line_split)-1]);
    */
    int str_size = 0;
    for (int i = 0; file_name[i] != NULL; i++){
        if (file_name[i] != ' ')
            file_name[str_size++] = file_name[i];
    }

    file_name[str_size] = '\0';


    free(line_split);

    //char **cmd_split = split(cmd_to_run, " ");

    close(1);
    mode = O_WRONLY| O_CREAT;

    if (open(file_name, mode, S_IRUSR| S_IWUSR| S_IRGRP | S_IROTH) < 0){
        fprintf(stderr, "Opening of %s failed!\n" ,file_name);
        free(cmd_split);
        return status;
    }
    

    int exec = execvp(cmd_split[0], cmd_split);
    if (exec == -1){
        status = -1;
    } else {
        status = 0;
    }

    free(cmd_split);
    return status; 

}

/* 
 * Input Redirection */

int input_redir(char *line){
    int status = -1; //assume it never ran
    int mode = 0;

    //start of eriq shitty code
    char **line_split = split(line, "<"); /* The last index would be the recieving file */
    char cmd_to_run[250];
    char file_name[255];
    strncpy(cmd_to_run, line_split[0],strlen(line_split[0]) -1);
    strcpy(file_name, line_split[get_size(line_split)-1]);
    memmove(&file_name[0], &file_name[1], strlen(file_name) - 0);
    //printf("Running '%s' on '%s'\n", cmd_to_run, pipe_txt);
    char **cmd_split = split(cmd_to_run, " ");
    char **pipe_split = split(file_name, " ");
    //end of eriq shitty code
    /*
    char **line_split = split(line, "<"); /* The last index would be the recieving file 
    char cmd_to_run[250];
    char file_name[255];
    
    */
    int str_size = 0;
    strcpy(file_name, line_split[get_size(line_split)-1]);
    for (int i = 0; file_name[i] != NULL; i++){
        if (file_name[i] != ' ')
            file_name[str_size++] = file_name[i];
    }


    free(line_split);

    //char **cmd_split = split(cmd_to_run, " ");
    close(0);
    mode = O_RDONLY;
    file_name[strlen(file_name) -1] = '\0';
    printf("filename: '%s'\n", file_name);
    if (open(file_name, mode, S_IRUSR| S_IWUSR| S_IRGRP | S_IROTH) < 0){
        fprintf(stderr, "Opening of %s failed!\n" ,file_name);
        free(cmd_split);
        return status;
    }

    int exec = execvp(cmd_split[0], cmd_split);
    if (exec == -1){
        status = -1;
    } else {
        status = 0;
    }

    free(cmd_split);
    return status; 

}

int pipe_cmd(char* line){
    //printf("Piping command: %s\n", line);
    int status = -1;
    int mode = 0;
    pid_t childPid;
    int fd[2];
    pipe(fd);
    char **line_split = split(line, "|"); /* The last index would be the recieving file */
    char cmd_to_run[250];
    char pipe_txt[255];
    strncpy(cmd_to_run, line_split[0],strlen(line_split[0]) -1);
    strcpy(pipe_txt, line_split[get_size(line_split)-1]);
    memmove(&pipe_txt[0], &pipe_txt[1], strlen(pipe_txt) - 0);
    //printf("Running '%s' on '%s'\n", cmd_to_run, pipe_txt);
    char **cmd_split = split(cmd_to_run, " ");
    char **pipe_split = split(pipe_txt, " ");

    //int i = 0;
    //int in = 0;
    /*
    while(cmd_split[i] != NULL){
        printf("cmd line %d is '%s'\n", i, cmd_split[i]);
        i++;
    }
    while(pipe_split[in] != NULL){
        printf("pipe line %d is '%s'\n", in, pipe_split[in]);
        in++;
    }
    */
   
    if(pipe(fd) == -1){
        printf("fork fail");
        error("fork failed\n");
        _exit(0);
    }
    childPid = fork();
    if(childPid < 0){
        printf("fork failed\n");
        _exit(0);
    }
    if(childPid == 0){
        //printf("in child\n");
        dup2(fd[1],1);
        close(fd[0]);
        close(fd[1]);
        int fp = execvp(cmd_split[0],cmd_split);
        if(fp == -1){
            printf("failed to execute child\n");
            _exit(0);
        }
        error("failed to exec command 1");
        _exit(0);

    } else {
        int status = 0;
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        fflush(0);
        int exec = execvp(pipe_split[0], pipe_split);
        if(exec == -1){
            printf("failed again");
            _exit(0);
        }
    }
    /*
    int fp = execvp(cmd_split[0], cmd_split);
    printf("fp is: %d", fp);
    free(cmd_split);
    free(line);*/
    //printf("what is going on\n");
    _exit(0);
    return 0;
    
}

int background_cmd(char *line){
    char line_cpy[255];
    strcpy(line_cpy, line);
    int linelen = strlen(line_cpy);
    line_cpy[linelen -1] = '\0';
    linelen = strlen(line_cpy);
    line_cpy[linelen -1] = '\0';
    linelen = strlen(line_cpy);
    char **cmd_line = split(line_cpy, " ");
    int j = 0;

    printf("[+]%d\n", getpid());
    if (execvp(cmd_line[0], cmd_line) == -1){
        printf("[-]%d\n", getpid());
        _exit(0);
        return -1;
    }
    

    return 0;
}