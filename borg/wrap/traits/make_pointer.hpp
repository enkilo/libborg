//----------------------------------------------------------------------------
//! \file make_pointer.hpp
//! \svn $Id: fit_word.hpp 33 2007-03-21 20:56:30Z nexbyte $
//----------------------------------------------------------------------------
#ifndef MAKE_POINTER_HPP
#define MAKE_POINTER_HPP

#include <boost/type_traits.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {


//! Convert the supplied type into a pointer if it is a reference.
template<typename T>
  struct make_pointer
{
  typedef typename boost::mpl::if_<
    boost::is_reference<T>,
    typename boost::remove_reference<T>::type *,
    T
  >::type type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, make_pointer, (T))
};

} // end of namespace borg
#endif //ndef MAKE_POINTER_HPP
