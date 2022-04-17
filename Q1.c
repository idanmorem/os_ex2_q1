#include <fcntl.h>
#include "Q1.h"

int openFile(char* name)
{
    int fd;
    fd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0)  // open failed
    {
        fprintf(stderr, "ERROR: open \"%s\" failed (%d). Exiting\n", name, fd);
        exit(2);
    }
    fprintf(stderr, "opened file %s, file descriptor is: %d\n",name, fd);
    return(fd);
}