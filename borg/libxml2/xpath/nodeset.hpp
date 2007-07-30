#ifndef BORG_LIBXML2_XPATH_NODESET_HPP
#define BORG_LIBXML2_XPATH_NODESET_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/libxml2/dom/attribute.hpp>
#include <borg/xml/xpath/nodeset.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/unwrap_cast.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
struct nodeset_impl<libxml2::traits>
{
  XML_XPATH_TYPES(libxml2::traits)

  //! Return the number of items in the node set.
  //-----------------------------------------------------------------------
  static length_type
  size(nodeset_type const ns)
  {
    return xmlXPathNodeSetGetLength(ns);
  }

  //! Returns a node by index (NULL if index is invalid).
  //-----------------------------------------------------------------------
  static node_type
  item(nodeset_type const ns, index_type index)
  {
    return xmlXPathNodeSetItem(ns, index);
  }

  //! Returns a reference to a node by index.
  //-----------------------------------------------------------------------
  static node_type &
  item_ref(nodeset_type const ns, length_type index)
  {
    return ns->nodeTab[index];
  }

  //! Checks whether the nodeset is empty.
  //-----------------------------------------------------------------------
  static bool
  empty(nodeset_type const ns)
  {
    return xmlXPathNodeSetIsEmpty(ns);
  }
  
};

//----------------------------------------------------------------------------
template<class Derived>
struct nodeset_facade<libxml2::traits, Derived>
{
  typedef node_t<libxml2::traits> *iterator;
  typedef const node_t<libxml2::traits> *const_iterator;
  
  typedef nodeset_impl<libxml2::traits> impl;
  
  iterator
  begin() 
  { 
    return reinterpret_cast<iterator>
      (&impl::item_ref
        (borg::dereference_cast<Derived>(this), 0));
  }

  const_iterator
  begin() const 
  {
    return reinterpret_cast<const_iterator>
      (&impl::item_ref
        (borg::dereference_cast<Derived const>(this), 0));
  }

  iterator
  end()
  {
    return reinterpret_cast<iterator>
      (&impl::item_ref
        (borg::dereference_cast<Derived>(this),
          impl::size(borg::dereference_cast<Derived>(this))));
  }

  const_iterator
  end() const
  {
    return reinterpret_cast<const_iterator>
      (&impl::item_ref(borg::dereference_cast<Derived const>(this),
                           impl::size(borg::dereference_cast<Derived const>(this))));
  }
    
};
  
//----------------------------------------------------------------------------
template<>
class nodeset_t<libxml2::traits>
    : public wrapper<libxml2::traits::nodeset_type>
    , public nodeset_interface< libxml2::traits, nodeset_t<libxml2::traits> >
    , public nodeset_facade< libxml2::traits, nodeset_t<libxml2::traits> >
{
public:
  XML_XPATH_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::nodeset_type> base_type;
  
  //! Wrapper constructor.
  nodeset_t(nodeset_type const &p) 
    : base_type(p)
  {}

/*  nodeset_t(node_type const &n)
    : base_type((nodeset_type)n)
  {}

  template<template<class> class Adapter>
  nodeset_t(Adapter<libxml2::traits> const &a)
    : base_type((nodeset_type)a)
  {}*/
  
};
  
} // namespace xpath
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace xpath {

typedef xml::xpath::nodeset_t<traits> nodeset_t;

} // namespace xpath
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_NODESET_HPP
