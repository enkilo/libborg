#ifndef BORG_AST_ITERATOR_HPP
#define BORG_AST_ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/ast/node.hpp>

namespace borg {
namespace ast {

#define BORG_AST_ITERATOR_TYPES(Traits, T) \
  typedef T        value_type; \
  BORG_PP_USE_TYPE(Traits, iterator); \
  BORG_PP_USE_TYPE(Traits, const_iterator)
  
//---------------------------------------------------------------------------

//BORG_AST_FORWARD(iterator, (class T)(class Sequence))
/* = node_t<Traits>*/
    
//---------------------------------------------------------------------------
template<class Traits, class T, class Sequence>
struct iterator_impl
{
  BORG_AST_ITERATOR_TYPES(typename Traits, T)

/*  static value_type const &
  dereference(const_iterator const &it)
  {
    return *reinterpret_cast<value_type const *>(&(*it));
  }*/

  static node_t<Traits> &
  dereference(iterator const &it)
  {
    return *(node_t<Traits> *)(&(*it));
  }

  static bool
  equal(iterator const &it1, iterator const &it2) { return (it1 == it2); }

//  static bool
//  equal(const_iterator const &it1, const_iterator const &it2) { return (it1 == it2); }

  static void
  increment(iterator &it) { ++it; }

// static void
//  increment(const_iterator &it) { ++it; }

  static void
  decrement(iterator &it) { --it; }
  
//  static void
//  decrement(const_iterator &it) { --it; }
  
};
    
//---------------------------------------------------------------------------
template<class Traits, class T, class Sequence>
struct iterator_t;
  
//---------------------------------------------------------------------------
template<class Derived, class Traits, class T, class Sequence>
struct iterator_interface
{  
  typedef iterator_impl<Traits, T, Sequence> impl;
  
  BORG_AST_ITERATOR_TYPES(typename impl, T)

  node_t<Traits> &
  dereference() const
  {
    return *(node_t<Traits> *)(&impl::dereference
      (dereference_cast<Derived const>(this)));
  }
  
  void
  increment()
  {
    impl::increment
      (dereference_cast<Derived>(this));
  }
  
  void
  decrement()
  {
    impl::decrement
      (dereference_cast<Derived>(this));
  }
  
  bool
  equal(const iterator_t<Traits, T, Sequence> &it) const
  {
    return impl::equal
      (dereference_cast<Derived const>(this), it);
  }
  
};
  
//---------------------------------------------------------------------------
template<class Derived, class Traits, class T>
struct iterator_facade : public boost::iterator_facade<
//    iterator_interface<Traits, Derived, T>,
    Derived,
    node_t<Traits>,
    boost::bidirectional_traversal_tag
>
{
};

//---------------------------------------------------------------------------
template<class Traits, class T, class Sequence>
class iterator_t
    : public iterator_interface< iterator_t<Traits, T, Sequence>, Traits, T, Sequence >
    , public iterator_facade< iterator_t<Traits, T, Sequence>, Traits, T >
{
public:
  typedef iterator_impl<Traits, T, Sequence> impl;

  BORG_AST_ITERATOR_TYPES(typename impl, T)
    
  typedef wrapper<iterator> base_type;

/*  iterator_t(const iterator &it)
    : m_iterator(it)
  {}*/
  
  iterator_t(const const_iterator &it)
    : m_iterator(it)
  {}
  
  operator iterator &() { return m_iterator; }
  operator iterator const &() const { return m_iterator; }

private:
  iterator m_iterator;
};
  
  
//---------------------------------------------------------------------------
/*template<class Traits>
class iterator
{
};*/
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_ITERATOR_HPP
