enum cmd_types{REGULAR=0, OUTPUT_REDIRECT, INPUT_REDIRECT, PIPE, BACKGROUND};
char *pwd();
char *sh_readline();
char **split(char *str, char *tok);
int get_size(char **line);
int normal_execute(int argc, char **line);
int what_command(int argc, char **argv);
int getIndxOf(char *delim, int argc, char **argv);
