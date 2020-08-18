#include <stdio.h>

int tmdout; // timed out. 1 if timed out, 0 otherwise.

/*
    Wrapper around fgets to provide a timeout option to end the blocking call to fgets if it does not read within the time frame.

    Parameters:
        char *buffer    - buffer to read input into, if NULL then memory will be allocated at the given size+1
        int size        - size to read into buffer
        FILE *stream    - file stream to read to buffer
        int seconds     - seconds to elapse before timeout
        char *prompt    - prompt to output to stdout before getting input, if NULL then no prompt will be shown

    Returns:
        char *buffer    - the buffer with the data read in. If providing a buffer then don't need the return value.
                            If buffer provided through malloc, remember to free it up.

    Note:
        Sets global variable tmdout to 1 if it timed out, 0 otherwise.
        Existing alarm and signal handler for alarm are re-stored (with the correct offset) if the user enters within the timeframe.
    
*/
char *timed_fgets(char *buffer, int size, FILE *stream, int seconds, char *prompt);