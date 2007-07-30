#ifndef BORG_NET_ADDRESS_HPP
#define BORG_NET_ADDRESS_HPP

#include <boost/ref.hpp>
#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/reference.hpp>
#include <borg/util/dereference_cast.hpp>

#define BORG_NET_ADDRESS_TYPES(Traits) \
    typedef Traits::af_type af_type; \
    typedef Traits::port_type port_type; \
    typedef Traits::address_type address_type; \
    typedef Traits::string_type string_type; \
    typedef Traits::status_type status_type; \
    typedef Traits::result_type result_type;

//---------------------------------------------------------------------------
namespace borg {
namespace net {

WRAP_PATTERN_FORWARD(address)
WRAP_PATTERN_FORWARD(ipv4_address)
WRAP_PATTERN_FORWARD(ipv6_address)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct address_interface
{
  BORG_NET_ADDRESS_TYPES(typename Traits)
  
  typedef address_impl<Traits> impl;
  
  std::string
  to_string() const
  {
    return impl::to_string(dereference_cast<Derived const>(this).get());
  }
  
  port_type
  get_port() const
  {
    return impl::get_port(dereference_cast<Derived const>(this).get());
  }
  
  void
  set_port(port_type p)
  {
    impl::set_port(dereference_cast<Derived>(this).get(), p);
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct ipv4_address_interface : address_interface<Traits, Derived>
{
  BORG_NET_ADDRESS_TYPES(typename Traits)
  
  typedef ipv4_address_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct ipv6_address_interface : address_interface<Traits, Derived>
{
  BORG_NET_ADDRESS_TYPES(typename Traits)
  
  typedef ipv4_address_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct address_facade
{
  BORG_NET_ADDRESS_TYPES(typename Traits)
    
  operator address_type &()
  {
    return *dereference_cast<Derived>(this).get();
  }
    
  operator const address_type &()
  {
    return *dereference_cast<Derived const>(this).get();
  }
};
  
//---------------------------------------------------------------------------
template<class Traits>
class address_t
    : public reference<typename Traits::address_type>
    , public address_interface< Traits, address_t<Traits> >
    , public address_facade< Traits, address_t<Traits> >
{
public:
  BORG_NET_ADDRESS_TYPES(typename Traits)
  typedef reference<typename Traits::address_type> base_type;

  address_t(typename Traits::address_type &v)
    : base_type(v)
  {}

/*  address_t(const reference<typename Traits::address_type> &v)
    : base_type(v) 
  {}*/

  address_t(ipv4_address<Traits> &a)
    : base_type(*a.get())
  {}

  address_t(ipv6_address<Traits> &a)
    : base_type(*a.get())
  {}
  
  address_type *
    get() { std::cout << "address* = " << (void *)base_type::get_pointer() << std::endl; return base_type::get_pointer(); }

  const address_type *
  get() const { return base_type::get_pointer(); }
  
  template<template<class> class Addr>
  address_t<Traits> &
  operator=(Addr<Traits> &a)
  {
    *reinterpret_cast<boost::reference_wrapper<typename Traits::address_type> *>(this) = boost::ref(a);
    return *this;
  }
  
};

//---------------------------------------------------------------------------
template<class Traits>
class ipv4_address
    : public ipv4_address_interface< Traits, ipv4_address<Traits> >
    , public address_facade< Traits, ipv4_address<Traits> >
{
public:
  BORG_NET_ADDRESS_TYPES(typename Traits)

  typedef ipv4_address_impl<Traits> impl;

  ipv4_address(const string_type &str)
  {
    // TODO: throw if conversion failed.
    impl::aton(str, &m_addr);
  }

  ~ipv4_address()
  {
  }
  
  address_type *
  get() { return boost::addressof(m_addr); }
  
  const address_type *
  get() const { return boost::addressof(m_addr); }      
  
private:
  address_type m_addr;
};

} // namespace net
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NET_ADDRESS_HPP
