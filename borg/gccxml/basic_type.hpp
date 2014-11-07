#ifndef BORG_GCCXML_BASIC_TYPE_HPP
#define BORG_GCCXML_BASIC_TYPE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/basic_type.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct basic_type_impl< gccxml::traits<XmlTraits> >
{
  BORG_AST_BASIC_TYPE_TYPES( typename gccxml::traits<XmlTraits> )

  static bool
  is_alias(const basic_type_type &type)
  {
    return type.name() == "Typedef";
  }

  static bool
  is_pointer(const basic_type_type &type)
  {
    return type.name() == "PointerType";
  }

  static bool
  is_reference(const basic_type_type &type)
  {
    return type.name() == "ReferenceType";
  }

  static bool
  is_cv_qualified(const basic_type_type &type)
  {
    return type.name() == "CvQualifiedType";
  }
  
  static bool
  is_array(const basic_type_type &type)
  {
    return type.name() == "ArrayType";
  }
  
  static bool
  is_sized(const basic_type_type &type)
  {
    return type.get_attribute_node("size");
  }
};

//----------------------------------------------------------------------------
} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_BASIC_TYPE_HPP
