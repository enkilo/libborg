#ifndef BORG_GCCXML_DECLARATION_HPP
#define BORG_GCCXML_DECLARATION_HPP

#include <boost/lexical_cast.hpp>
#include <borg/gccxml/traits.hpp>
#include <borg/ast/declaration.hpp>
//#include <borg/gccxml/libxml2.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct declaration_impl< gccxml::traits<XmlTraits> >
{
  BORG_AST_DECLARATION_TYPES( typename gccxml::traits<XmlTraits> )

  //----------------------------------------------------------------------------
  static string_type
  get_name(const function_type &fn)
  {

//    std::cerr << "function type: " << fn.name() << std::endl;

    return fn.get_attribute("name");
  }

  //----------------------------------------------------------------------------
  static bool
  is_extern(const declaration_type &fn)
  {
    string_type flag = fn.get_attribute("extern");
    return flag == "1";
  }

  //----------------------------------------------------------------------------
  static attributes_type
  get_attributes(const declaration_type &fn)
  {
    string_type attrs = fn.get_attribute("attributes");

    return attributes_type(attrs.begin(), attrs.end());
  }
  
    
};

//----------------------------------------------------------------------------
}// namespace ast
/*namespace gccxml {
  
typedef ast::declaration_t<libxml2_traits> declaration_t;
  
} // namespace gccxml*/
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_DECLARATION_HPP
