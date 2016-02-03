#ifndef XML_XPATH_NS_RESOLVER_HPP
#define XML_XPATH_NS_RESOLVER_HPP

#include <borg/xml/dom/node.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/xml/xpath/forward.hpp>
#include <borg/util/dereference_cast.hpp>

namespace xml {
namespace xpath {

using borg::dereference_cast;
  
//---------------------------------------------------------------------------
template<class Traits>
struct ns_resolver_impl
{
  XML_XPATH_TYPES(typename Traits)
  
};
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct ns_resolver_interface
{
  XML_XPATH_TYPES(typename Traits)

  typedef ns_resolver_impl<Traits> impl;
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct ns_resolver_facade
{
};
  
//---------------------------------------------------------------------------

}// namespace xpath
}// namespace xml

//---------------------------------------------------------------------------
#endif //ndef XML_XPATH_NS_RESOLVER_HPP
