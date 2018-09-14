#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

long* readMatrix(char*);
long* getColumn(int, long*);
long* getRow(int, long*);
int getLock();
int realeaseLock(int);
