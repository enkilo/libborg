//----------------------------------------------------------------------------
//! \file  is_mutable.hpp
//! \brief Provides the borg::is_mutable metafunction.
//! \svn   $Id: is_mutable.hpp 35 2007-03-21 22:09:24Z nexbyte $
//----------------------------------------------------------------------------
#ifndef IS_MUTABLE_HPP
#define IS_MUTABLE_HPP

#include <boost/type_traits.hpp>
#include "boost/type_traits/detail/bool_trait_def.hpp"

namespace borg 
{

//! Coreementation details.
namespace detail
{
  using namespace boost;
  
  //! Types which are changeable - as a whole and without invoking an assignment
  //! operator - after they are initialized. Qualifies for all non-const, 
  //! non-reference and non-function types which have a trivial assignment operator.
  template<typename T, bool trivially> 
    struct is_mutable_impl
  {
    BOOST_STATIC_CONSTANT(
        bool, value =
         (type_traits::ice_and<
            type_traits::ice_not< is_const<T>::value >::value,
            type_traits::ice_not< is_reference<T>::value >::value,
           (type_traits::ice_or<
              type_traits::ice_not<trivially>::value,
              has_trivial_assign<T>::value
            >::value)
         >::value));
  };
}

//! Declare the is_mutable<T, trivially> metafunction.
template<typename T, bool trivially = false>
  struct is_mutable
    BOOST_TT_AUX_BOOL_C_BASE((detail::is_mutable_impl<T, trivially>::value))
{
  BOOST_TT_AUX_BOOL_TRAIT_VALUE_DECL((detail::is_mutable_impl<T, trivially>::value))
  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_mutable, (T))
};

} // end of namespace borg

#include "boost/type_traits/detail/bool_trait_undef.hpp"

#endif // IS_MUTABLE_HPP
