#ifndef BORG_XML_ADAPTER_MACROS_HPP
#define BORG_XML_ADAPTER_MACROS_HPP

#include <borg/wrap/wrapper.hpp>

namespace borg {
namespace xml {

//---------------------------------------------------------------------------
//! Most adapters will want to use this wrapper.
//---------------------------------------------------------------------------
using borg::wrapper;
using borg::wrap_traits;

//---------------------------------------------------------------------------
//! Declaration of an adapter class.
//---------------------------------------------------------------------------
#define XML_ADAPTER_DECL_0(name) \
  template<class Traits> \
  class name ## _t \
    : public wrapper<typename Traits:: name ## _type, wrap_traits< typename Traits:: name ## _type > > \
      , public name ## _interface< Traits, name ## _t<Traits> > \
      , public name ## _facade< Traits, name ## _t<Traits> >

//---------------------------------------------------------------------------
//! Implementation of an adapter class.
//---------------------------------------------------------------------------
#define XML_ADAPTER_IMPL_0(name) \
  { \
  public: \
    typedef typename Traits::name ## _type name ## _type; \
    typedef wrapper<name ## _type> base_type; \
  \
    name ## _t(name ## _type const &v) \
        : base_type(v) \
    {} \
  \
    name ## _t(const name ##_t<Traits> &v) \
        : base_type(borg::unwrap_cast(v)) \
    {} \
  };
  
//---------------------------------------------------------------------------
//! Implementation and declaration.
//---------------------------------------------------------------------------
#define XML_ADAPTER_CLASS_0(name) \
  XML_ADAPTER_DECL_0(name) \
  XML_ADAPTER_IMPL_0(name)
  
//---------------------------------------------------------------------------
//! Declaration of an adapter class taking 1 extra template argument.
//---------------------------------------------------------------------------
#define XML_ADAPTER_DECL_1(name) \
  template<class Traits, class T> \
  class name ## _t \
      : public wrapper<T /*typename Traits::template name<T>::type*/> \
      , public name ## _interface< Traits, name ## _t<Traits, T>, T > \
      , public name ## _facade< Traits, name ## _t<Traits, T>, T >

//---------------------------------------------------------------------------
//! Implementation of an adapter class taking 1 extra template argument.
//---------------------------------------------------------------------------
#define XML_ADAPTER_IMPL_1(name) \
  { \
  public: \
    XML_LIB_TYPES(typename Traits) \
    typedef wrapper<T> base_type; \
  \
    name ## _t(const T &v) \
      : base_type(v) \
    {} \
  };
  
//---------------------------------------------------------------------------
#define XML_ADAPTER_CLASS_1(name) \
  XML_ADAPTER_DECL_1(name) \
  XML_ADAPTER_IMPL_1(name)

//---------------------------------------------------------------------------
#define XML_ADAPTER_DECL_T(name) \
  template<class Traits, template<class> class Tmpl> \
  class name ## _t \
      : public wrapper<typename Traits::name ## _type> \
      , public name ## _interface< Traits, name ## _t<Traits, Tmpl>, Tmpl > \
      , public name ## _facade< Traits, name ## _t<Traits, Tmpl>, Tmpl >

//---------------------------------------------------------------------------
//! Implementation of an adapter class taking 1 extra template argument.
//---------------------------------------------------------------------------
#define XML_ADAPTER_IMPL_T(name) \
  { \
  public: \
    XML_LIB_TYPES(typename Traits) \
    typedef typename Traits::name ## _type name ## _type; \
    typedef wrapper<name ## _type> base_type; \
  \
    name ## _t(name ## _type const &v) \
      : base_type(v) \
    {} \
  \
    template<template<class> class U> \
    name ## _t(name ## _t< Traits, U > const &a) \
      : base_type(a) \
    {} \
  };
  
//---------------------------------------------------------------------------
#define XML_ADAPTER_CLASS_T(name) \
  XML_ADAPTER_DECL_T(name) \
  XML_ADAPTER_IMPL_T(name)

//---------------------------------------------------------------------------
//! Instantiate adapter template in the namespace of the implementation.
//---------------------------------------------------------------------------
#define XML_ADAPTER_USE_0(ns, name) \
  namespace ns { typedef ::borg::xml::ns::name ## _t<traits> name ## _t; }

} // namespace xml
} // namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef BORG_XML_ADAPTER_MACROS_HPP
