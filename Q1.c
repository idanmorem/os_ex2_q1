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
    return(fd);
}

void checkForkSuccess(int rc) {
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAIL);
    }
}

void fileRedirect(int fileToClose, int fileToOpen) {
    close(fileToClose);
    dup(fileToOpen);
    close(fileToOpen);
}

void exitArgs() {
    perror("Not enough arguments!.\n");
    exit(EXIT_FAIL);
}