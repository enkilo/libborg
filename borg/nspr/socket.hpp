#ifndef BORG_NSPR_SOCKET_HPP
#define BORG_NSPR_SOCKET_HPP

#include <borg/net/socket.hpp>
#include <borg/nspr/traits.hpp>
#include <borg/nspr/address.hpp>
#include <borg/nspr/interval_time.hpp>

namespace borg {
namespace net {

//----------------------------------------------------------------------------
template<>
struct socket_impl< nspr::traits >
{
  BORG_NET_SOCKET_TYPES( nspr::traits )

  enum shutdown_type
  {
    shutdown_recv = ::PR_SHUTDOWN_RCV,
    shutdown_send = ::PR_SHUTDOWN_SEND,
    shutdown_both = ::PR_SHUTDOWN_BOTH
  };
    
  static void 
  destroy(socket_type &sock)
  {
    PR_Close(sock);
    sock = 0;
  }  
  
  static status_type
  connect(const socket_type &sock, const address_type &addr,
          const interval_time_t< nspr::traits > &timeout)
  {
    return ::PR_Connect(sock, &addr, timeout);
  }
  
  static socket_type
  accept(const socket_type &sock, address_type &addr,
         const interval_time_t< nspr::traits > &timeout)
  {
    return ::PR_Accept(sock, &addr, timeout);
  }
  
  static status_type
  bind(const socket_type &sock, const address_type &addr)
  {
    return ::PR_Bind(sock, &addr);
  }
  
  static status_type
  listen(const socket_type &sock, const size_type backlog)
  {
    return ::PR_Listen(sock, backlog);
  }
  
  static status_type
  shutdown(const socket_type &sock, const shutdown_type how)
  {
    return ::PR_Shutdown(sock, (const PRShutdownHow)how);
  }
  
  static result_type
  recv(const socket_type &sock, void *buf, const size_type n, 
       const flags_type flags, const interval_time_t< nspr::traits > &timeout)
  {
    return ::PR_Recv(sock, buf, n, flags, timeout);
  }
  
  static result_type
  send(const socket_type &sock, const void *buf, const size_type n, 
       const flags_type flags, const interval_time_t< nspr::traits > &timeout)
  {
    return ::PR_Send(sock, buf, n, flags, timeout);
  }
};
  
//----------------------------------------------------------------------------
template<>
struct tcp_socket_impl< nspr::traits > : socket_impl< nspr::traits >
{
  BORG_NET_SOCKET_TYPES( nspr::traits )

  static socket_type 
  create() 
  { 
    return ::PR_NewTCPSocket(); 
  }

  static socket_type
  create(const af_type &af) 
  { 
    return ::PR_OpenTCPSocket(af); 
  }
  
};

//----------------------------------------------------------------------------
template<>
struct udp_socket_impl< nspr::traits >
{
  BORG_NET_SOCKET_TYPES( nspr::traits )

  static socket_type
  create()
  {
    return ::PR_NewUDPSocket();
  }  
  
  
  
};
  
//----------------------------------------------------------------------------

} // namespace net
namespace nspr {

typedef net::socket_t<traits> socket_t;
typedef net::socket<traits> socket;

typedef net::tcp_socket<traits> tcp_socket;
typedef net::udp_socket<traits> udp_socket;

} // namespace nspr
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_NSPR_SOCKET_HPP
