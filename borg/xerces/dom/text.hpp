#ifndef BORG_XERCES_DOM_TEXT_HPP
#define BORG_XERCES_DOM_TEXT_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct text_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml

namespace xerces {
namespace dom {
  
  typedef xml::dom::text_t<xerces::traits> text_t;
  
} // namespace dom
} // namespace xerces
} // namespace borg  
  
//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_TEXT_HPP
