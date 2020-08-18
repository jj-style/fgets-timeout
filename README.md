# fgets-timeout
Wrapper around fgets to provide a timeout option to exit the program if the blocking call to fgets does not read within the time frame.

`char *timed_fgets(char *buffer, int size, FILE *stream, int seconds, char *prompt);`

## Usage

```
git clone https://github.com/jj-style/fgets-timeout

<In C program>
#include "fgets-timeout/timed_fgets.h"
```
Remember to compile with the source `fgets-timeout/timed_fgets.c`

## Function Documentation
### Parameters:
* `char *buffer`    - buffer to read input into, if NULL then memory will be allocated at the given size+1
* `int size`        - size to read into buffer
* `FILE *stream`    - file stream to read to buffer
* `int seconds`     - seconds to elapse before timeout
* `char *prompt`    - prompt to output to stdout before getting input, if NULL then no prompt will be shown

### Returns:
* `char *buffer`    - the buffer with the data read in. If providing a buffer then don't need the return value. If buffer provided through malloc, remember to free it up.

### Note:
* Program exits with status code 1 if the timeout is elapsed, a timeout message is printed out.
* Existing alarm and signal handler for alarm are re-stored (with the correct offset) if the user enters within the timeframe.
