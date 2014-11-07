#ifndef BORG_SCRIPT_RUNTIME_HPP
#define BORG_SCRIPT_RUNTIME_HPP

//---------------------------------------------------------------------------
//! Generic wrapper for script-language runtime objects like JSRuntime.
//---------------------------------------------------------------------------

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/wrapper_core_access.hpp>
#include <borg/util/dereference_cast.hpp>

namespace borg {
namespace script {

using borg::wrapper;
  
//---------------------------------------------------------------------------
//! Forward declaration for the pattern templates.
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(runtime)
    
//---------------------------------------------------------------------------
//! Typedef forwarding macro.
//---------------------------------------------------------------------------
#define BORG_SCRIPT_RUNTIME_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, context_type) \
    BORG_PP_USE_TYPE(Traits, runtime_type) \
    BORG_PP_USE_TYPE(Traits, length_type) \
    
//---------------------------------------------------------------------------
//! Generic interface containing concrete interface methods for said runtime
//! objects.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct runtime_interface
{
  BORG_SCRIPT_RUNTIME_TYPES(typename Traits)

  typedef runtime_impl<Traits> impl;

};
  
//---------------------------------------------------------------------------
//! Facade template, containing operators and STL support for script-language
//! runtime objects.
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct runtime_facade
{
  BORG_SCRIPT_RUNTIME_TYPES(typename Traits)

  typedef runtime_impl<Traits> impl;
};
  
//---------------------------------------------------------------------------
//! Adapter template, takes a native instance (e.g. JSRuntime) and wraps it
//! up into the generic interface.
//---------------------------------------------------------------------------
template<class Traits>
class runtime_t : public wrapper<typename Traits::runtime_type>
                , public runtime_interface<Traits, runtime<Traits> >
                , public runtime_facade<Traits, runtime<Traits> >
{
  BORG_SCRIPT_RUNTIME_TYPES(typename Traits)
  
  typedef runtime_impl<Traits> impl;

public:

  runtime_t(const runtime_type &val) : wrapper<runtime_type>(val)
  {}
};

//---------------------------------------------------------------------------
//! Concrete class template, constructs and destructs native runtimes 
//! appropriately.
//---------------------------------------------------------------------------
template<class Traits>
class runtime : public runtime_interface<Traits, runtime<Traits> >
              , public runtime_facade<Traits, runtime<Traits> >
{
  BORG_SCRIPT_RUNTIME_TYPES(typename Traits)
    
  typedef runtime_impl<Traits> impl;

  typename Traits::runtime_type m_rt;
/*  typename Traits::runtime_type &get() { return m_rt; }
  typename Traits::runtime_type const &get() const { return m_rt; }

  friend class runtime_impl<Traits>;
  friend class runtime_interface<Traits, runtime<Traits> >;
  friend class runtime_facade<Traits, runtime<Traits> >;*/
  
public:
  runtime() 
    : m_rt(impl::create())
  {}

  runtime(length_type stack)
    : m_rt(impl::create(stack))
  {}
  
  ~runtime()
  {
    impl::destroy(*this);
  }
  
  operator runtime_type() const { return m_rt; }    
  operator runtime_t<Traits>() const { return m_rt; }
    
};
  
}// namespace script
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_SCRIPT_RUNTIME_HPP
