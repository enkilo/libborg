#ifndef BORG_ABSTRACT_LIST_HPP
#define BORG_ABSTRACT_LIST_HPP

#include <borg/abstract/types.hpp>
#include <borg/abstract/forward.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/wrap/wrapper.hpp>

namespace borg {

using borg::dereference_cast;
  
//---------------------------------------------------------------------------
template<class Traits, class Derived, class T>
struct list_interface
{
  BORG_ABSTRACT_LIST_TYPES(typename Traits)

  typedef list_impl<Traits, T> impl;

  //-------------------------------------------------------------------
  T 
  search(T item) const
  {
    return impl::search
      (dereference_cast<Derived const>(this), item);
  }

  //-------------------------------------------------------------------
  T 
  reverse_search(T item) const
  {
    return impl::reverse_search
      (dereference_cast<Derived const>(this), item);
  }

  //-------------------------------------------------------------------
  return_type
  insert(T item)
  {
    return impl::insert
      (dereference_cast<Derived const>(this), item);
  }

  //-------------------------------------------------------------------
  return_type
  append(T item)
  {
    return impl::append
      (dereference_cast<Derived const>(this), item);
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived, class T>
struct list_facade
{
  BORG_ABSTRACT_LIST_TYPES(typename Traits)

  typedef list_impl<Traits, T> impl;

  //-----------------------------------------------------------------------

};

//---------------------------------------------------------------------------
template<class Traits, class T>
struct list_t
    : public wrapper<typename Traits::list_type>
    , public list_interface< Traits, list_t<Traits, T>, T >
    , public list_facade< Traits, list_t<Traits, T>, T >
{
  BORG_ABSTRACT_LIST_TYPES(typename Traits)
  
  typedef wrapper<typename Traits::list_type> base_type;
  typedef list_impl<Traits, T> impl;

  //---------------------------------------------------------------------
  list_t(typename Traits::list_type const &list)
    : base_type(list)
  {}
};  
    
//---------------------------------------------------------------------------
template<class Traits, class T>
struct list : list_t<Traits, T>
{
  BORG_ABSTRACT_LIST_TYPES(typename Traits)
  
  typedef list_t<Traits, T> base_type;
  typedef list_impl<Traits, T> impl;
    
  list() : base_type(impl::create())
  {}
  
  
  //---------------------------------------------------------------------
};
  
//---------------------------------------------------------------------------
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ABSTRACT_LIST_HPP
