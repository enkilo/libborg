#ifndef BORG_LIBXML2_NANOHTTP_HPP
#define BORG_LIBXML2_NANOHTTP_HPP

#include <libxml/nanohttp.h>

#include <borg/libxml2/traits.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/net/http_client.hpp>

namespace borg { 
namespace net {

//----------------------------------------------------------------------------
template<>
struct http_client_impl<libxml2::traits>
{
  BORG_NET_HTTP_CLIENT_TYPES(libxml2::traits)

  static return_type
  read(const http_client_type &ctx, void *dest, length_type len)
  {
    return xmlNanoHTTPRead(ctx, dest, len);
  }
 
  static return_type
  return_code(const http_client_type &ctx)
  {
    return xmlNanoHTTPReturnCode(ctx);
  }
 
  static length_type
  content_length(const http_client_type &ctx)
  {
    return xmlNanoHTTPContentLength(ctx);
  }
};

//----------------------------------------------------------------------------
template<class Derived>
struct http_client_facade<libxml2::traits, Derived>
{
  XML_DOM_TYPES(libxml2::traits)
};
  
//----------------------------------------------------------------------------
template<>
class http_client_t<libxml2::traits>
    : public wrapper<libxml2::traits::http_client_type>
    , public http_client_interface< libxml2::traits, http_client_t<libxml2::traits> >
    , public http_client_facade< libxml2::traits, http_client_t<libxml2::traits> >
{
public:
  BORG_NET_HTTP_CLIENT_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::http_client_type> base_type;
  
  //! Wrapper constructor.
  http_client_t(http_client_type const &p) 
    : base_type(p)
  {}

  http_client_t(node_type const &n)
    : base_type((http_client_type)n)
  {}

  template<template<class> class Adapter>
  http_client_t(Adapter<libxml2::traits> const &a)
    : base_type((http_client_type)a)
  {}
  
};
  
//----------------------------------------------------------------------------
template<>
class http_client<libxml2::traits>
    : public http_client_interface< libxml2::traits, http_client<libxml2::traits> >
    , public http_client_facade< libxml2::traits, http_client<libxml2::traits> >
{
public:
  BORG_NET_HTTP_CLIENT_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::http_client_type> base_type;
  typedef http_client<libxml2::traits> this_type;
  
  //! Wrapper constructor.
  http_client(const char *url)
    : m_handle(xmlNanoHTTPOpen(url, &m_content_type))
  {}

  ~http_client()
  {
    xmlNanoHTTPClose(m_handle);
  }
  
  operator libxml2::traits::http_client_type() const
  {
    return m_handle;
  }
  
  char *
  content_type() const
  {
    return m_content_type;
  }
  
private:
  void *m_handle;
  char *m_content_type;
  
  this_type &
  operator=(const this_type &);

  http_client(const this_type &);
};
  
}// namespace net

//---------------------------------------------------------------------------
namespace libxml2 {

typedef net::http_client_t<traits> http_client_t;
typedef net::http_client<traits> http_client;

} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_NANOHTTP_HPP
