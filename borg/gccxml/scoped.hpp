#ifndef BORG_GCCXML_SCOPED_HPP
#define BORG_GCCXML_SCOPED_HPP

#include <boost/lexical_cast.hpp>
#include <borg/gccxml/traits.hpp>
#include <borg/ast/scoped.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct scoped_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_SCOPED_TYPES( typename traits )

  //----------------------------------------------------------------------------
  static scoped_type
  get_context(const scoped_type &fn)
  {
    string_t<typename XmlTraits::wchar_type, XmlTraits> str = fn.get_attribute("context");
    
    if(!str) //return (typename XmlTraits::element_type)0;
      throw exception< gccxml::traits<XmlTraits> >("gccxml::scoped::get_context(" + std::string(fn.name().begin(), fn.name().end()) + "): not a scoped node");
    
    scoped_type ctx = fn.owner_document().get_element_by_id(str);

    if(!ctx)
      throw exception< gccxml::traits<XmlTraits> >
        ("gccxml::scoped::get_context(" + std::string(fn.name().begin(), fn.name().end()) + 
         "): could not find node with id=" + std::string(str.begin(), str.end()));
    
    return ctx;
  }
};

//----------------------------------------------------------------------------
}// namespace ast
/*namespace gccxml {
  
scopedef ast::scoped_t<libxml2_traits> scoped_t;
  
} // namespace gccxml*/
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_SCOPED_HPP
