#include "ring_buffer.hpp"

/*inline size_t ring_buffer<float>::put(const float *s, size_t n)
{
  __asm__ __volatile__("testl %4,%4\n\t"
                                            "jz .done\n\t"
                                            ".done:\n"
                       : "=r"(m_data), "=r"(m_head), "=r"(m_tail), "=r"(m_size)
                       : "r"(m_data), "r"(m_head), "r"(m_tail), "r"(m_size), "r"(n)
                       : "memory");
  return n;
}

  
*/
