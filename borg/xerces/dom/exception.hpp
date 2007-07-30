#ifndef BORG_XERCES_DOM_EXCEPTION_HPP
#define BORG_XERCES_DOM_EXCEPTION_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/interface.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct exception_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)
  typedef xerces::traits::string<char_type>::type string_type;

  template<typename ExceptionT>
  static string_type
  message(ExceptionT const &e)
  {
    return e->getMessage();
  }        
};

//----------------------------------------------------------------------------
/*template<>
class exception_t<xerces::traits>
    : public wrapper<xerces::traits::exception_type>
    , public exception_interface< xerces::traits, exception_t<xerces::traits> >
{
public:
  XML_DOM_TYPES(xerces::traits)
//  typedef xerces::traits::string<wchar_type>::type wstring_type;

  typedef wrapper<xerces::traits::exception_type> base_type;
  
  //! Wrapper constructor.
  exception_t(exception_type const &p) 
    : base_type(p)
  {}
  
  //! Default constructor.
  exception_t()
    : base_type(new XERCES_CPP_NAMESPACE::DOMException)
  {}

  //! Custom constructor.
  exception_t(id_type code, const wchar_type *msg)
    : base_type(new XERCES_CPP_NAMESPACE::DOMException(code, msg))
  {}
};*/

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_EXCEPTION_HPP
