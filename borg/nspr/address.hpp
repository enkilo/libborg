#ifndef BORG_NSPR_ADDRESS_HPP
#define BORG_NSPR_ADDRESS_HPP

#include <borg/net/address.hpp>
#include <borg/nspr/traits.hpp>

#include <nspr/prnetdb.h>

namespace borg {
namespace net {

//----------------------------------------------------------------------------
template<>
struct address_impl< nspr::traits >
{
  BORG_NET_ADDRESS_TYPES( nspr::traits )

  static status_type
  aton(const string_type &a, address_type *n)
  {
    return ::PR_StringToNetAddr(a, n);
  }
  
  static std::string
  to_string(const address_type *a)
  {
    char str[1024];
    
    if(::PR_NetAddrToString(a, str, sizeof(str)) == PR_FAILURE)
      str[0] = '\0';
      
    return str;
  }
  
  static port_type
  get_port(const address_type *a)
  {
    switch(a->raw.family)
    {
      case PR_AF_INET:
      case PR_AF_INET6:
        return PR_ntohs(a->inet.port);
      default: 
        return 0;
    }
  }
  
  static void
  set_port(address_type *a, port_type port)
  {
    a->inet.port = PR_htons(port);
  }
  
};
  
//----------------------------------------------------------------------------
template<>
struct ipv4_address_impl< nspr::traits > : address_impl< nspr::traits >
{
  BORG_NET_ADDRESS_TYPES( nspr::traits )

};

//----------------------------------------------------------------------------
template<>
struct ipv6_address_impl< nspr::traits >
{
  BORG_NET_ADDRESS_TYPES( nspr::traits )

  
};
  
//----------------------------------------------------------------------------

} // namespace net
namespace nspr {

typedef net::address_t<traits> address_t;
typedef net::address<traits> address;

typedef net::ipv4_address<traits> ipv4_address;
typedef net::ipv6_address<traits> ipv6_address;

} // namespace nspr
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_NSPR_ADDRESS_HPP
