//----------------------------------------------------------------------------
//! \file  unwrap_cast.hpp
//! \brief Implements unwrap_cast<>.
//! \svn   $Id: wrapper_facade.hpp 13 2007-03-19 11:55:21Z nexbyte $
//----------------------------------------------------------------------------
#ifndef UNWRAP_CAST_HPP
#define UNWRAP_CAST_HPP

#include <borg/wrap/wrap_traits.hpp>
#include <borg/wrap/wrapper_core_access.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<typename T, template<class, class> class WrapperCore>
inline static typename wrap_traits<T>::unwrap_type 
unwrap_cast(const WrapperCore< T, wrap_traits<T> > &w)
{
  typedef typename wrap_traits<T>::unwrap_type unwrap_type;
  return wrapper_core_access::get(w);
}

//----------------------------------------------------------------------------
  
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef UNWRAP_CAST_HPP
