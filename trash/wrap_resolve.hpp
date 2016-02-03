#warning "obsolete"
//----------------------------------------------------------------------------
//! \file wrap_resolve.hpp
//! \svn  $Id: wrap_resolve.hpp 66 2007-04-03 17:06:06Z nexbyte $
//!
//! Implements wrap::resolve, the wrapping class resolver.
//----------------------------------------------------------------------------
#ifndef WRAP_RESOLVE_HPP
#define WRAP_RESOLVE_HPP

#include <boost/type_traits.hpp>
#include <wrap/pointer.hpp>
#include <wrap/reference.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace wrap {

  using namespace boost;
  
  template<typename wrapT, bool isPtr, bool isRef>
    struct resolve
  {    
    typedef wrapT wrap_type;
    typedef encapsulate<wrapT> wrapper_type;
  };

  template<typename wrapT>
    struct resolve<wrapT, true, false>
  {
    typedef typename boost::remove_pointer<wrapT>::type wrap_type;
    typedef pointer<wrap_type> wrapper_type;
  };
  
  template<typename wrapT>
    struct resolve<wrapT, false, true>
  {
    typedef typename boost::remove_reference<wrapT>::type wrap_type;
    typedef reference<wrap_type> wrapper_type;
  };

  template<typename wrapT>
    struct traits : public resolve<wrapT,
                                   boost::is_pointer<wrapT>::value,
                                   boost::is_reference<wrapT>::value >
  {};
  

} // end of namespace wrap

#endif //ndef WRAP_RESOLVE_HPP
