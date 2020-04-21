#include "dependencies.h"

pthread_key(struct st_my_thread_var *, THR_KEY_mysys);

char _dig_vec_upper[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char _dig_vec_lower[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char *strmake(register char *dst, register const char *src, size_t length) {
#ifdef EXTRA_DEBUG
    /*
      'length' is the maximum length of the string; the buffer needs
      to be one character larger to accomodate the terminating '\0'.
      This is easy to get wrong, so we make sure we write to the
      entire length of the buffer to identify incorrect buffer-sizes.
      We only initialise the "unused" part of the buffer here, a) for
      efficiency, and b) because dst==src is allowed, so initialising
      the entire buffer would overwrite the source-string. Also, we
      write a character rather than '\0' as this makes spotting these
      problems in the results easier.
    */
    uint n = 0;
    while (n < length && src[n++])
        ;
    memset(dst + n, (int)'Z', length - n + 1);
#endif

    while (length--)
        if (!(*dst++ = *src++))
            return dst - 1;
    *dst = 0;
    return dst;
}

char *strmov(register char *dst, register const char *src) {
    while ((*dst++ = *src++))
        ;
    return dst - 1;
}

char *strnmov(register char *dst, register const char *src, size_t n) {
    while (n-- != 0) {
        if (!(*dst++ = *src++)) {
            return (char *)dst - 1;
        }
    }
    return dst;
}

char *int10_to_str(long int val, char *dst, int radix) {
    char buffer[65];
    register char *p;
    long int new_val;
    unsigned long int uval = (unsigned long int)val;

    if (radix < 0) /* -10 */
    {
        if (val < 0) {
            *dst++ = '-';
            /* Avoid integer overflow in (-val) for LONGLONG_MIN (BUG#31799). */
            uval = (unsigned long int)0 - uval;
        }
    }

    p = &buffer[sizeof(buffer) - 1];
    *p = '\0';
    new_val = (long)(uval / 10);
    *--p = '0' + (char)(uval - (unsigned long)new_val * 10);
    val = new_val;

    while (val != 0) {
        new_val = val / 10;
        *--p = '0' + (char)(val - new_val * 10);
        val = new_val;
    }
    while ((*dst++ = *p++) != 0)
        ;
    return dst - 1;
}

struct st_my_thread_var *_my_thread_var(void) {
    return my_pthread_getspecific(struct st_my_thread_var *, THR_KEY_mysys);
}

my_thread_id my_thread_dbug_id() {
    return my_thread_var->id;
}

#ifdef DBUG_OFF
const char *my_thread_name(void) {
    return "no_name";
}

#else

const char *my_thread_name(void) {
    char name_buff[100];
    struct st_my_thread_var *tmp = my_thread_var;
    if (!tmp->name[0]) {
        my_thread_id id = my_thread_dbug_id();
        sprintf(name_buff, "T@%lu", (ulong)id);
        strmake(tmp->name, name_buff, THREAD_NAME_SIZE);
    }
    return tmp->name;
}

extern void **my_thread_var_dbug() {
    struct st_my_thread_var *tmp =
        my_pthread_getspecific(struct st_my_thread_var *, THR_KEY_mysys);
    return tmp && tmp->init ? &tmp->dbug : 0;
}
#endif

size_t my_vsnprintf(char *to, size_t n, const char *fmt, va_list ap) {
    return vsnprintf(to, n, fmt, ap); // just vsnprintf it
}

size_t my_snprintf(char *to, size_t n, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    size_t result = snprintf(to, n, fmt, args); // just snprintf it
    va_end(args);
    return result;
}
