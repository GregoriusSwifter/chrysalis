#include <freestanding.h>

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xe2dee396
#else
#define STACK_CHK_GUARD 0x595e9fbd94fda766
#endif

uintptr_t extern __stack_chk_guard;
__attribute__((__noreturn__)) void __stack_chk_fail(void);
