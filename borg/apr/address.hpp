#ifndef BORG_APR_ADDRESS_HPP
#define BORG_APR_ADDRESS_HPP

#include <borg/net/address.hpp>
#include <borg/apr/traits.hpp>

#include <apr_network_io.h>

namespace borg {
namespace net {

#define BORG_APR_ADDRESS_TYPES(Traits) \
    BORG_NET_ADDRESS_TYPES(Traits) \
    typedef Traits::pool_type pool_type;
  
//----------------------------------------------------------------------------
template<>
struct address_impl< apr::traits >
{
  BORG_APR_ADDRESS_TYPES( apr::traits )

  static status_type
  aton(const string_type &a, address_type &n, const pool_type &pool)
  {
    return ::apr_sockaddr_info_get(&n, a, APR_UNSPEC, 0, 0, pool);
  }
  
  static std::string
  to_string(const address_type &a)
  {
    char *str;
    
    if(::apr_getnameinfo(&str, a, 0) != APR_SUCCESS)
      str = 0;

    return str ? str : "";
  }
  
  static port_type
  get_port(const address_type &a)
  {
    return a->port;
  }
  
  static void
  set_port(const address_type &a, port_type port)
  {
    a->port = port;
  }
  
};
  
//----------------------------------------------------------------------------
template<>
struct ipv4_address_impl< apr::traits > : address_impl< apr::traits >
{
  BORG_NET_ADDRESS_TYPES( apr::traits )

};

//----------------------------------------------------------------------------
template<>
struct ipv6_address_impl< apr::traits >
{
  BORG_NET_ADDRESS_TYPES( apr::traits )

  
};
  
//----------------------------------------------------------------------------

} // namespace net
namespace apr {

typedef net::address_t<traits> address_t;
typedef net::address<traits> address;

typedef net::ipv4_address<traits> ipv4_address;
typedef net::ipv6_address<traits> ipv6_address;

} // namespace apr
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_APR_ADDRESS_HPP
