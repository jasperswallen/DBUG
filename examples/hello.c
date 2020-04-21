#include "dbug.h"

static int sub1(void);
static void sub2(char *arg);

static int sub1(void) {
    DBUG_ENTER("sub1");

    sub2("Hello world!");
    sub2("Hello earth!");
    sub2("Hello programmer!");

    DBUG_RETURN(0);
}

static void sub2(char *arg) {
    DBUG_ENTER("sub2");
    DBUG_PRINT("info", ("Got argument: '%s'", arg));

    printf("%s\n", arg);

    DBUG_VOID_RETURN;
}

int main(void) {
    int ret = 0;
    DBUG_PUSH("d:t:O");
    DBUG_PROCESS("hello");

    ret = sub1();
    DBUG_PRINT("info", ("Returned value: %d", ret));

    return 0;
}
