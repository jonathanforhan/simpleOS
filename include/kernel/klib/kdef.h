/* kdef.h - kernel definitions */
#pragma once

#ifndef NULL
#define NULL ((void*)0)
#endif

#define __NEED_ptrdiff_t
#define __NEED_size_t
#define __NEED_wchar_t

#define _Addr       long
#define _Int64      long long
#define _Reg        long

typedef unsigned _Addr size_t;
typedef unsigned _Addr uintptr_t;
typedef _Addr ptrdiff_t;
typedef _Addr ssize_t;
typedef _Addr intptr_t;
typedef _Addr regoff_t;
typedef _Reg register_t;
typedef _Int64 time_t;
typedef _Int64 suseconds_t;

typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed int      int32_t;
typedef signed _Int64   int64_t;
typedef signed _Int64   intmax_t;
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned int    uint32_t;
typedef unsigned _Int64 uint64_t;
typedef unsigned _Int64 u_int64_t;
typedef unsigned _Int64 uintmax_t;

typedef void *timer_t;
typedef int clockid_t;
typedef long clock_t;

typedef int pid_t;
typedef unsigned id_t;
typedef unsigned uid_t;
typedef unsigned gid_t;
typedef int key_t;
typedef unsigned useconds_t;

typedef __builtin_va_list va_list;
typedef __builtin_va_list __isoc_va_list;

#undef _Addr
#undef _Int64
#undef _Reg

#define offsetof(type, member) ((size_t)( (char *)&(((type *)0)->member) - (char *)0 ))
