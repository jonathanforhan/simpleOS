/* kassert.h - kernel assert */
#pragma once

#ifdef NDEBUG
# define assert(EX)
#else
# define assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
#endif

void __assert (const char *msg, const char *file, int line);
