#ifndef BORG_XERCES_HTTP_INPUT_STREAM_HPP
#define BORG_XERCES_HTTP_INPUT_STREAM_HPP

#include <xercesc/util/XMLURL.hpp>
#ifdef WIN32
#include <xercesc/util/NetAccessors/WinSock/BinHTTPURLInputStream.hpp>
#else
#include <xercesc/util/NetAccessors/Socket/UnixHTTPURLInputStream.hpp>
#endif

#include <boost/type_traits/remove_pointer.hpp>
#include <borg/xerces/traits.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/net/http_client.hpp>

namespace borg { 
namespace net {

//----------------------------------------------------------------------------
template<>
struct http_client_impl<xerces::traits>
{
  BORG_NET_HTTP_CLIENT_TYPES(xerces::traits)

  // TODO: abstract input stream methods
    
  static return_type
  read(const http_client_type &ctx, void *dest, length_type len)
  {
    return ctx->readBytes((XMLByte *)dest, len);
  }

};

//----------------------------------------------------------------------------
template<class Derived>
struct http_client_facade<xerces::traits, Derived>
{
  XML_DOM_TYPES(xerces::traits)
};
  
//----------------------------------------------------------------------------
template<>
class http_client_t<xerces::traits>
    : public wrapper<xerces::traits::http_client_type>
    , public http_client_interface< xerces::traits, http_client_t<xerces::traits> >
    , public http_client_facade< xerces::traits, http_client_t<xerces::traits> >
{
public:
  BORG_NET_HTTP_CLIENT_TYPES(xerces::traits)

  typedef wrapper<xerces::traits::http_client_type> base_type;
  
  //! Wrapper constructor.
  http_client_t(http_client_type const &p) 
    : base_type(p)
  {}

  http_client_t(node_type const &n)
    : base_type((http_client_type)n)
  {}

  template<template<class> class Adapter>
  http_client_t(Adapter<xerces::traits> const &a)
    : base_type((http_client_type)a)
  {}
  
};
  
//----------------------------------------------------------------------------
template<>
class http_client<xerces::traits>
    : public http_client_interface< xerces::traits, http_client<xerces::traits> >
    , public http_client_facade< xerces::traits, http_client<xerces::traits> >
{
public:
  BORG_NET_HTTP_CLIENT_TYPES(xerces::traits)

  typedef wrapper<xerces::traits::http_client_type> base_type;
  typedef http_client<xerces::traits> this_type;
  
  //! Wrapper constructor.
  http_client(const url_type &url)
    : m_stream(url)
  {}

  ~http_client()
  {
  }
  
  operator http_client_type()
  {
    return &m_stream;
  }

  http_client_type
  operator->()
  {
    return &m_stream;
  }
  
private:
#ifdef WIN32
  ::XERCES_CPP_NAMESPACE::BinHTTPURLInputStream m_stream;
#else
  ::XERCES_CPP_NAMESPACE::UnixHTTPURLInputStream m_stream;
#endif
  
  this_type &
  operator=(const this_type &);

  http_client(const this_type &);
};
  
}// namespace net

//---------------------------------------------------------------------------
namespace xerces {

typedef net::http_client_t<traits> http_input_stream_t;
typedef net::http_client<traits> http_input_stream;

} // namespace xerces
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_HTTP_INPUT_STREAM_HPP
