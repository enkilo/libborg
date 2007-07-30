#ifndef BORG_XERCES_DOM_IMPLEMENTATION_HPP
#define BORG_XERCES_DOM_IMPLEMENTATION_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

/*//---------------------------------------------------------------------------
template<>
struct implementation_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)

  template<typename ImplementationT>
  static document_type
  create_document(ImplementationT const &impl)
  {
    return impl->createDocument();
  }      
};*/
  
//----------------------------------------------------------------------------
template<>
class implementation<xerces::traits>
    : /*protected*/public wrapper<xerces::traits::implementation_type>
    , public implementation_interface< xerces::traits, implementation_t<xerces::traits> >
{
  friend class borg::wrapper_core_access;
  
public:
  XML_DOM_TYPES(xerces::traits)

  typedef wrapper<xerces::traits::implementation_type> base_type;

  //! Default constructor.
  implementation()
    : base_type(::XERCES_CPP_NAMESPACE::DOMImplementationRegistry::getDOMImplementation((const XMLCh *)"L\0S\0\0"))
    , m_delete(true)
  {}

  ~implementation()
  {
    if(m_delete)
      delete borg::unwrap_cast(*this);
  }
  
private:
  bool m_delete;
};

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_IMPLEMENTATION_HPP
