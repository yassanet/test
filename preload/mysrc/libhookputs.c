/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */
#define _STDI_H
#  include "config.h"
#  include <stdlib.h>
#  include <stdio.h>
#  include <dlfcn.h>
#  include <fcntl.h>
#  include <sys/stat.h>
#  include <sys/types.h>
#  include <unistd.h>

#  define RTLD_NEXT ((void *) -1L)

// function pointer to the original one
static int (*puts_org) (const char *s) = NULL;

__attribute__((constructor))
void
_save_original_functions()
{
    puts_org = (int(*)(const char *)) dlsym(RTLD_NEXT, "puts");
}

int
puts(s)
    const char *s;
{
    {
        char *command;

        command = getenv("HOOKEX_COMMAND");
        if (command) {
            system(command);
        }
    }
	
    return puts_org(s);
}
