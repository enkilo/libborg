#ifndef BORG_GCCXML_TYPED_HPP
#define BORG_GCCXML_TYPED_HPP

#include <boost/lexical_cast.hpp>
#include <borg/gccxml/traits.hpp>
#include <borg/ast/typed.hpp>
#include <borg/util/exception.hpp>
#include <borg/xml/dom/attribute.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct typed_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_TYPED_TYPES( typename traits )

  //----------------------------------------------------------------------------
  static basic_type_type
  get_type(const typed_type &typed)
  {
    xml::dom::attribute_t<XmlTraits> attr = 
      typed.get_attribute_node("type");
    
    if(!attr)
      attr = typed.get_attribute_node("returns");

    if(!attr)
      throw exception<traits>("Unable to find type attribute");
    
    xml::dom::idref_t<XmlTraits> idref(attr);
/*    basic_type_type t = 
      typed.owner_document().get_element_by_id(attr.value());
    
    if(!t)
      throw exception<traits>
        ("Unable to find type with id=" +
         stdcxx::string(attr.value().begin(), attr.value().end()));*/
    
    return *idref;
  }
};

//----------------------------------------------------------------------------
}// namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_TYPED_HPP
