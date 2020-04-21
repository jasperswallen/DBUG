#ifdef DBUG_OFF

int factorial(register int value) {
    if (value > 1) {
        value *= factorial(value - 1);
    }
    return value;
}

#else

#include "dbug.h"

int factorial(register int value) {
    DBUG_ENTER("factorial");
    DBUG_PRINT("find", ("find %d factorial", value));
    if (value > 1) {
        value *= factorial(value - 1);
    }
    DBUG_PRINT("result", ("result is %d", value));
    DBUG_RETURN(value);
}

#endif

int main(int argc, char **argv) {
    printf("Factorial: ");
    int c;
    scanf("%i", &c);
    printf("%i\n", factorial(c));
}
