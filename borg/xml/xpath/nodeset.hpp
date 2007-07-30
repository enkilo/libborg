#ifndef BORG_XML_XPATH_NODESET_HPP
#define BORG_XML_XPATH_NODESET_HPP

#include <borg/xml/xpath/forward.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace xpath {

//---------------------------------------------------------------------------
template<class Traits>
struct nodeset_access
{
  XML_DOM_TYPES(typename Traits)
};
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct nodeset_interface
{
  XML_DOM_TYPES(typename Traits)

  typedef nodeset_impl<Traits> impl;
  
  length_type
  size() const
  {
    return impl::size(borg::dereference_cast<Derived const>(this));
  }
  
  bool empty() const
  {
    return borg::dereference_cast<Derived const>(this).size() == 0;
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct nodeset_facade
{
};
  
//---------------------------------------------------------------------------

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_XPATH_NODESET_HPP
