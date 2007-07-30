#ifndef BORG_GCCXML_FUNCTION_HPP
#define BORG_GCCXML_FUNCTION_HPP

#include <borg/gccxml/declaration.hpp>
#include <borg/ast/function.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct function_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_GCCXML_NODE_TYPES(typename traits)
  BORG_PP_USE_TYPE(typename traits, sequence_type)

  //----------------------------------------------------------------------------
  static typed_type
  get_return_type(const function_type &fn)
  {
    string_t<typename XmlTraits::wchar_type, XmlTraits> str = 
      fn.get_attribute("returns");
    
    if(!str)
      throw exception<traits>("gccxml::function::get_type(): no \"returns\" attribute");
    
    return fn.owner_document().get_element_by_id(str);
  }
  
  //----------------------------------------------------------------------------
  static bool
  is_operator(const function_type &fn)
  {
    return fn.name() == "OperatorFunction";
  }
  
};

//----------------------------------------------------------------------------
}// namespace ast
/*namespace gccxml {
  
typedef ast::function<libxml2_traits> function;
  
}// namespace gccxml*/
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_FUNCTION_HPP
