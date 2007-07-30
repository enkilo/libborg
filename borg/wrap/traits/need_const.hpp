//----------------------------------------------------------------------------
//! \file need_const.hpp
//! \svn  $Id: need_const.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef NEED_CONST_HPP
#define NEED_CONST_HPP

#include <boost/type_traits.hpp>

namespace borg {

//! Force addition of a const specifier to the supplied type. 
//! boost::add_const would silently return the same type if it were a
//! reference while borg::need_const re-checks the type using
//! BOOST_STATIC_ASSERT.
template<typename T>
  struct need_const : public boost::add_const<T>
{
  // Must not be a reference, because references themselves need not be
  // associated with storage and therefore they imply constness and do not
  // let us apply an explicit const specifier.
  // 
  // This is obsolete, the assertion below will catch situations like this
  // more generally.
  //BOOST_STATIC_ASSERT(::boost::is_reference<T>::value == false);
  
  // Assertion will fail when the const specifier could not be applied.
  BOOST_STATIC_ASSERT(
    boost::is_const< typename boost::add_const<T>::type >::value
  );

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, need_const, (T))
};

} // namespace borg
#endif //ndef NEED_CONST_HPP
