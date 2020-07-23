#ifndef __HEADER_H_
#define __HEADER_H_ 5
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int store[5];

void *customer(void *param);
void *customer_key();
void *worker(void *param);

#endif
