#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include "stdio.h"
#include <string.h>

static void itoa(int num,char* s,int* i);
void i_toa(int num,char* s);

int power(int num,int n);

void appendStr(char** dest,const char* src);

static void ftoa(int num,char* s,int* i,int p);
void f_toa(float num,char* s);

int getRandom(int upper,int lower);

#endif
