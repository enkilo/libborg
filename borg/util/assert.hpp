#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <borg/msg.hpp>

#define ASSERT_MSG MSG_BOX

static inline void assert_fail(const char *expr, const char *file, int line)
{
  ASSERT_MSG("%s:%u: Assertion (%s) failed.", file, line, expr);
  __asm__ __volatile__("int $3\n");
}

#ifdef NDEBUG
#define ASSERT(expr)  ((void)0)
#else
#define ASSERT(expr)  ((expr) ? (void)0 : (assert_fail(#expr, __FILE__, __LINE__)));
#endif

#endif // ASSERT_HPP
