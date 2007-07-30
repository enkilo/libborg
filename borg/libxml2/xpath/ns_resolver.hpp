#ifndef BORG_LIBXML2_XPATH_NS_RESOLVER_HPP
#define BORG_LIBXML2_XPATH_NS_RESOLVER_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/xml/xpath/forward.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class ns_resolver_impl<libxml2::traits>
{
public:
  XML_XPATH_TYPES(libxml2::traits)
  
  //-----------------------------------------------------------------------

};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_NS_RESOLVER_HPP
