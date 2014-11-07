#ifndef BORG_AST_SEQUENCE_HPP
#define BORG_AST_SEQUENCE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/ast/iterator.hpp>
#include <borg/ast/branch.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_SEQUENCE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, sequence_type) \
  BORG_AST_ITERATOR_TYPES(Traits, typename sequence_type::value_type)

//---------------------------------------------------------------------------
template<class Iterator, class Sequence, class Traits>
struct sequence_impl;

//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits>
struct sequence_t;

//---------------------------------------------------------------------------
template<class Children, class Parent, class Traits>
struct branch_t;

//---------------------------------------------------------------------------
template<class Traits, class Node>
struct sequence_iterator
{
 
  
};

//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits, class Derived>
struct sequence_interface
{  
  typedef Traits   traits;
  typedef T        value_type;
  typedef Sequence sequence_type;

  typedef sequence_impl<value_type, sequence_type, traits> impl;

  typedef iterator_t< traits, value_type, sequence_type > iterator;
  typedef iterator_t< traits, value_type const, sequence_type > const_iterator;
  
  iterator
  begin() 
  { return impl::begin
      (dereference_cast<Derived>(this)); }

  iterator
  end() 
  { return impl::end
      (dereference_cast<Derived>(this)); }

  const_iterator
  begin() const 
  { return impl::begin
      (dereference_cast<Derived const>(this)); }

  const_iterator
  end() const 
  { return impl::end
      (dereference_cast<Derived const>(this)); }
};
  
//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits, class Derived>
struct sequence_facade
{
  
  
};
  
//---------------------------------------------------------------------------
//! Sequence (list) of children, but actually holds the parent node.
//! Usually instantiated as public 'children' member of a node class.
//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits, class Parent, class Impl>
struct sequence_proxy
    : public sequence_interface
      <
          T
        , Sequence
        , Traits
        , sequence_proxy<T, Sequence, Traits, Parent, Impl>
      >
{
  BORG_AST_ITERATOR_TYPES(typename Traits, T)

//protected:
  friend class node_t<Traits>;
  
  sequence_proxy(const Parent &parent)
      : m_parent(parent)
  {}

  Sequence
  get() const { return Impl::get_children(m_parent); }

  Parent const &
  get_parent() const { return m_parent; }    

  Parent &
  get_parent() { return m_parent; }
  
  operator Sequence() const { return get(); }
  
private:
  Parent m_parent;
};
    
//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits>
class sequence_t
    : public wrapper<typename Traits::sequence_type>
    , public sequence_interface< T, Sequence, Traits, sequence_t<T, Sequence, Traits> >
    , public sequence_facade< T, Sequence, Traits, sequence_t<T, Sequence, Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, sequence_type)
    
  typedef wrapper<typename Traits::sequence_type> base_type;
    
  sequence_t(const sequence_type &fn) 
    : base_type(fn)
  {}
};
  
  
//---------------------------------------------------------------------------
/*template<class Traits>
class sequence
{
};*/
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_SEQUENCE_HPP
