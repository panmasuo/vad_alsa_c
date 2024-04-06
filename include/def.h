/* file for project defines and includes */
#ifndef DEF_H_
#define DEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <semaphore.h>


#define SUCCESS 0
#define FAILURE 1

#define ALSA_PCM_NEW_HW_PARAMS_API

#define DELAY           10000       // us

pthread_mutex_t mx_sync1, signal_buffer_lock;
short *real_buffer;   // global variable for acquired pcm signal

/* time calculating */
double total_time;
clock_t start, end;

#endif
