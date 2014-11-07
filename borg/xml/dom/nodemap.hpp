#ifndef BORG_XML_DOM_NODEMAP_HPP
#define BORG_XML_DOM_NODEMAP_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/unwrap_cast.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/nodelist.hpp>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
//! Node list interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived, template<class> class Node>
struct nodemap_interface 
{
  XML_DOM_TYPES(typename Traits)

  typedef nodemap_impl<Traits> impl;

  length_type
  size() const
  {
    return impl::size
      (dereference_cast<Derived const>(this));
  }
  
  Node<Traits>
  item(length_type index) const
  {
    return (Node<Traits>)impl::item
      (dereference_cast<Derived const>(this), index);
  }
  
  Node<Traits>
  get_named_item(const string<wchar_type, Traits> &name) const
  {
    return (Node<Traits>)impl::get_named_item
      (dereference_cast<Derived const>(this), name);
  }

/*  Node<Traits>
  operator[](length_type index) const
  {
    return item(index);
  }*/

  Node<Traits>
  operator[](const string<wchar_type, Traits> &name) const
  {
    return get_named_item(name);
  }
};  
  
//---------------------------------------------------------------------------
template<class Traits, class Derived, template<class> class Node>
struct nodemap_facade
{
  XML_DOM_TYPES(typename Traits)

  typedef nodemap_impl<Traits> impl;

  class iterator : public boost::iterator_facade
    <
    typename nodemap_facade<Traits, Derived, Node>::iterator,
    Node<Traits> const,
    boost::random_access_traversal_tag
    >
  {
    public:
    XML_DOM_TYPES(typename Traits)
    typedef typename nodemap_facade<Traits, Derived, Node>::iterator iterator_type;

    template<class U>
    iterator(const U &map, length_type pos = 0)
      : m_map(map)
      , m_node(attribute_type())
      , m_pos(pos)
    {
      if(m_pos < m_map.size())
        m_node = m_map.item(m_pos);
    }

  protected:
    //! \name Iterator core interface.
    //@{

    friend class boost::iterator_core_access;

    //! Dereference the iterator (Return reference to pointee).
    Node<Traits> const &
    dereference() const
    { return m_node; }

    //! Advance to next position.
    void
    increment()
    { m_node = m_map.item(++m_pos); }

    //! Return to previous position.
    void
    decrement()
    { m_node = m_map.item(--m_pos); }

    //! Advance n positions.
    void
    advance(length_type n)
    { m_node = m_map.item((m_pos += n)); }
      
    //! Compare iterators.
    bool
    equal(iterator_type const &it) const
    {
      return (borg::unwrap_cast(it.m_map) == borg::unwrap_cast(m_map)) &&
             (it.m_pos == m_pos);
    }

    //! Compare distance to other iterator.
    int
    distance_to(iterator_type const &it) const
    {
      return it.m_pos - m_pos;
    }

    //@}

    nodemap_t<Traits, Node> const &m_map;
    Node<Traits> m_node;
    length_type m_pos;
  };  
  
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

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_NODEMAP_HPP
