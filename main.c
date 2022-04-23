#include "Q1.h"

int main(int argc, char *argv[]) {
    int i = 1;
    char currentTemp[256];
    char previousTemp[256];

    if (argc < 3) {
        exitArgs();
    } else if (argc > 4) {
        for (; i < argc - 3; i++) {
            sprintf(currentTemp, "%d", i);
            sprintf(previousTemp, "%d", i - 1);
            int rc = fork();
            checkForkSuccess(rc);
            if (rc == 0) {
                char *inputFileName = strcat(previousTemp, "temp.txt");
                int fd_in;
                if (i == 1) {
                    fd_in = openFile(argv[1]);
                } else {
                    fd_in = openFile(inputFileName);
                }
                fileRedirect(STDIN_FILENO, fd_in);
                char *outputFileName = strcat(currentTemp, "temp.txt");
                int fd_out = openFile(outputFileName);
                fileRedirect(STDOUT_FILENO, fd_out);
                char *args[3] = {"merger", argv[i + 1], NULL};
                execve(args[0], args, NULL);
            } else {
                wait(NULL);
            }
        }
    }

    //Only two files to merge/two files left to merge
    sprintf(previousTemp, "%d", i - 1);
    char *inputFileName = strcat(previousTemp, "temp.txt");
    int fd_in;
    int rc = fork();
    checkForkSuccess(rc);
    if (rc == 0) {
        char **args = NULL;
        if (argc == 4) { //Only two files to merge
            fd_in = openFile(argv[1]);
            args = (char **) malloc(2 * sizeof(char *));
            args[0] = "merger";
            args[1] = argv[2];
        } else { //Two files left to merge
            fd_in = openFile(inputFileName);
            args = (char **) malloc(2 * sizeof(char *));
            args[0] = "merger";
            args[1] = argv[argc - 2];
        }
        fileRedirect(STDIN_FILENO, fd_in);
        int fd_out = openFile(argv[argc - 1]);
        fileRedirect(STDOUT_FILENO, fd_out);
        execve(args[0], args, NULL);
    } else {
        wait(NULL);
    }

    return 0;
}