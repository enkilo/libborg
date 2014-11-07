#ifndef BORG_LIBXML2_DOM_NODEMAP_HPP
#define BORG_LIBXML2_DOM_NODEMAP_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/libxml2/string.hpp>
#include <borg/libxml2/dom/attribute.hpp>
#include <borg/xml/dom/nodemap.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/unwrap_cast.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//----------------------------------------------------------------------------
template<>
struct nodemap_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //! Return the number of items in the node list.
  //-----------------------------------------------------------------------
  static length_type
  size(nodemap_type nm)
  {
    attribute_type link = (attribute_type)nm;
    length_type n = 0;
    
    for(; link; link = link->next)
      ++n;

    return n; 
  }

  //-----------------------------------------------------------------------
  template<typename NodeMapT>
  static nodemap_type
  item(NodeMapT const &nodemap, length_type i)
  {
    NodeMapT list = nodemap;

    for(length_type n = 0; list; list = list->next, ++n)
    {
      if(n == i)
        return list;
    }
    
    return nodemap_type();
  }

  //-----------------------------------------------------------------------
  static attribute_type
  get_named_item(nodemap_type nm, const wchar_type *name)
  {
    return xmlHasProp(attribute_type(nm)->parent, name);
  }
  
  
};

//----------------------------------------------------------------------------
/*template<class Derived, template<class> class Node>
struct nodemap_interface<libxml2::traits, Derived, Node>
{
  XML_DOM_TYPES(libxml2::traits)

  typedef nodemap_impl<libxml2::traits> impl;

  Node<libxml2::traits>
  item(size_t i) const
  {
    return (Node<libxml2::traits>)impl::item
      (dereference_cast<Derived const>(this), i);
  }

  size_t
  size() const
  {
    return impl::size
      (dereference_cast<Derived const>(this));
  }
  
};*/
    
    
//----------------------------------------------------------------------------
template<class Derived, template<class> class Node>
struct nodemap_facade<libxml2::traits, Derived, Node>
{
  class iterator : public boost::iterator_facade<
    typename nodemap_facade<libxml2::traits, Derived, Node>::iterator,
    Node<libxml2::traits> const,
    boost::bidirectional_traversal_tag
    >
  {
  public:
    XML_DOM_TYPES(libxml2::traits)
    typedef typename nodemap_facade<libxml2::traits, Derived, Node>::iterator iterator_type;

    iterator(const nodemap_t<libxml2::traits> &m,
             const nodemap_type &n)
      : m_map(m)
      , m_node(n)
    {}    
    
  protected:
    //! \name Iterator core interface.
    //@{
  
    friend class boost::iterator_core_access;

    //! Dereference the iterator (Return reference to pointee).
    Node<libxml2::traits> const &
    dereference() const
    { return m_node; }

    //! Advance to next position.
    void
    increment()
    { if(m_node) m_node = m_node->next; }

    //! Return to previous position.
    void
    decrement()
    { if(m_node) m_node = m_node->prev; }

    //! Compare iterators.
    bool
    equal(iterator_type const &it) const 
    { 
      return (borg::unwrap_cast(it.m_map) == borg::unwrap_cast(m_map)) &&
             (borg::unwrap_cast(it.m_node) == borg::unwrap_cast(m_node));
    }

    //@}
    
    nodemap_t<libxml2::traits, Node> const &m_map;
    Node<libxml2::traits> m_node;
  };

  typedef iterator const_iterator;
  
  iterator
  begin() const
  {
    return iterator(dereference_cast<Derived const>(this), dereference_cast<Derived const>(this));
  }

  iterator
  end() const
  {
    return iterator(dereference_cast<Derived const>(this), 0);
  }
};
  
//----------------------------------------------------------------------------
template<>
class nodemap_t<libxml2::traits>
    : public wrapper<libxml2::traits::nodemap_type>
    , public nodemap_interface< libxml2::traits, nodemap_t<libxml2::traits> >
    , public nodemap_facade< libxml2::traits, nodemap_t<libxml2::traits> >
{
public:
  XML_DOM_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::nodemap_type> base_type;
  
  //! Wrapper constructor.
  nodemap_t(nodemap_type const &p) 
    : base_type(p)
  {}

  nodemap_t(node_type const &n)
    : base_type((nodemap_type)n)
  {}

  template<template<class> class Adapter>
  nodemap_t(Adapter<libxml2::traits> const &a)
    : base_type((nodemap_type)a)
  {}
  
/*  attribute_t<libxml2::traits>
  operator[](const char *name) const
  {
    return get_named_item((unsigned char *)name);
  }
*/
  attribute_t<libxml2::traits>
  operator[](const string<libxml2::traits::wchar_type, libxml2::traits> &str) const
  {
    return get_named_item(str);
  }
  
};
  
} // namespace dom
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::nodemap_t<traits, xml::dom::attribute_t> nodemap_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_NODEMAP_HPP
