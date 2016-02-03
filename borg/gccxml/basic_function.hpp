#ifndef BORG_GCCXML_BASIC_FUNCTION_HPP
#define BORG_GCCXML_BASIC_FUNCTION_HPP

#include <borg/gccxml/declaration.hpp>
#include <borg/ast/basic_function.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

template<class XmlTraits>
struct basic_function_impl< gccxml::traits<XmlTraits> >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_GCCXML_NODE_TYPES(typename traits)
  BORG_PP_USE_TYPE(typename traits, sequence_type)

  //----------------------------------------------------------------------------
  static typed_type
  get_type(const function_type &fn)
  {
    // <Function> nodes have no representation of their types.
    // We could however emulate one by proxying as the return type and the
    // argument types are known.
  }
  
  //----------------------------------------------------------------------------
  static bool
  is_operator(const function_type &fn)
  {
    return fn.name() == "OperatorFunction"
        || fn.name() == "OperatorMethod"
        || fn.name() == "Converter";
  }
  
  //----------------------------------------------------------------------------
  static bool
  is_method(const function_type &fn)
  {
    return fn.name() == "Method"
        || fn.name() == "OperatorMethod"
        || fn.name() == "Converter";
  }
  
  //----------------------------------------------------------------------------
  static bool
  is_constructor(const function_type &fn)
  {
    return fn.name() == "Constructor";
  }
  
  //----------------------------------------------------------------------------
  static bool
  is_destructor(const function_type &fn)
  {
    return fn.name() == "Destructor";
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
