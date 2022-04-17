#include "Q1.h"


void checkForkSuccess(int rc);

int main(int argc, char *argv[]) {

    if (argc < 2)
    {
        perror("Not enough arguments!.\n");
        exit(EXIT_FAIL);
    }
    /*
    // TODO: seperate the stdin and stdout to different files (create temporary files)
    int fdIn = openFile("Temp.txt");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    dup(fdIn);
    dup(fdIn);
    close(fdIn);
    */
    int i = 1;
    for (i; i < argc - 1; i++)
    {
        int rc = fork();
        checkForkSuccess(rc);
        if (rc == 0) // the child's run
        {
            char srcIn[256];
            sprintf(srcIn, "%d.txt", i);
            int tempIn = openFile(strcat("temp", srcIn));
            close(STDIN_FILENO);
            dup(tempIn);
            close(tempIn);
            char srcOut[256];
            sprintf(srcOut, "%d.txt", i + 1);
            int tempOut = openFile(strcat("temp", srcOut));
            close(STDOUT_FILENO);
            dup(tempOut);
            close(tempOut);
            char* args[3] = {"merger",  argv[i] ,NULL};
            execve(args[0], args, NULL);
        }
        else
        {
            pid_t wpid;
            int status = 0;
            while ((wpid = wait(&status)) > 0);
        }
    }

    char srcIn[256];
    sprintf(srcIn, "%d.txt", i + 1);
    int fdIn = openFile(strcat("temp", srcIn));
    close(STDIN_FILENO);
    dup(fdIn);
    close(fdIn);
    int fdOut = openFile("merged.txt");
    close(STDOUT_FILENO);
    dup(fdOut);
    close(fdOut);
    char* args[3] = {"merger", argv[argc-1], NULL};
    execve(args[0], args, NULL);

    return 0;
}

void checkForkSuccess(int rc) {
    if (rc < 0)
    {
        fprintf(stderr, "fork failed\n");
        exit(EXIT_FAIL);
    }
}
