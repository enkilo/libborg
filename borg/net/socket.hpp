#ifndef BORG_NET_SOCKET_HPP
#define BORG_NET_SOCKET_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/net/address.hpp>
#include <borg/net/interval_time.hpp>

#define BORG_NET_SOCKET_TYPES(Traits) \
    typedef Traits::af_type af_type; \
    typedef Traits::socket_type socket_type; \
    typedef Traits::status_type status_type; \
    typedef Traits::size_type size_type; \
    typedef Traits::flags_type flags_type; \
    typedef Traits::address_type address_type; \
    typedef Traits::result_type result_type;

//---------------------------------------------------------------------------
namespace borg {
namespace net {

enum status_t
{
  failure = -1,
  success = 0
};
  
WRAP_PATTERN_FORWARD(socket)
WRAP_PATTERN_FORWARD(tcp_socket)
WRAP_PATTERN_FORWARD(udp_socket)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct socket_interface 
{
  BORG_NET_SOCKET_TYPES(typename Traits)
  
  typedef socket_impl<Traits> impl;
  
  status_t
  connect(const address_t<Traits> &addr, interval_time_t<Traits> timeout)
  {
    return (status_t)impl::connect(dereference_cast<Derived>(this), addr, timeout);
  }
  
  result_type
  send(const void *buf, size_type n, flags_type flags, interval_time_t<Traits> timeout)
  {
    return (status_t)impl::send(dereference_cast<Derived>(this), buf, n, flags, timeout);
  }
  
  result_type
  recv(void *buf, size_type n, flags_type flags, interval_time_t<Traits> timeout)
  {
    return (status_t)impl::recv(dereference_cast<Derived>(this), buf, n, flags, timeout);
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct tcp_socket_interface : socket_interface<Traits, Derived>
{
  BORG_NET_SOCKET_TYPES(typename Traits)
  
  typedef tcp_socket_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct udp_socket_interface : socket_interface<Traits, Derived>
{
  BORG_NET_SOCKET_TYPES(typename Traits)
  
  typedef tcp_socket_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct socket_facade
{
};
  
//---------------------------------------------------------------------------
template<class Traits>
class socket_t
    : public wrapper< typename Traits::socket_type >
    , public socket_interface< Traits, socket_t<Traits> >
    , public socket_facade< Traits, socket_t<Traits> >
{
public:
  typedef typename Traits::socket_type socket_type;
  typedef wrapper<socket_type> base_type;

  socket_t(socket_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  socket_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

//---------------------------------------------------------------------------
template<class Traits>
class tcp_socket
    : public tcp_socket_interface< Traits, socket_t<Traits> >
    , public socket_facade< Traits, socket_t<Traits> >
{
public:
  BORG_NET_SOCKET_TYPES(typename Traits)

  typedef tcp_socket_impl<Traits> impl;

  tcp_socket() 
    : m_sock(impl::create())
  {
  }

  ~tcp_socket()
  {
    impl::destroy(m_sock);
  }
  
private:
  socket_type m_sock;
};

} // namespace net
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NET_SOCKET_HPP
