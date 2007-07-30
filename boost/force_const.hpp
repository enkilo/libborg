#warning "obsolete"

//  (C) Copyright Roman Senn 2007.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#ifndef BOOST_TT_FORCE_CONST_HPP_INCLUDED
#define BOOST_TT_FORCE_CONST_HPP_INCLUDED

#include "boost/type_traits/add_const.hpp"

namespace boost {

//! Force const specifier to the supplied type. Will yield an assertion 
//! failure when the const specifier could not be applied.
template<typename T>
  struct force_const : public ::boost::add_const<T>
{
  // Must not be a reference, because references themselves need not be
  // associated with storage and therefore they imply constness and do not
  // let us apply an explicit const specifier.
  // This is obsolete, the assertion below will catch situations like this
  // more generally.
  //BOOST_STATIC_ASSERT(::boost::is_reference<T>::value == false);

  // Assertion will fail when the const specifier could not be applied.
  BOOST_STATIC_ASSERT(::boost::is_const<
                        typename ::boost::add_const<T>::type
                      >::value);

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, force_const, (T))
};

} // namespace boost

#endif // BOOST_TT_FORCE_CONST_HPP_INCLUDED
