#ifndef BORG_GCCXML_ARGUMENT_HPP
#define BORG_GCCXML_ARGUMENT_HPP

#include <borg/gccxml/declaration.hpp>
#include <borg/ast/argument.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct argument_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_ARGUMENT_TYPES(typename traits)

  //----------------------------------------------------------------------------
  static string_type
  get_name(const argument_type &fn)
  {
    xml::dom::attribute_t<XmlTraits> attr = fn.get_attribute_node("name");

    return !attr ? string_type() : attr.value();
  }
  
    
};

//----------------------------------------------------------------------------
}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_ARGUMENT_HPP
