#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "timed_fgets.h"


pthread_t thread;

// signal handler for SIGALRM
void _alarm_timeup(int sigint) {
    tmdout = 1;
    pthread_cancel(thread);
}

// arguments to pass to fgets in thread function
struct _pthread_fgets_arg {
    char *buffer;
    int size;
    FILE *stream;
};

// thread function running fgets and stripping trailing newline
void *_pthread_fgets(void *arg) {
    struct _pthread_fgets_arg *_args = (struct _pthread_fgets_arg *) arg;
    fgets( _args->buffer, _args->size, _args->stream);
    strtok(_args->buffer, "\n");
}

char *timed_fgets(char *buffer, int size, FILE *stream, int seconds, char *prompt) {
    __sighandler_t old_signal_handler;
    int old_seconds, seconds_remaining;
    struct _pthread_fgets_arg thread_args;
    tmdout = 0;

    old_signal_handler = signal(SIGALRM, &_alarm_timeup);
    old_seconds = alarm(seconds);

    if(prompt)
        fwrite(prompt,strlen(prompt), 1, stdout);

    if(!buffer)
        thread_args.buffer = (char *) malloc(size+1);
    else
        thread_args.buffer = buffer;
    thread_args.size = size;
    thread_args.stream = stream;
    pthread_create(&thread, NULL, _pthread_fgets, (void*) &thread_args);
    pthread_join(thread, NULL);

    seconds_remaining = alarm(0);
    signal(SIGALRM, old_signal_handler);
    if (seconds - seconds_remaining < old_seconds)
        alarm(old_seconds - (seconds - seconds_remaining));    
    return thread_args.buffer;
}