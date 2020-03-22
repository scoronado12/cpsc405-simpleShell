enum cmd_types{REGULAR, OUTPUT_REDIRECT, INPUT_REDIRECT, PIPE, BACKGROUND};
char *pwd();
char *sh_readline();
char **split(char *str, char *tok);
int get_size(char **line);
int normal_execute(int argc, char **line);
int what_command(int argc, char **argv);
