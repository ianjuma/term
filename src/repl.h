#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>

static inline void config();
static inline void __clearconfig();

static int checkfile_();

static inline  __attribute__ ((always_inline)) void status(const char *ini_file);
__attribute__ ((pure)) int foo(int val);

//strict pure func()
__attribute__ ((const)) int pull(int val);

//auto -- storage class specifier
register int *if_so asm("ebx");

int x = 0;
typeof(x) p;
