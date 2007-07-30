#ifndef BORG_XERCES_XPATH_EXPRESSION_HPP
#define BORG_XERCES_XPATH_EXPRESSION_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/xpath/expression.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class expression_impl<xerces::traits>
{
public:
  XML_XPATH_TYPES(xerces::traits)
  
  //-----------------------------------------------------------------------

};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_XPATH_EXPRESSION_HPP
