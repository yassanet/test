/* vim: set expandtab tabstop=4 shiftwidth=4 softtabstop=4: */

#if HAVE_CONFIG_H
#  include "config.h"
#endif
#if STDC_HEADERS
#  include <stdlib.h>
#else
#  if !HAVE_UTIME
#    error "the system which dose not have utime is not supported yet"
#  endif
#endif
#if HAVE_DLFCN_H
#  include <dlfcn.h>
#endif
#if HAVE_FCNTL_H
#  include <fcntl.h>
#endif
#if HAVE_SYS_STAT_H
#  include <sys/stat.h>
#endif
#if HAVE_SYS_TYPES_H
#  include <sys/types.h>
#endif
#if HAVE_UNISTD_H
#  include <unistd.h>
#endif

#if ! defined(RTLD_NEXT)
#  define RTLD_NEXT ((void *) -1L)
#endif

// function pointer to the original one
static ssize_t (*write_org) (int fd, const void *buf, size_t count) = NULL;

__attribute__((constructor))
void
_save_original_functions()
{
    write_org = (int(*)(const char *)) dlsym(RTLD_NEXT, "write");
}

int
write(s)
    const char *s;
{
    {
        char *update_file;

        update_file = getenv("HOOKWRITE_UPDATE_FILE");
        if (update_file) {
            int fd;
            fd = open(update_file, O_WRONLY|O_NONBLOCK|O_CREAT|O_NOCTTY, 0666);
            close(fd);
            utime(update_file, NULL);
        }
    }

    {
        char *command;

        command = getenv("HOOKWRITE_COMMAND");
        if (command) {
            system(command);
        }
    }

    return write_org(s);
}
