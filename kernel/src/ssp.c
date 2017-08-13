#include <k/ssp.h>
#include <freestanding.h>
#include <stdio.h>

uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((__noreturn__))
void __stack_chk_fail(void) {
#if __STDC_HOSTED__
    abort();
#elif __SWARM_OS__
    printf("Stack smashing detected\n");
#endif
#if __has_builtin(__builtin_unreachable)
    __builtin_unreachable();
#endif
}
