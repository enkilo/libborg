#ifndef BORG_GCCXML_NAMESPACE_HPP
#define BORG_GCCXML_NAMESPACE_HPP

#include <borg/gccxml/declaration.hpp>
#include <borg/ast/namespace.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct namespace_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_NAMESPACE_TYPES(typename traits)

  static bool
  is_root(const namespace_type &ns)
  {
    string_t<typename XmlTraits::wchar_type, XmlTraits> str = ns.get_attribute("name");
    
    if(str && str == "::")
      return true;
    
    return !ns.get_attribute_node("context");
  }  
    
};

//----------------------------------------------------------------------------
}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_NAMESPACE_HPP
