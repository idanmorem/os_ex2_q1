#include "Q1.h"


int main(int argc, char *argv[]) {

    if (argc < 2)
    {
        perror("Not enough arguments!.\n");
        exit(EXIT_FAIL);
    }

    int fd_in = open_file("Temp.txt");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    dup(fd_in);
    dup(fd_in);
    close(fd_in);

    for (int i = 1; i < argc - 1; i++)
    {
        int rc = fork();
        if (rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(EXIT_FAIL);
        }
        else if (rc == 0) // the child's run
        {
            char* args[3] = {"merger",  argv[i] ,NULL};
            execve(args[0], args, NULL);
        }
        else
        {
            int rc_wait = wait(NULL);
        }
    }

    int fd_out = open_file("merged.txt");
    close(STDOUT_FILENO);
    dup(fd_out);
    close(fd_out);
    char* args[3] = {"merger", argv[argc-1], NULL};
    execve(args[0], args, NULL);

    return 0;
}