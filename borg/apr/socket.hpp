#ifndef BORG_APR_SOCKET_HPP
#define BORG_APR_SOCKET_HPP

#include <borg/net/socket.hpp>
#include <borg/apr/traits.hpp>
#include <borg/apr/address.hpp>
#include <borg/apr/interval_time.hpp>

namespace borg {
namespace net {

#define BORG_APR_SOCKET_TYPES(Traits) \
    BORG_NET_SOCKET_TYPES(Traits) \
    typedef Traits::pool_type pool_type;
  
//----------------------------------------------------------------------------
template<>
struct socket_impl< apr::traits >
{
  BORG_APR_SOCKET_TYPES( apr::traits )

  enum shutdown_type
  {
    shutdown_recv = ::APR_SHUTDOWN_READ,
    shutdown_send = ::APR_SHUTDOWN_WRITE,
    shutdown_both = ::APR_SHUTDOWN_READWRITE
  };
    
  static void
  destroy(socket_type &sock)
  {
    apr_socket_close(sock);
    sock = 0;
  }  
  
  static status_type
  connect(const socket_type &sock, const address_type &addr)
  {
    return ::apr_socket_connect(sock, addr);
  }
  
  static socket_type
  accept(const socket_type &sock, const pool_type &pool)
  {
    apr_socket_t *newsock;
    
    if(::apr_socket_accept(&newsock, sock, pool) != APR_SUCCESS)
      newsock = 0;
    
    return newsock;
  }
  
  static status_type
  bind(const socket_type &sock, const address_type &addr)
  {
    return ::apr_socket_bind(sock, addr);
  }
  
  static status_type
  listen(const socket_type &sock, const size_type backlog)
  {
    return ::apr_socket_listen(sock, backlog);
  }
  
  static status_type
  shutdown(const socket_type &sock, const shutdown_type how)
  {
    return ::apr_socket_shutdown(sock, (apr_shutdown_how_e)how);
  }
  
  static result_type
  recv(const socket_type &sock, void *buf, size_type &n)
  {
    return ::apr_socket_recv(sock, (char *)buf, &n);
  }
  
  static result_type
  send(const socket_type &sock, const void *buf, size_type &n)
  {
    return ::apr_socket_send(sock, (const char *)buf, &n);
  }
};
  
//----------------------------------------------------------------------------
template<>
struct tcp_socket_impl< apr::traits > : socket_impl< apr::traits >
{
  BORG_APR_SOCKET_TYPES( apr::traits )

  static socket_type 
  create(const pool_type &pool) 
  { 
    apr_socket_t *ret;

    if(apr_socket_create(&ret, APR_INET, SOCK_STREAM, APR_PROTO_TCP, pool) != APR_SUCCESS)
      ret = 0;
    
    return ret;
  }

  static socket_type
  create(const af_type &af, const pool_type &pool) 
  { 
    apr_socket_t *ret;

    if(apr_socket_create(&ret, af, SOCK_STREAM, APR_PROTO_TCP, pool) != APR_SUCCESS)
      ret = 0;
    
    return ret;
  }
  
};

//----------------------------------------------------------------------------
template<>
struct udp_socket_impl< apr::traits >
{
  BORG_APR_SOCKET_TYPES( apr::traits )

  static socket_type
  create(const pool_type &pool)
  {
    apr_socket_t *ret;

    if(apr_socket_create(&ret, APR_INET, SOCK_DGRAM, APR_PROTO_UDP, pool) != APR_SUCCESS)
      ret = 0;
    
    return ret;
  }  
  
  
  
};
  
//----------------------------------------------------------------------------

} // namespace net
namespace apr {

typedef net::socket_t<traits> socket_t;
typedef net::socket<traits> socket;

typedef net::tcp_socket<traits> tcp_socket;
typedef net::udp_socket<traits> udp_socket;

} // namespace apr
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_APR_SOCKET_HPP
