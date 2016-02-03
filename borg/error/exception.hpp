#ifndef BORG_ERROR_EXCEPTION_HPP
#define BORG_ERROR_EXCEPTION_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>

#define BORG_ERROR_EXCEPTION_TYPES(Traits) \
    typedef Traits::status_type status_type; \
    typedef Traits::size_type size_type;

//---------------------------------------------------------------------------
namespace borg {

WRAP_PATTERN_FORWARD(exception)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct exception_i 
{
  BORG_ERROR_EXCEPTION_TYPES(typename Traits)
  
  typedef exception_impl<Traits> impl;
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct exception_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class exception_t
    : public wrapper< typename Traits::exception_type >
    , public exception_interface< Traits, exception_t<Traits> >
    , public exception_facade< Traits, exception_t<Traits> >
{
public:
  typedef typename Traits::exception_type exception_type;
  typedef wrapper<exception_type> base_type;

  exception_t(exception_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  exception_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ERROR_EXCEPTION_HPP
