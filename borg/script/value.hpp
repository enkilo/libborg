#ifndef BORG_SCRIPT_VALUE_HPP
#define BORG_SCRIPT_VALUE_HPP

//---------------------------------------------------------------------------
//! Generic wrapper for script-language value objects like 'zval's for php's
//! Zend engine, 'jsval's for the SpiderMonkey JavaScript language.
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
WRAP_PATTERN_FORWARD(value)
    
//---------------------------------------------------------------------------
//! Typedef forwarding macro.
//---------------------------------------------------------------------------
#define BORG_SCRIPT_VALUE_TYPES(Traits) \
    typedef Traits::value_type value_type;
    
//---------------------------------------------------------------------------
//! Generic interface containing concrete interface methods for said value
//! objects.
//---------------------------------------------------------------------------
template<class Derived, class Traits>
struct value_interface
{
  BORG_SCRIPT_VALUE_TYPES(typename Traits)

  typedef value_impl<Traits> impl;
  
/*  template<class T>
  void 
  set(const T &val)
  {
    impl::set(dereference_cast<Derived const>(this), val);
  }
  
  template<class T>
  T
  get() const
  {
    return impl::get(dereference_cast<Derived const>(this));
  }*/

  void
  print_r(int indent = 2) const
  {
    return impl::print_r(&dereference_cast<Derived const>(this).get(), indent);
  }
};
  
//---------------------------------------------------------------------------
//! Facade template, containing operators and STL support for script-language
//! value objects.
//---------------------------------------------------------------------------
template<class Derived, class Traits>
struct value_facade
{
  BORG_SCRIPT_VALUE_TYPES(typename Traits)

  //! Assignment operator template.
  //-------------------------------------------------------------------
  template<class T>
  Derived &
  operator=(const T &val)
  {
    return dereference_cast<Derived>(this).set(val);
  }
  
  //! Type conversion operator template.
  //-------------------------------------------------------------------
/*  template<class ValueT>
  operator ValueT() const
  {
    return borg::wrapper_core_access::get(dereference_cast<Derived const>(this));
  }*/
};
  
//---------------------------------------------------------------------------
//! Adapter template, takes a native instance (e.g. zval, jsval) and wraps it
//! up into the generic interface.
//---------------------------------------------------------------------------
template<class Traits>
class value_t : public wrapper< typename Traits::value_type >
              , public value_interface< value<Traits>, Traits >
              , public value_facade< value<Traits>, Traits >
{
  BORG_SCRIPT_VALUE_TYPES(typename Traits)
  
public:

  value_t(const value_type &val) : wrapper<value_type>(val)
  {}
};

//---------------------------------------------------------------------------
//! Concrete class template, constructs and destructs native values 
//! appropriately.
//---------------------------------------------------------------------------
template<class Traits>
class value : public value_interface< value<Traits>, Traits >
            , public value_facade< value<Traits>, Traits >
{
  BORG_SCRIPT_VALUE_TYPES(typename Traits)
//  BORG_PP_USE_TYPE(typename Traits, value_type)

  value_type        m_value;
  value_type       &get()       { return m_value; }
  value_type const &get() const { return m_value; }

/*  friend class value_impl<Traits>;
  friend class value_facade<Traits, value<Traits> >;*/
  friend class value_interface< value<Traits>, Traits >;

public:
  value() : m_value() 
  {}

  value(const value_t<Traits> &val) : m_value(val) 
  {}
};
  
}// namespace script
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_SCRIPT_VALUE_HPP
