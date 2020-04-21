#include "dbug.h"

static int factorial(register int value) {
    DBUG_ENTER("factorial");
    DBUG_PRINT("find", ("find %d factorial", value));
    if (value > 1) {
        value *= factorial(value - 1);
    }
    DBUG_PRINT("result", ("result is %d", value));
    DBUG_RETURN(value);
}

int main(void) {
    DBUG_PUSH("d:t:O");
    DBUG_PROCESS("factorial");

    int init;
    scanf("%i", &init);

    int fact = factorial(init);
    printf("%i\n", fact);

    DBUG_PRINT("info", ("Factorial value: %d", fact));

    return 0;
}