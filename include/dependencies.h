#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#if !defined(HAVE_UINT)
#undef HAVE_UINT
#define HAVE_UINT
typedef unsigned int uint;
typedef unsigned short ushort;
#endif

#ifndef TRUE
#define TRUE (1)  /* Logical true */
#define FALSE (0) /* Logical false */
#endif

typedef char my_bool;        /* Small bool */
typedef unsigned long ulong; /* Short for unsigned long */
typedef unsigned char uchar; /* Short for unsigned char */
typedef ulong my_thread_id;
#define NullS (char *)0
extern char _dig_vec_upper[];
extern char _dig_vec_lower[];
#define THREAD_NAME_SIZE 10

struct st_my_thread_var {
    int thr_errno;
    // mysql_cond_t suspend;
    // mysql_mutex_t mutex;
    // mysql_mutex_t * volatile current_mutex;
    // mysql_cond_t * volatile current_cond;
    pthread_t pthread_self;
    my_thread_id id;
    int cmp_length;
    int volatile abort;
    my_bool init;
    struct st_my_thread_var *next, **prev;
    void *opt_info;
    void *stack_ends_here;
#ifndef DBUG_OFF
    void *dbug;
    char name[THREAD_NAME_SIZE + 1];
#endif
};

#if defined(HAVE_LONG_LONG) && SIZEOF_LONG_LONG == 8
typedef unsigned long long int ulonglong; /* ulong or unsigned long long */
typedef long long int longlong;
#else
typedef unsigned long ulonglong; /* ulong or unsigned long long */
typedef long longlong;
#endif
#define my_thread_var (_my_thread_var())
extern struct st_my_thread_var *_my_thread_var(void) __attribute__((const));
extern void **my_thread_var_dbug();
extern const char *my_thread_name(void);
extern char *int10_to_str(long val, char *dst, int radix);

/* additional file share flags for win32 */
#ifdef __WIN__
#define _SH_DENYRWD 0x110 /* deny read/write mode & delete */
#define _SH_DENYWRD 0x120 /* deny write mode & delete      */
#define _SH_DENYRDD 0x130 /* deny read mode & delete       */
#define _SH_DENYDEL 0x140 /* deny delete only              */
#endif                    /* __WIN__ */

/* General constants */
#define FN_LEN 256     /* Max file name len */
#define FN_HEADLEN 253 /* Max length of filepart of file name */
#define FN_EXTLEN 20   /* Max length of extension (part of FN_LEN) */
#define FN_REFLEN 512  /* Max length of full path-name */
#define FN_EXTCHAR '.'
#define FN_HOMELIB '~'    /* ~/ is used as abbrev for home dir */
#define FN_CURLIB '.'     /* ./ is used as abbrev for current dir */
#define FN_PARENTDIR ".." /* Parent directory; Must be a string */

#ifdef _WIN32
#define FN_LIBCHAR '\\'
#define FN_LIBCHAR2 '/'
#define FN_DIRSEP "/\\" /* Valid directory separators */
#define FN_EXEEXT ".exe"
#define FN_SOEXT ".dll"
#define FN_ROOTDIR "\\"
#define FN_DEVCHAR ':'
#define FN_NETWORK_DRIVES /* Uses \\ to indicate network drives */
#define FN_NO_CASE_SENCE  /* Files are not case-sensitive */
#else
#define FN_LIBCHAR '/'
#define FN_LIBCHAR2 '/'
#define FN_DIRSEP "/" /* Valid directory separators */
#define FN_EXEEXT ""
#define FN_SOEXT ".so"
#define FN_ROOTDIR "/"

#define HAVE_PERROR
#endif

#ifndef strmov
#define strmov_overlapp(A, B) strmov(A, B)
#define strmake_overlapp(A, B, C) strmake(A, B, C)
extern char *strmov(char *dst, const char *src);
#else
extern char *strmov_overlapp(char *dst, const char *src);
#endif
extern char *strnmov(char *dst, const char *src, size_t n);

#define max(a, b)                                                              \
    ({                                                                         \
        __typeof__(a) _a = (a);                                                \
        __typeof__(b) _b = (b);                                                \
        _a > _b ? _a : _b;                                                     \
    })
#define min(a, b)                                                              \
    ({                                                                         \
        __typeof__(a) _a = (a);                                                \
        __typeof__(b) _b = (b);                                                \
        _a < _b ? _a : _b;                                                     \
    })
#ifndef ATTRIBUTE_FORMAT
#define ATTRIBUTE_FORMAT(style, m, n) __attribute__((format(style, m, n)))
#endif

size_t my_snprintf(char *to, size_t n, const char *fmt, ...);
size_t my_vsnprintf(char *to, size_t n, const char *fmt, va_list ap);

#if !defined(HAVE_NONPOSIX_PTHREAD_GETSPECIFIC)
#define my_pthread_getspecific(A, B) ((A)pthread_getspecific(B))
#else
#define my_pthread_getspecific(A, B) ((A)my_pthread_getspecific_imp(B))
void *my_pthread_getspecific_imp(pthread_key_t key);
#endif
#define pthread_key(T,V) pthread_key_t V
