#ifndef BORG_GCCXML_ARRAY_TYPE_HPP
#define BORG_GCCXML_ARRAY_TYPE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/array_type.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct array_type_impl< gccxml::traits<XmlTraits> >
{
  BORG_AST_ARRAY_TYPE_TYPES( typename gccxml::traits<XmlTraits> )

  static size_type
  get_extent(const array_type_type &type)
  {
    string_type max = type.get_attribute("max");
    
    return max.length();
  }
};

//----------------------------------------------------------------------------
} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_ARRAY_TYPE_HPP
