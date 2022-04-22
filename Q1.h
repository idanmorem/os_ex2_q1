#ifndef OS_EX2_Q1_Q1_H
#define OS_EX2_Q1_Q1_H
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define EXIT_FAIL 1

int openFile(char* name);
void checkForkSuccess(int rc);
#endif //OS_EX2_Q1_Q1_H
