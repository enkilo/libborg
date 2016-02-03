#ifndef BORG_NET_HTTP_CLIENT_HPP
#define BORG_NET_HTTP_CLIENT_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/net/address.hpp>
#include <borg/net/interval_time.hpp>

#define BORG_NET_HTTP_CLIENT_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, http_client_type) \
    BORG_PP_USE_TYPE(Traits, return_type) \
    BORG_PP_USE_TYPE(Traits, length_type) \
    BORG_PP_USE_TYPE(Traits, url_type)

//---------------------------------------------------------------------------
namespace borg {
namespace net {

WRAP_PATTERN_FORWARD(http_client)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct http_client_interface
{
  BORG_NET_HTTP_CLIENT_TYPES(typename Traits)
  
  typedef http_client_impl<Traits> impl;
  
  return_type
  read(void *dest, length_type len)
  {
    return impl::read(dereference_cast<Derived>(this), dest, len);
  }
  
  return_type
  return_code() const
  {
    return impl::return_code(dereference_cast<Derived const>(this));
  }
  
  length_type
  content_length() const
  {
    return impl::content_length(dereference_cast<Derived const>(this));
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct http_client_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class http_client_t
    : public wrapper< typename Traits::http_client_type >
    , public http_client_interface< Traits, http_client_t<Traits> >
    , public http_client_facade< Traits, http_client_t<Traits> >
{
public:
  typedef typename Traits::http_client_type http_client_type;
  typedef wrapper<http_client_type> base_type;

  http_client_t(http_client_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  http_client_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace net
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NET_HTTP_CLIENT_HPP
