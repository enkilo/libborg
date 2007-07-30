#ifndef BORG_XML_XPATH_EXPRESSION_HPP
#define BORG_XML_XPATH_EXPRESSION_HPP

#include <borg/xml/xpath/adapters.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace xpath {

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct expression_interface : expression_impl<Traits>
{
  XML_DOM_TYPES(typename Traits)

  typedef expression_impl<Traits> impl;

/*  template<class StringT>
  static expression_t
  compile(const StringT &str)
  {
    return impl::compile(str);
  }*/
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct expression_facade
{
};
  
//---------------------------------------------------------------------------

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_XPATH_EXPRESSION_HPP
