/*
 * memcpy.c
 */

#include <string.h>

void *memcpy(void *dst, const void *src, size_t n)
{
  const char *p = src;
  char *q = dst;
#if defined(__i386__)
  asm volatile("cld ; movl %0,%%edx ; shrl $2,%0 ; rep ; movsl ; "
	       "movl %%edx,%0 ; andl $3,%0 ; rep ; movsb"
	       : "+c" (n), "+S" (p), "+D" (q) :: "edx");
#elif defined(__x86_64__)
  asm volatile("cld ; movq %0,%%rdx ; shrq $3,%0 ; rep ; movsq ; "
	       "movl %%edx,%0 ; andl $7,%0 ; rep ; movsb"
	       : "+c" (n), "+S" (p), "+D" (q) :: "rdx");
#else
  while ( n-- ) {
    *q++ = *p++;
  }
#endif

  return dst;
}
