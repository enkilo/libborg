#ifndef BORG_XERCES_DOM_ELEMENT_HPP
#define BORG_XERCES_DOM_ELEMENT_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct element_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)

  template<typename ElementT>
  static nodemap_type
  attributes(ElementT const &elm)
  {
    return elm->getAttributes();
  }

  //-----------------------------------------------------------------------
  //! Sets the attribute value for the specified attribute name.
  //-----------------------------------------------------------------------
  template<typename ElementT, typename StringT>
  static void
  set_attribute(ElementT const &elm, StringT const &name, StringT const &value)
  {
    return elm->setAttribute(name, value);
  }
  
  //-----------------------------------------------------------------------
  //! Returns the attribute value for the specified attribute name.
  //-----------------------------------------------------------------------
  template<typename ElementT, typename StringT>
  static const wchar_type *
  get_attribute(ElementT const &elm, StringT const &name)
  {
    return elm->getAttribute(name);
  }

  //-----------------------------------------------------------------------
  //! Returns the attribute node for the specified attribute name.
  //-----------------------------------------------------------------------
  template<typename ElementT, typename StringT>
  static attribute_type
  get_attribute_node(ElementT const &elm, StringT const &name)
  {
    return elm->getAttributeNode(name);
  }
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_ELEMENT_HPP
