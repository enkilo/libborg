#ifndef BORG_XML_DOM_IMPLEMENTATION_HPP
#define BORG_XML_DOM_IMPLEMENTATION_HPP

#include <borg/xml/dom/document.hpp>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
template<class Traits>
struct implementation_impl
{
  XML_DOM_TYPES(typename Traits)
  
  template<typename ImplementationT>
  static document_type
  create_document(ImplementationT const &impl)
  {
    return impl->createDocument();
  }
  
  template<class ImplementationT>
  static writer_type
  create_dom_writer(const ImplementationT &impl)
  {
    return impl->createDOMWriter();
  }
};
  
//---------------------------------------------------------------------------
//! Implementation interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct implementation_interface : node_interface<Traits, Derived>  
{
  XML_DOM_TYPES(typename Traits)
  typedef typename Traits::template string<char_type>::type string_type;

  typedef implementation_impl<Traits> impl;
    
  document_t<Traits>
  create_document() const
  {
    return impl::create_document(dereference_cast<Derived const>(this));
  }
    
  writer_t<Traits>
  create_dom_writer() const
  {
    return impl::create_dom_writer(dereference_cast<Derived const>(this));
  }
};

//---------------------------------------------------------------------------
//! Implementation facade.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct implementation_facade
{
};

//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_IMPLEMENTATION_HPP
