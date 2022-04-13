#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define EXIT_FAIL 1

int main(int argc, char *argv[]) {

    if (argc < 2)
    {
        perror("Not enough arguments!.\n");
        exit(EXIT_FAIL);
    }

    FILE* temp = fopen("merged.txt", "w");

    for (int i = 0; i < argc - 1; i++)
    {
        int rc = fork();
        if (rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            exit(EXIT_FAIL);
        }
        else if (rc == 0)
        {
            char* args[2] = {"merger", /* some arguments */ NULL};
            execvp(args[0], args);
        }
        else
        {
            int rc_wait = wait(NULL);
        }
    }
    char* args[2] = {"merger", /* some arguments */ NULL};
    execvp(args[0], args);

    return 0;
}