#include "Q1.h"
/*how to debug using fork:
 * Enter the GDB in the debugger console and enter
 * set follow-fork-mode child
 * set detach-on-fork off */
// argc = 4, argv[4] = {program name, gr_1, gr_2, gr_3}
int main(int argc, char *argv[]) {
    int i = 1;
    char currentTemp[256];
    char previousTemp[256];

    if (argc < 3) {
        perror("Not enough arguments!.\n");
        exit(EXIT_FAIL);
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
                close(STDIN_FILENO);
                dup(fd_in);
                close(fd_in);
                char *outputFileName = strcat(currentTemp, "temp.txt");
                int fd_out = openFile(outputFileName);
                close(STDOUT_FILENO);
                dup(fd_out);
                close(fd_out);
                char *args[3] = {"merger", argv[i + 1], NULL};
                execve(args[0], args, NULL);
            } else {
                wait(NULL);
            }
        }
    }

    sprintf(previousTemp, "%d", i - 1);
    char *inputFileName = strcat(previousTemp, "temp.txt");
    int fd_in;
    int rc = fork();
    checkForkSuccess(rc);
    if (rc == 0) {
        char **args = NULL;
        if (argc == 4) {
            fd_in = openFile(argv[1]);
            args = (char **) malloc(2 * sizeof(char *));
            args[0] = "merger";
            args[1] = argv[2];
        } else {
            fd_in = openFile(inputFileName);
            args = (char **) malloc(2 * sizeof(char *));
            args[0] = "merger";
            args[1] = argv[argc - 2];
        }
        close(STDIN_FILENO);
        dup(fd_in);
        close(fd_in);
        int fd_out = openFile(argv[argc - 1]);
        close(STDOUT_FILENO);
        dup(fd_out);
        close(fd_out);
        execve(args[0], args, NULL);
    } else {
        wait(NULL);
    }

    return 0;
}
