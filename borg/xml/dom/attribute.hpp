#ifndef BORG_XML_DOM_ATTRIBUTE_HPP
#define BORG_XML_DOM_ATTRIBUTE_HPP

#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace xml {
namespace dom {

using borg::dereference_cast;

//---------------------------------------------------------------------------
//! Attribute interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct attribute_interface : public node_interface<Traits, Derived>  
{
  XML_DOM_TYPES(typename Traits)
  typedef typename Traits::template string<char_type>::type string_type;

  typedef attribute_impl<Traits> impl;
    
  bool
  is_id() const
  {
    return impl::is_id(dereference_cast<Derived const>(this));
  }
    
  bool
  is_ref() const
  {
    return impl::is_ref(dereference_cast<Derived const>(this));
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct attribute_facade
{
  XML_DOM_TYPES(typename Traits)

  operator node_t<Traits>() const
  {
    return (node_type)(dereference_cast<const Derived>(this));
  }

  operator node_type() const
  {
    return (node_type)(dereference_cast<const Derived>(this));
  }
};
    
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_ATTRIBUTE_HPP
