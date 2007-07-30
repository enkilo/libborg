#ifndef RANGE_PREDICATE_HPP
#define RANGE_PREDICATE_HPP

#include <cstdlib>
#include <iostream>

namespace borg {

//----------------------------------------------------------------------------
class range_predicate
{
public:
  range_predicate(size_t start, size_t end)
    : m_count(0)
    , m_start(start)
    , m_end(end)
  {}

  template<class value_type>
  bool
  operator()(const value_type &v)
  {
    bool pred = (m_count >= m_start && m_count < m_end);
    
//    std::cout << "predicate(" << m_count << ", " << v << "): " << pred<< std::endl;
    
    ++m_count;
    return pred;
  }
  
private:
  size_t m_count;
  const size_t m_start;
  const size_t m_end;
};
  
}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef RANGE_PREDICATE_HPP
