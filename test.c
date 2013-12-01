#include "gcc_attributes.h"

inline __pure int foo() {
    return 10;
}

int main() {
    foo();
}
