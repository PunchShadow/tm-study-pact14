#ifndef TM_H
#define TM_H 1

#  include <stdio.h>

#  define MAIN(argc, argv)              int main (int argc, char** argv)
#  define MAIN_RETURN(val)              return val

#  define GOTO_SIM()                    /* nothing */
#  define GOTO_REAL()                   /* nothing */
#  define IS_IN_SIM()                   (0)

#  define SIM_GET_NUM_CPU(var)          /* nothing */

#  define TM_PRINTF                     printf
#  define TM_PRINT0                     printf
#  define TM_PRINT1                     printf
#  define TM_PRINT2                     printf
#  define TM_PRINT3                     printf

#  define P_MEMORY_STARTUP(numThread)   /* nothing */
#  define P_MEMORY_SHUTDOWN()           /* nothing */

#  include <string.h>
#  include <stm.h>
#  include "thread.h"

#    define TM_ARG                        STM_SELF,
#    define TM_ARG_ALONE                  STM_SELF
#    define TM_ARGDECL                    STM_THREAD_T* TM_ARG
#    define TM_ARGDECL_ALONE              STM_THREAD_T* TM_ARG_ALONE
#    define TM_CALLABLE                   /* nothing */

#      include "norec.h"

#      define TM_STARTUP(numThread)     STM_STARTUP()
#      define TM_SHUTDOWN()             STM_SHUTDOWN()

#      define TM_THREAD_ENTER()         TM_ARGDECL_ALONE = STM_NEW_THREAD(); \
                                        STM_INIT_THREAD(TM_ARG_ALONE, thread_getId())
#      define TM_THREAD_EXIT()          STM_FREE_THREAD(TM_ARG_ALONE)

#      define P_MALLOC(size)            malloc(size)
#      define P_FREE(ptr)               /* free(ptr) */
#      define TM_MALLOC(size)           malloc(size)
#      define TM_FREE(ptr)              /* STM_FREE(ptr) */

#    define TM_BEGIN()                  STM_BEGIN_WR()
#    define TM_BEGIN_RO()               STM_BEGIN_RD()
#    define TM_END()                    STM_END()
#    define TM_RESTART()                STM_RESTART()

#    define P_MALLOC(size)              malloc(size)
#    define P_FREE(ptr)                 /* free(ptr) */
#    define TM_MALLOC(size)             malloc(size)
#    define TM_FREE(ptr)                /* free(ptr) */

#  define TM_EARLY_RELEASE(var)         /* nothing */

#  define TM_SHARED_READ(var)           STM_READ(var)
#  define TM_SHARED_READ_P(var)         STM_READ_P(var)
#  define TM_SHARED_READ_D(var)         STM_READ_D(var)

#  define TM_SHARED_WRITE(var, val)     STM_WRITE((var), val)
#  define TM_SHARED_WRITE_P(var, val)   STM_WRITE_P((var), val)
#  define TM_SHARED_WRITE_D(var, val)   STM_WRITE_D((var), val)

#  define TM_SHARED_READ_F(var)         ({ \
                                            float* ptr = &(var); \
                                            uintptr_t addr = (uintptr_t)ptr; \
                                            uintptr_t word_addr = addr & ~(sizeof(intptr_t)-1); \
                                            intptr_t word_val = STM_READ(*(intptr_t*)word_addr); \
                                            union { intptr_t i; float f[2]; } cvt; \
                                            cvt.i = word_val; \
                                            (addr == word_addr) ? cvt.f[0] : cvt.f[1]; \
                                        })

#  define TM_SHARED_WRITE_F(var, val)   do { \
                                            float* ptr = &(var); \
                                            uintptr_t addr = (uintptr_t)ptr; \
                                            uintptr_t word_addr = addr & ~(sizeof(intptr_t)-1); \
                                            intptr_t old_word = STM_READ(*(intptr_t*)word_addr); \
                                            union { intptr_t i; float f[2]; } cvt; \
                                            cvt.i = old_word; \
                                            if (addr == word_addr) { \
                                                cvt.f[0] = (val); \
                                            } else { \
                                                cvt.f[1] = (val); \
                                            } \
                                            STM_WRITE(*(intptr_t*)word_addr, cvt.i); \
                                        } while (0)

#  define TM_LOCAL_WRITE(var, val)      STM_LOCAL_WRITE(var, val)
#  define TM_LOCAL_WRITE_P(var, val)    STM_LOCAL_WRITE_P(var, val)
#  define TM_LOCAL_WRITE_D(var, val)    STM_LOCAL_WRITE_D(var, val)
#  define TM_LOCAL_WRITE_F(var, val)    STM_LOCAL_WRITE(var, val)

#endif /* TM_H */
