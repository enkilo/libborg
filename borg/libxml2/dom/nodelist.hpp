#ifndef BORG_LIBXML2_DOM_NODELIST_HPP
#define BORG_LIBXML2_DOM_NODELIST_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/adapters.hpp>
#include <borg/xml/dom/nodelist.hpp>
#include <borg/wrap/unwrap_cast.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//----------------------------------------------------------------------------
template<>
struct nodelist_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //! Return the number of items in the node list.
  //-----------------------------------------------------------------------
  static length_type
  size(nodelist_type const nodelist)
  {
    length_type n = 0;
    
    for(node_type node = nodelist; node; node = node->next)
      ++n;

    return n; 
  }

};

//---------------------------------------------------------------------------
template<class NodeT>
class nodelist_iterator<libxml2::traits, NodeT>
    : public boost::iterator_facade<
        nodelist_iterator<libxml2::traits, NodeT>,
        NodeT const,
        boost::bidirectional_traversal_tag
    >
{
public:
  XML_DOM_TYPES(libxml2::traits)
  typedef nodelist_iterator<libxml2::traits, NodeT> iterator_type;

  nodelist_iterator(const nodelist_t<libxml2::traits> &m,
                    const nodelist_type &n)
    : m_list(m)
    , m_node(n)
  {}
    
    
protected:
  //! \name Iterator core interface.
  //@{
  
  friend class boost::iterator_core_access;
  
  //! Dereference the iterator (Return reference to pointee).
  const NodeT &
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
    return (unwrap_cast(it.m_list) == unwrap_cast(m_list)) &&
           (unwrap_cast(it.m_node) == unwrap_cast(m_node));
  }

  //@}
    
  nodelist_t<libxml2::traits, NodeT> const &m_list;
  NodeT m_node;
};

//---------------------------------------------------------------------------
template<class Derived, class NodeT>
struct nodelist_facade<libxml2::traits, Derived, NodeT>
  {
  typedef nodelist_iterator< libxml2::traits, NodeT > iterator;
  typedef nodelist_iterator< libxml2::traits, NodeT /*const*/ > const_iterator;

  const_iterator
  begin() const
  {
    return const_iterator(dereference_cast<Derived const>(this), dereference_cast<Derived const>(this));
  }

  const_iterator
  end() const
  {
    return const_iterator(dereference_cast<Derived const>(this), 0);
  }    
};
  
//----------------------------------------------------------------------------
/*template<>
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
  
};*/
  
//----------------------------------------------------------------------------
/*template<>
class nodelist_t<libxml2::traits>
    : public wrapper<libxml2::traits::nodelist_type>
    , public nodelist_interface< libxml2::traits, nodelist_t<libxml2::traits> >
{
public:
  XML_DOM_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::nodelist_type> base_type;
  
  //! Wrapper constructor.
  nodelist_t(nodelist_type const &p) 
    : base_type(p)
  {}

};*/
  
}// namespace dom
}// namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::nodelist_t<traits> nodelist_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_NODELIST_HPP


