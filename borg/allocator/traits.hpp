#ifndef BORG_ALLOCATOR_TRAITS_HPP
#define BORG_ALLOCATOR_TRAITS_HPP

#include <borg/allocator/fwd.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Tags to specify allocator implementation capabilities.
//---------------------------------------------------------------------------
struct singleton_allocator_tag {}; //!< Implementation has a shared allocator.
struct reentrant_allocator_tag {}; //!< Implementation has a reentrant allocator.  
struct hinting_allocator_tag {};   //!< Implementation supports hinting.
struct size_tracking_tag {};       //!< Implementation tracks size itself.
  
//! Implementation supports reallocation. This is an extended form of hinting, 
//! where the memory on the old location is copied to the new location when
//! reallocation yields another memory address.
struct reallocation_tag : hinting_allocator_tag {};

//---------------------------------------------------------------------------
template<class Allocator>
struct allocator_traits;

//---------------------------------------------------------------------------
//! Traits specialisation for std::allocator, which is a singleton (locking
//! should be up to libstdc++ respectively the underlying libc) and supports
//! none of our special features.
//---------------------------------------------------------------------------
template<class T>
struct allocator_traits< std::allocator<T> >
{
  BOOST_STATIC_CONSTANT(bool, is_singleton = true);
  BOOST_STATIC_CONSTANT(bool, is_reentrant = false);
  BOOST_STATIC_CONSTANT(bool, supports_hinting = false);
  BOOST_STATIC_CONSTANT(bool, supports_realloc = false);
};

//---------------------------------------------------------------------------
//! Traits specialisation for allocator implementation.
//---------------------------------------------------------------------------
template<class T, class Traits>
struct allocator_traits< allocator_impl<T, Traits> >
{
  typedef allocator_impl<T, Traits> impl;

  //-------------------------------------------------------------------
  //! Determine whether a tag is set in that specific implementation.
  //-------------------------------------------------------------------
  template<class Tag>
  struct has_tag
  {
    BOOST_STATIC_CONSTANT(bool, value = 
       (boost::is_convertible< typename impl::category, Tag >::value)
    );
  };

  //-------------------------------------------------------------------
  //! \name Allocator capabilities.
  //-------------------------------------------------------------------
  //@{
  BOOST_STATIC_CONSTANT(bool, is_singleton = has_tag< singleton_allocator_tag >::value);
  BOOST_STATIC_CONSTANT(bool, is_reentrant = has_tag< reentrant_allocator_tag >::value);
  BOOST_STATIC_CONSTANT(bool, supports_hinting = has_tag< hinting_allocator_tag >::value);
  BOOST_STATIC_CONSTANT(bool, supports_realloc = has_tag< reallocation_tag >::value);
  //@}
};

//---------------------------------------------------------------------------
//! Traits specialisation for allocator interface.
//---------------------------------------------------------------------------
template<class Derived, class T, class Traits>
struct allocator_traits< allocator_interface<Derived, T, Traits> >
     : allocator_traits< typename allocator_interface<Derived, T, Traits>::impl >
{
};
  
//---------------------------------------------------------------------------
template<template<class, class> class Tmpl, class T, class Traits>
struct allocator_traits< Tmpl<T, Traits> >
     : allocator_traits< typename Tmpl<T, Traits>::impl >
{
};
  
//---------------------------------------------------------------------------
template<template<class> class Tmpl, class T>
struct allocator_traits< Tmpl<T> >
     : allocator_traits< typename Tmpl<T>::impl >
{
};
  
//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_TRAITS_HPP
