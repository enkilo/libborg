#ifndef CHARACTER_PREDICATE_HPP
#define CHARACTER_PREDICATE_HPP

#include <functional>

namespace borg {

//----------------------------------------------------------------------------
template<class charT = char>
class character_predicate : public std::unary_function<charT, bool>
{
public:
  character_predicate(const charT &compare) 
    : m_cmp(compare)
  {}

  bool
  operator()(const charT &subject) const
  {
    // special case: '\0' matches all chars.
    if(m_cmp == '\0')
      return true;
    
    return (subject == m_cmp);
  }

private:
  charT const m_cmp;
};
  
}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef CHARACTER_PREDICATE_HPP
