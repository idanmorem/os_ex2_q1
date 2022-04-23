#ifndef OS_EX2_Q1_Q1_H
#define OS_EX2_Q1_Q1_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define EXIT_FAIL 1

void fileRedirect(int fileToClose, int fileToOpen);
int openFile(char* name);
void checkForkSuccess(int rc);
void exitArgs();

#endif //OS_EX2_Q1_Q1_H
