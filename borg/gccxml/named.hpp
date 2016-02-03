#ifndef BORG_GCCXML_NAMED_HPP
#define BORG_GCCXML_NAMED_HPP

#include <boost/lexical_cast.hpp>
#include <borg/gccxml/traits.hpp>
#include <borg/ast/named.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct named_impl< gccxml::traits<XmlTraits> >
{
  BORG_AST_NAMED_TYPES( typename gccxml::traits<XmlTraits> )

  //----------------------------------------------------------------------------
  static string_type
  get_name(const named_type &n)
  {
    return n.get_attribute("name");
  }
};

//----------------------------------------------------------------------------
}// namespace ast
/*namespace gccxml {
  
typedef ast::typed_t<libxml2_traits> typed_t;
  
} // namespace gccxml*/
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_NAMED_HPP
