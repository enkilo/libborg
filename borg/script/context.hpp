#ifndef BORG_SCRIPT_CONTEXT_HPP
#define BORG_SCRIPT_CONTEXT_HPP

//---------------------------------------------------------------------------
//! Generic wrapper for script-language context objects like JSContext.
//---------------------------------------------------------------------------

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/wrapper_core_access.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/script/runtime.hpp>

namespace borg {
namespace script {

using borg::wrapper;
  
//---------------------------------------------------------------------------
//! Forward declaration for the pattern templates.
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(context)
    
//---------------------------------------------------------------------------
//! Typedef forwarding macro.
//---------------------------------------------------------------------------
#define BORG_SCRIPT_CONTEXT_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, context_type) \
    BORG_PP_USE_TYPE(Traits, runtime_type) \
    BORG_PP_USE_TYPE(Traits, length_type)
    
//---------------------------------------------------------------------------
//! Generic interface containing concrete interface methods for said context
//! objects.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct context_interface
{
  BORG_SCRIPT_CONTEXT_TYPES(typename Traits)

  typedef context_impl<Traits> impl;

};
  
//---------------------------------------------------------------------------
//! Facade template, containing operators and STL support for script-language
//! context objects.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct context_facade
{
  BORG_SCRIPT_CONTEXT_TYPES(typename Traits)

  typedef context_impl<Traits> impl;
};
  
//---------------------------------------------------------------------------
//! Adapter template, takes a native instance (e.g. JSContext) and wraps it
//! up into the generic interface.
//---------------------------------------------------------------------------
template<class Traits>
class context_t : public wrapper<typename Traits::context_type>
                , public context_interface<Traits, context<Traits> >
                , public context_facade<Traits, context<Traits> >
{
  BORG_SCRIPT_CONTEXT_TYPES(typename Traits)
  
  typedef context_impl<Traits> impl;

public:

  context_t(const context_type &val)
    : wrapper<context_type>(val)
  {}

  template<template<class> class Context>
  context_t(const Context<Traits> &val)
    : wrapper<context_type>(val)
  {}
};

//---------------------------------------------------------------------------
//! Concrete class template, constructs and destructs native contexts 
//! appropriately.
//---------------------------------------------------------------------------
template<class Traits>
class context : public context_interface<Traits, context<Traits> >
              , public context_facade<Traits, context<Traits> >
{
  BORG_SCRIPT_CONTEXT_TYPES(typename Traits)
    
  typedef context_impl<Traits> impl;

  typename Traits::context_type m_cx;
/*  typename Traits::context_type &get() { return m_cx; }
  typename Traits::context_type const &get() const { return m_cx; }

  friend class context_impl<Traits>;
  friend class context_interface<Traits, context<Traits> >;
  friend class context_facade<Traits, context<Traits> >;*/
  
  //! Suppress copy constructor.
  context(const context<Traits> &cx);
  
public:
  context()
    : m_cx(impl::create())
  {}
  
  template<template<class> class Runtime>
  context(const Runtime<Traits> &rt) 
    : m_cx(impl::create(rt))
  {}

  template<template<class> class Runtime>
  context(const Runtime<Traits> &rt, length_type stack) 
    : m_cx(impl::create(rt, stack))
  {}
  
  ~context()
  {
    impl::destroy(*this);
  }
  
  operator const context_type &() const { return m_cx; }
  operator context_type &() { return m_cx; }
};
  
}// namespace script
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_SCRIPT_CONTEXT_HPP
