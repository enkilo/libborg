#ifndef BORG_LIBXML2_DOM_ELEMENT_HPP
#define BORG_LIBXML2_DOM_ELEMENT_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/libxml2/dom/node.hpp>
#include <borg/libxml2/string.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct element_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //-----------------------------------------------------------------------
  static nodemap_type
  attributes(element_type const &elm)
  {
    return (nodemap_type)((element_type)elm)->properties;
  }
  
  //-----------------------------------------------------------------------
  //! Returns the attribute value for the specified attribute name.
  //-----------------------------------------------------------------------
  static wchar_type *    
  get_attribute(element_type const &elm, const wchar_type *name)
  {
    return xmlGetProp(elm, name);
  }

  //-----------------------------------------------------------------------
  //! Returns the attribute node for the specified attribute name.
  //-----------------------------------------------------------------------
//  template<class CharT>
  static attribute_type
  get_attribute_node(element_type const &elm, const wchar_type *name)
  {
//    std::cout << "xmlHasProp(" << (void *)elm << ", " << (const wchar_type *)name << ")" << std::endl;
    
    return xmlHasProp((node_type)(element_type)elm, (const wchar_type *)name);
  }

  static attribute_type
  get_attribute_node_ns
    (element_type const &elm, const wchar_type *name, const wchar_type *ns)
  {
    return xmlHasNsProp((node_type)(element_type)elm, name, ns);
  }
};

} // namespace dom
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::element_t<traits> element_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_ELEMENT_HPP
