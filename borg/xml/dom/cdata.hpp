#ifndef BORG_XML_DOM_CDATA_HPP
#define BORG_XML_DOM_CDATA_HPP

#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace dom {
  
//---------------------------------------------------------------------------
//! Attribute interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct cdata_interface 
    : node_interface<Traits, Derived>  
{
  XML_DOM_TYPES(typename Traits)

  typedef cdata_impl<Traits> impl;
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct cdata_facade
{
  XML_DOM_TYPES(typename Traits);
  
/*  operator node_t<Traits>() const
  {
    return node_type(dereference_cast<Derived const>(this));
  }*/
  
/*  operator void *() const
  {
    return (node_type)dereference_cast<Derived const>(this);
  }
  
  operator node_type() const
  {
    return (node_type)dereference_cast<Derived const>(this);
  }*/
};
    
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_CDATA_HPP
