
char *pwd();
char *sh_readline();
char **split(char *str, char *tok);
int get_size(char **line);
int normal_execute(int argc, char **line);
int what_command(int argc, char **argv);
