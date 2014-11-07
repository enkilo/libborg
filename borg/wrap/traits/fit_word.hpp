#ifndef BORG_WRAP_FIT_WORD_HPP
#define BORG_WRAP_FIT_WORD_HPP

#include <borg/wrap/traits/add_const_reference.hpp>
#include <borg/wrap/traits/remove_const_reference.hpp>
#include <borg/wrap/traits/make_reference.hpp>
#include <borg/wrap/traits/reference_to_pointer.hpp>
#include <borg/wrap/traits/make_const_reference.hpp>

#include <boost/type_traits/detail/bool_trait_def.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {

//! Coreementation details.
namespace detail {

//! Assume this to be the processor word size.
struct word
{
  typedef long type;
  BOOST_STATIC_CONSTANT(size_t, size = sizeof(type));
  BOOST_STATIC_CONSTANT(size_t, bits = size * 8);
};
  
//! Identifies types which fit a processor word.
//! From the view of the ABI, references are pointers, so we convert them
//! to pointers prior to the sizeof() operator.
//! This will prevent ending up with the size of the referencee.
template<typename T> 
  struct fits_word_impl
{
  BOOST_STATIC_CONSTANT(
      bool, value =
        (sizeof(typename reference_to_pointer<T>::type) <= ::borg::detail::word::size));
};

} // namespace detail

//! Declare the fits_word<T> metafunction.
BOOST_TT_AUX_BOOL_TRAIT_DEF1(
    fits_word, T, 
    ::borg::detail::fits_word_impl<T>::value)
  
//! Transforms the supplied type into a type that fits into a processor word
//! by adding const-reference specifiers if necessary.
template<typename T>
  struct fit_into_word
{
  typedef typename boost::mpl::if_<
    ::borg::fits_word<T>,
    T,
    typename ::borg::make_const_reference<T>::type
  >::type type;

  BOOST_MPL_AUX_LAMBDA_SUPPORT(1, fit_into_word, (T))
};

} // end of namespace borg

#include <boost/type_traits/detail/bool_trait_undef.hpp>

//---------------------------------------------------------------------------
#endif //ndef BORG_WRAP_FIT_WORD_HPP
