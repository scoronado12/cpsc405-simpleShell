#include "shellopt.h"

void msg_prompt(void)
{
    char buff[] = "gustysh $ ";
    fprintf(stdout, "%s", buff);
    fflush(stdout);
}
