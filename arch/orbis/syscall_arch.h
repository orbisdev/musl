#define __SYSCALL_LL_E(x) (x)
#define __SYSCALL_LL_O(x) (x)

#include <errno.h>
#include <stdio.h>
#include "bits/syscall.h"
#include "orbis/brk.h"

#define __NR_NON_NATIVE 10000

static __inline long __orbis_syscall_interp(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
    //if (n != SYS_poll && n != SYS_clock_gettime)
    //    sceClibPrintf("musl: syscall called: %i: %s\n", n, __lookup_syscall_name(n));

    switch (n)
    {
		SYS_BRK:
			return __orbis_brk((void *)a1);
		default:
            printf("musl: unhandled syscall called: %i\n", n);
    }

    return -ENOSYS;
}

static __inline long __syscall0(long n)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, 0, 0, 0, 0, 0, 0);
	} else {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall1(long n, long a1)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, 0, 0, 0, 0, 0);
	} else {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall2(long n, long a1, long a2)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, a2, 0, 0, 0, 0);
	} else {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2)
						  : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall3(long n, long a1, long a2, long a3)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, a2, a3, 0, 0, 0);
	} else {
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							"d"(a3) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall4(long n, long a1, long a2, long a3, long a4)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, a2, a3, a4, 0, 0);
	} else {		
		register long r10 __asm__("r10") = a4;
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							"d"(a3), "r"(r10): "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall5(long n, long a1, long a2, long a3, long a4, long a5)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, a2, a3, a4, a5, 0);
	} else {
		register long r10 __asm__("r10") = a4;
		register long r8 __asm__("r8") = a5;
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							"d"(a3), "r"(r10), "r"(r8) : "rcx", "r11", "memory");
	}
	return ret;
}

static __inline long __syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)
{
	unsigned long ret;
	if (n > __NR_NON_NATIVE) {
		ret = __orbis_syscall_interp(n, a1, a2, a3, a4, a5, a6);
	} else {
		register long r10 __asm__("r10") = a4;
		register long r8 __asm__("r8") = a5;
		register long r9 __asm__("r9") = a6;
		__asm__ __volatile__ ("syscall" : "=a"(ret) : "a"(n), "D"(a1), "S"(a2),
							"d"(a3), "r"(r10), "r"(r8), "r"(r9) : "rcx", "r11", "memory");
	}
	return ret;
}

#define VDSO_USEFUL
#define VDSO_CGT_SYM "__vdso_clock_gettime"
#define VDSO_CGT_VER "LINUX_2.6"
#define VDSO_GETCPU_SYM "__vdso_getcpu"
#define VDSO_GETCPU_VER "LINUX_2.6"

#define IPC_64 0
