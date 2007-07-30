#ifndef BORG_XML_DOM_ELEMENT_HPP
#define BORG_XML_DOM_ELEMENT_HPP

#include <boost/utility/enable_if.hpp>
#include <borg/string.hpp>
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
struct element_interface : public node_interface<Traits, Derived>
{
  XML_DOM_TYPES(typename Traits)

  typedef element_impl<Traits> impl;

  nodemap_t<Traits, attribute_t>
  attributes() const
  {
    return impl::attributes(dereference_cast<const Derived>(this));
  }
  
  //! Set attribute value.
  void
  set_attribute(const string<wchar_type, Traits> &name,
                const string<wchar_type, Traits> &value) const
  {
    return impl::set_attribute(dereference_cast<const Derived>(this), name, value);
  }
  
  string_t<wchar_type, Traits>
  get_attribute(const string<wchar_type, Traits> &name) const
  {
    return impl::get_attribute(dereference_cast<const Derived>(this), name);
  }

  attribute_t<Traits>
  get_attribute_node(const string<wchar_type, Traits> &name) const
  {
    return impl::get_attribute_node(dereference_cast<const Derived>(this), name);
  }

  attribute_t<Traits>
  get_attribute_node_ns
    (const string<wchar_type, Traits> &name, const string<wchar_type, Traits> &ns) const
  {
    return impl::get_attribute_node_ns
      (dereference_cast<const Derived>(this), name, ns);
  }

};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct element_facade
{
  XML_DOM_TYPES(typename Traits);
  
/*  operator bool() const
  {
    return wrapper_core_access::get(dereference_cast<Derived const>(this));
  }*/
  
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
#endif //ndef BORG_XML_DOM_ELEMENT_HPP
