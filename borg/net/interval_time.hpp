#ifndef BORG_NET_INTERVAL_TIME_HPP
#define BORG_NET_INTERVAL_TIME_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>

#define BORG_NET_INTERVAL_TIME_TYPES(Traits) \
    typedef Traits::interval_type interval_type; \
    typedef Traits::size_type size_type;

//---------------------------------------------------------------------------
namespace borg {
namespace net {

WRAP_PATTERN_FORWARD(interval_time)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct interval_time_interface
{
  BORG_NET_INTERVAL_TIME_TYPES(typename Traits)
  
  typedef interval_time_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct interval_time_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class interval_time_t
    : public wrapper< typename Traits::interval_type >
    , public interval_time_interface< Traits, interval_time_t<Traits> >
    , public interval_time_facade< Traits, interval_time_t<Traits> >
{
public:
  BORG_NET_INTERVAL_TIME_TYPES(typename Traits)
  
  typedef wrapper<interval_type> base_type;

  interval_time_t(interval_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  interval_time_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace net
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NET_INTERVAL_TIME_HPP
