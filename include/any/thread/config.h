/* Define if against Unix platform*/
#undef HAVE_POSIX_THREADS

/* Define if Win32 platform*/
#define HAVE_WIN32_THREADS 1

/* Define if your c++ compiler supports iostream in namespace std. */
#define HAVE_STD_IOSTREAM 1

/* Define if your c++ compiler does not support wide character stream I/O */
#undef HAVE_NO_WCHAR_T_SUPPORT_IN_STREAMS

/* Define if your c++ compiler supports STL in namespace std. */
#define HAVE_STD_STL 1

/* Define if your c++ compiler supports set_terminate and set_unexpected in namespace std. */
#undef HAVE_STD_SET_X

/* Define if your c++ compiler can explicitly instanciate templates. */
#define HAVE_NO_EXPLICIT_TEMPLATES 1

/* Define if your c++ compiler doesn't have typename. */
#undef HAVE_NO_TYPENAME

/* Define if you don't have a prototype for gethostname(). */
#undef HAVE_NO_GETHOSTNAME_PROTOTYPE

/* Define if the sockaddr_storage structure is not supported. */
#undef HAVE_NO_SOCKADDR_STORAGE

/* Define if socklen_t type is known. */
#undef HAVE_SOCKLEN_T

/* Define if there is no declaration for h_errno. */
#undef HAVE_NO_H_ERRNO_DECLARATION

/* Define if socket operations require address length of type size_t. */
#undef HAVE_SOCKETS_WITH_SIZE_T

/* Define if h_errno has a broken declaration. */
/* (HPUX 11.x defines h_errno without an extern "C" block.) */
#undef HAVE_BROKEN_H_ERRNO_DECL

/* Define if there is no getaddrinfo(). */
#undef HAVE_NO_GETADDRINFO

/* Define if there is no getnameinfo(). */
#undef HAVE_NO_GETNAMEINFO

/* Define if OS supports FSU threads. */
#undef HAVE_FSU_THREADS

/* Define if OS supports posix threads. */
#undef HAVE_POSIX_THREADS

/* Define if OS supports pthread_attr_setstacksize. */
#undef HAVE_PTHREAD_ATTR_SETSTACKSIZE

/* Define if OS supports pthread_delay_np. */
#undef HAVE_PTHREAD_DELAY_NP

/* Define if OS supports pthread_sched_yield. */
#undef HAVE_SCHED_YIELD

/* Define if OS supports pthread_yield. */
#undef HAVE_PTHREAD_YIELD

/* Define if JThreads/C++ has no support for iostreams. */
#undef HAVE_JTC_NO_IOSTREAM

/* Define if ORBacus support for IPv6 is disabled. */
#undef HAVE_DISABLE_IPV6

/* Define if ORBacus has support for licensed translators. */
#undef HAVE_OB_LICENSE

/* Define if the Event Service is available. */
#undef HAVE_OBEVENT

/* Define if the Notification is available. */
#undef HAVE_OBNOTIFY

/* Define if you have the <new> header file.  */
#undef HAVE_NEW

/* Define if you have the <iostream> header file.  */
#define HAVE_IOSTREAM 1

/* Define if you have the <sstream> header file.  */
#define HAVE_SSTREAM 1

/* Define if you have the <fstream> header file.  */
#define HAVE_FSTREAM 1

/* Define if you have the <iomanip> header file.  */
#define HAVE_IOMANIP 1

/* Define if shared libraries are used */
#undef HAVE_SHARED

/* Define to 1 if you have the <bstring.h> header file. */
#undef HAVE_BSTRING_H

/* Define to 1 if you have the <exception> header file. */
#undef HAVE_EXCEPTION

/* Define to 1 if you have the <exception.h> header file. */
#undef HAVE_EXCEPTION_H

/* Define to 1 if you have the <fcntl.h> header file. */
#undef HAVE_FCNTL_H

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* Define to 1 if you have the `malloc' library (-lmalloc). */
#undef HAVE_LIBMALLOC

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Define to 1 if you have the <sched.h> header file. */
#undef HAVE_SCHED_H

/* Define to 1 if you have the <stddef.h> header file. */
#undef HAVE_STDDEF_H

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the `strcasecmp' function. */
#undef HAVE_STRCASECMP

/* Define to 1 if you have the `strerror' function. */
#undef HAVE_STRERROR

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if you have the `strncasecmp' function. */
#undef HAVE_STRNCASECMP

/* Define to 1 if you have the <sys/param.h> header file. */
#undef HAVE_SYS_PARAM_H

/* Define to 1 if you have the <sys/sched.h> header file. */
#undef HAVE_SYS_SCHED_H

/* Define to 1 if you have the <sys/select.h> header file. */
#undef HAVE_SYS_SELECT_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/times.h> header file. */
#undef HAVE_SYS_TIMES_H

/* Define to 1 if you have the <sys/time.h> header file. */
#undef HAVE_SYS_TIME_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the <terminate.h> header file. */
#undef HAVE_TERMINATE_H

/* Define to 1 if you have the <termios.h> header file. */
#undef HAVE_TERMIOS_H

/* Define to 1 if you have the <termio.h> header file. */
#undef HAVE_TERMIO_H

/* Define to 1 if you have the <time.h> header file. */
#undef HAVE_TIME_H

/* Define to 1 if you have the <unexpected.h> header file. */
#undef HAVE_UNEXPECTED_H

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to 1 if you have the `vprintf' function. */
#undef HAVE_VPRINTF

/* Define to 1 if you have the `wcschr' function. */
#undef HAVE_WCSCHR

/* Define to 1 if you have the `wcscmp' function. */
#undef HAVE_WCSCMP

/* Define to 1 if you have the `wcscpy' function. */
#undef HAVE_WCSCPY

/* Define to 1 if you have the `wcslen' function. */
#undef HAVE_WCSLEN

/* Define to 1 if you have the `wcsncpy' function. */
#undef HAVE_WCSNCPY

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* The size of a `bool', as computed by sizeof. */
#define SIZEOF_BOOL 1

/* The size of a `char', as computed by sizeof. */
#undef SIZEOF_CHAR

/* The size of a `double', as computed by sizeof. */
#undef SIZEOF_DOUBLE

/* The size of a `float', as computed by sizeof. */
#undef SIZEOF_FLOAT

/* The size of a `int', as computed by sizeof. */
#undef SIZEOF_INT

/* The size of a `long', as computed by sizeof. */
#undef SIZEOF_LONG

/* The size of a `long double', as computed by sizeof. */
#undef SIZEOF_LONG_DOUBLE

/* The size of a `long long', as computed by sizeof. */
#undef SIZEOF_LONG_LONG

/* The size of a `short', as computed by sizeof. */
#undef SIZEOF_SHORT

/* The size of a `wchar_t', as computed by sizeof. */
#undef SIZEOF_WCHAR_T

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#undef TIME_WITH_SYS_TIME

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
#undef WORDS_BIGENDIAN

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#undef YYTEXT_POINTER
