#ifndef BORG_LIBXML2_DOM_ATTRIBUTE_HPP
#define BORG_LIBXML2_DOM_ATTRIBUTE_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/interface.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct attribute_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //-----------------------------------------------------------------------
/*  template<typename AttributeT>
  static string<libxml2::traits>
  value(AttributeT const &attr)
  {
  }*/
    
  //-----------------------------------------------------------------------
  template<typename AttributeT>
  static element_type
  owner_element(AttributeT const &attr)
  {
    return attr->parent;
  }
  
  //-----------------------------------------------------------------------
  static bool
  is_id(attribute_type const attr)
  {
    return xmlIsID(attr->doc, attr->parent, attr);
  }
  
  //-----------------------------------------------------------------------
  static bool
  is_ref(attribute_type const attr)
  {
    return xmlIsRef(attr->doc, attr->parent, attr);
  }
  
  
};

//----------------------------------------------------------------------------
template<class Derived>
struct attribute_facade<libxml2::traits, Derived>
{
  XML_DOM_TYPES(libxml2::traits)

  operator nodemap_type() const
  {
    return (nodemap_type)dereference_cast<Derived const>(this);
  }
};  

//----------------------------------------------------------------------------
template<>
class attribute_t<libxml2::traits>
    : public wrapper<libxml2::traits::attribute_type>
    , public attribute_interface< libxml2::traits, attribute_t<libxml2::traits> >
    , public attribute_facade< libxml2::traits, attribute_t<libxml2::traits> >
{
public:
  XML_DOM_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::attribute_type> base_type;
  
  //! Wrapper constructor.
  attribute_t(attribute_type const &p)
    : base_type(p)
  {}
  
  attribute_t(nodemap_type const &n)
    : base_type((attribute_type)n)
  {}
    
  template<template<class> class Adapter>
  attribute_t(Adapter<libxml2::traits> const &a)
    : base_type((attribute_type)a)
  {}
    
};

  
}// namespace dom
}// namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::attribute_t<traits> attribute_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_ATTRIBUTE_HPP
