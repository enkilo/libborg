#ifndef BORG_XML_DOM_NODELIST_HPP
#define BORG_XML_DOM_NODELIST_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/preproc.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg {
namespace xml {
namespace dom {

WRAP_PATTERN_FORWARD(nodelist, (class NodeT = node_t<Traits>))
  
template<class Traits, class Derived, class NodeT>
struct nodelist_facade;
    
//---------------------------------------------------------------------------
//! Node list interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived, class NodeT>
struct nodelist_interface
{
  XML_DOM_TYPES(typename Traits)

  typedef nodelist_impl<Traits> impl;
  
  NodeT
  item(length_type i) const
  {
    return impl::item(dereference_cast<Derived const>(this), i);
  }

  length_type
  size() const
  {
    return impl::size
      (dereference_cast<Derived const>(this));
  }
};  
  
//---------------------------------------------------------------------------
template<class Traits, class NodeT>
class nodelist_iterator 
    : public boost::iterator_facade
      <
          nodelist_iterator<Traits, NodeT>
        , NodeT
        , boost::forward_traversal_tag
      >
{
public:
  XML_DOM_TYPES(typename Traits)
  typedef nodelist_iterator<Traits, NodeT> iterator_type;

  template<class U>
  nodelist_iterator(const U &list, length_type pos = 0)
    : m_list(list)
    , m_node(list.item(pos))
    , m_pos(pos)
  {}

protected:
  friend class nodelist<Traits>;

  //! \name Iterator core interface.
  //@{

  friend class boost::iterator_core_access;

  //! Dereference the iterator (Return reference to pointee).
  NodeT const &
  dereference() const
  { return m_node; }

//! Advance to next position.
  void
  increment()
  { m_node = m_list.item(++m_pos); }

  //! Return to previous position.
  void
  decrement()
  { m_node = m_list.item(--m_pos); }

  //! Advance n positions.
  void
  advance(length_type n)
  { m_node = m_list.item((m_pos += n)); }

  //! Compare iterators.
  bool
  equal(iterator_type const &it) const
  {
    return (&it.m_list == &m_list) &&
           (it.m_pos == m_pos);
  }

  //! Compare distance to other iterator.
  int
  distance_to(iterator_type const &it)
  {
    return it.position() - m_pos;
  }

  //@}

  nodelist_t<Traits> const &m_list;
  NodeT m_node;
  length_type m_pos;
};

//---------------------------------------------------------------------------
template<class Traits, class Derived, class NodeT>
struct nodelist_facade
{
  XML_DOM_TYPES(typename Traits)

  typedef nodelist_impl<Traits> impl;
  
  typedef nodelist_iterator<Traits, NodeT> iterator;
  typedef nodelist_iterator<Traits, NodeT const> const_iterator;
  
  iterator
  begin() const
  {
    return iterator(dereference_cast<Derived const>(this), 0);
  }
  
  iterator
  end() const
  {
    return iterator(dereference_cast<Derived const>(this), 
                    impl::size(dereference_cast<Derived const>(this)));
  }  
};
  
//---------------------------------------------------------------------------
template<class Traits, class NodeT>
struct nodelist_t
    : public wrapper<typename Traits::nodelist_type>
    , public nodelist_interface<Traits, nodelist_t<Traits, NodeT>, NodeT>
    , public nodelist_facade<Traits, nodelist_t<Traits, NodeT>, NodeT>
{
  XML_DOM_TYPES(typename Traits)

  typedef wrapper<nodelist_type> base;
  typedef nodelist_impl<Traits> impl;
  
  nodelist_t(const nodelist_type &nodelist) 
    : base(nodelist)
  {}
  
  template<class T>
  nodelist_t(const nodelist_t<Traits, T> &nodelist)
    : base(nodelist)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_NODELIST_HPP
