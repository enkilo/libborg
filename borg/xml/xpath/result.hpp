#ifndef BORG_XML_XPATH_RESULT_HPP
#define BORG_XML_XPATH_RESULT_HPP

#include <borg/xml/xpath/forward.hpp>
#include <borg/xml/xpath/types.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace xpath {

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct result_interface
{
  XML_XPATH_TYPES(typename Traits)

  enum 
  type_id
  {
    undefined_result,
    nodeset_result,
    boolean_result,
    number_result,
    string_result
  };
    
  typedef result_impl<Traits> impl;

  type_id
  type()
  {
    return (type_id)impl::type(dereference_cast<Derived const>(this));
  }

  const char *
  typestr()
  {
    switch(type())
    {
      case nodeset_result: return "nodeset";
      case boolean_result: return "boolean";
      case number_result: return "number";
      case string_result: return "string";
      default: return "undefined";
    }
  }
  
  nodeset_t<Traits>
  nodeset() const
  {
    return impl::nodeset(dereference_cast<Derived const>(this));
  }

  number_type
  number() const
  {
    return impl::number(dereference_cast<Derived const>(this));
  }

  string_t<wchar_type, Traits>
  string() const
  {
    return impl::string(dereference_cast<Derived const>(this));
  }

  bool
  boolean() const
  {
    return impl::boolean(dereference_cast<Derived const>(this));
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct result_facade
{
};
  
//---------------------------------------------------------------------------

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_XPATH_RESULT_HPP
