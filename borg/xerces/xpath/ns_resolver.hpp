#ifndef BORG_XERCES_XPATH_NS_RESOLVER_HPP
#define BORG_XERCES_XPATH_NS_RESOLVER_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/xml/xpath/forward.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class ns_resolver_impl<xerces::traits>
{
public:
  XML_XPATH_TYPES(xerces::traits)
  
  //-----------------------------------------------------------------------

};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_XPATH_NS_RESOLVER_HPP
