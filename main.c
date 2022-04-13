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
    //Will the child continue the loop and create another child?
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
            if (i == 1)
            {
                //TODO: redirect the stdin to argv[1]
                //TODO: redirect the stdout to "temp"
                char* args[3] = {"merger",  argv[2] ,NULL};
                execvp(args[0], args);
            }
            else
            {
                //TODO: redirect the stdin to temp
                //TODO: redirect the stdout to temp
                char* args[3] = {"merger", argv[i + 1] ,NULL};
                execvp(args[0], args);
            }
        }
        else
        {
            int rc_wait = wait(NULL);
        }
    }
    //TODO: redirect stdin to temp
    //TODO: redirect stdout to merged
    char* args[3] = {"merger", argv[argc-1], NULL};
    execvp(args[0], args);

    return 0;
}