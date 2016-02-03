//----------------------------------------------------------------------------
//! \file make_const.hpp
//! \svn  $Id: fit_word.hpp 34 2007-03-21 21:11:07Z nexbyte $
//----------------------------------------------------------------------------
#ifndef MAKE_CONST_HPP
#define MAKE_CONST_HPP

#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {

  
//! Make a const type from the supplied type. If the supplied type is 
//! already const, the resulting type stays the same.
template<typename T>
  struct make_const
{
  //! Not allowing reference types, see borg::add_const.
  BOOST_STATIC_ASSERT(boost::is_reference<T>::value == false);

  typedef typename boost::mpl::if_< boost::is_const<T>, T, T const >::type type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_const, (T))
};

} // end of namespace borg
#endif //ndef MAKE_CONST_HPP
