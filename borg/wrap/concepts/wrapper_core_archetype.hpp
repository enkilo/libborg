#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  wrapper_impl_archetype.hpp  
//! \brief Implements wrapper_impl_archetype.
//! \svn   $Id: wrapper_impl_archetype.hpp 34 2007-03-21 21:11:07Z nexbyte $
//----------------------------------------------------------------------------
#ifndef WRAPPER_COREARCHETYPE_HPP
#define WRAPPER_COREARCHETYPE_HPP

#include <wrap/wrap_traits.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! Wrapper implementation archetype.
//----------------------------------------------------------------------------
template< class value, 
          class traits = wrap_traits<T> >
struct wrapper_impl_archetype
{
  WRAP_TRAITS(traits)

  template<class impl>
  explicit
  wrapper_impl_archetype(const impl &w)
    : m_wrapee(w.get()) {}

  explicit 
  wrapper_impl_archetype(init_type w)
    : m_wrapee(w) {}

  const wrap_type &
  get() const { return m_wrapee; }

  wrap_type &
  get() { return m_wrapee; }
  
  template<class param>
  typename lazy_enable_if< is_assignable_to<param, wrap_type>, 
                           this_type & >
  set(param w)
  { 
    m_wrapee = w;
    return *this;
  }
  
private:
  wrap_type m_wrapee;  
};

} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef WRAPPER_COREARCHETYPE_HPP
