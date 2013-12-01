#include <stdio.h>
#include <stdarg.h>


int
add_(int count, ... ){
    
    va_list ap;
    int i, sum;
    va_start (ap, count);

    sum = 0;
    for(i = 0; i < count; i++) {
        sum += va_arg (ap, int);
    }

    va_end (ap);

    return (int) sum;
}

int
main(void) {

    int sum = add_(1, 3, 5);

    printf("Sum -> %d\n", add_(1, 3, 5));
    printf("Sum -> %d\n", sum);

    return 0;
}
