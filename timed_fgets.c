#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "timed_fgets.h"

void _timeup(int sigint) {
    printf("\nProgram timed out, exiting now.\n");
    exit(1);
}

char *timed_fgets(char *buffer, int size, FILE *stream, int seconds, char *prompt) {
    __sighandler_t old_signal_handler;
    int old_seconds, seconds_remaining;

    old_signal_handler = signal(SIGALRM, &_timeup);
    old_seconds = alarm(seconds);

    if(!buffer)
        buffer = (char*) malloc(size+1);
    if(prompt)
        fwrite(prompt,strlen(prompt), 1, stdout);
    fgets(buffer, size, stream);
    strtok(buffer, "\n");

    seconds_remaining = alarm(0);
    signal(SIGALRM, old_signal_handler);
    if (seconds - seconds_remaining < old_seconds)
        alarm(old_seconds - (seconds - seconds_remaining));
    
    return buffer;
}