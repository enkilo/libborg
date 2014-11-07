//----------------------------------------------------------------------------
//! \file  wrap_traits.hpp
//! \brief Provides type traits used in conjunction with wrappers.
//! \svn   $Id: wrap_traits.hpp 68 2007-04-03 19:59:53Z nexbyte $
//----------------------------------------------------------------------------
#ifndef BORG_WRAP_TRAITS_HPP
#define BORG_WRAP_TRAITS_HPP

#include <boost/type_traits.hpp>
#include <boost/call_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/ref.hpp>

#include <borg/wrap/traits/is_mutable.hpp>
#include <borg/wrap/traits/is_assignable_to.hpp>
#include <borg/wrap/traits/fit_word.hpp>
#include <borg/wrap/traits/remove_leftmost_const.hpp>
#include <borg/wrap/traits/make_reference.hpp>
#include <boost/utility/enable_if.hpp>

//----------------------------------------------------------------------------
//! Provides generic wrapping objects.
//----------------------------------------------------------------------------
namespace borg {

//! Wraps references to T into boost::reference_wrapper<T>.
template<typename T>
struct wrap_reference
{
  typedef typename boost::mpl::if_<
      boost::is_reference<T>,
      boost::reference_wrapper<typename boost::remove_reference<T>::type>,
      T 
  >::type type;
};

//! Provides types used within wrapper classes.
template<class T>
struct wrap_traits : boost::call_traits<T>
{
  //! Is the type changeable once it has been initialized?
  //! false for references and consts.
  BOOST_STATIC_CONSTANT(bool, is_mutable = borg::is_mutable<T>::value);

  //! This type.
  typedef wrap_traits<T> wrapper_traits;
  
  //! The analogous const (non-mutable) traits.
  typedef wrap_traits<T const> const_traits;
  
  //! The analogous non-const (mutable) traits.
  typedef wrap_traits<typename boost::remove_const<T>::type> mutable_traits;
  
  //! One-way compatible traits having no leftmost const specifier.
  typedef wrap_traits<typename remove_leftmost_const<T>::type> no_leftconst_traits;
  
  //! Type which is to be wrapped.
  typedef T value_type;

  //! type & -> type *const
  typedef typename reference_to_pointer<T>::type pointer_type;

  //! type & -> type *const
  typedef typename boost::lazy_enable_if_c<
      borg::is_mutable<T>::value,
      typename make_reference<T>::type > 
  reference;
  
  //! type [const] [&] -> type
  typedef typename remove_const_reference<T>::type plain_type;
  
  //! Type which is effectively wrapped.
  typedef typename wrap_reference<T>::type wrap_type;

  //! Type which is used as parameter in wrapper constructors.
  typedef typename boost::call_traits<T>::param_type init_type;
  
  //! Type which is used as return value on unwrapping.
  typedef typename fit_into_word<T>::type unwrap_type;
};

#define BORG_WRAP_TRAITS_TYPE(Traits, name) \
  typedef Traits::name name;
  
#define BORG_WRAP_TRAITS(Traits) \
  BORG_WRAP_TRAITS_TYPE(Traits, wrapper_traits) \
  BORG_WRAP_TRAITS_TYPE(Traits, const_traits) \
  BORG_WRAP_TRAITS_TYPE(Traits, mutable_traits) \
  BORG_WRAP_TRAITS_TYPE(Traits, no_leftconst_traits) \
  BORG_WRAP_TRAITS_TYPE(Traits, value_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, pointer_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, plain_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, wrap_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, init_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, param_type) \
  BORG_WRAP_TRAITS_TYPE(Traits, unwrap_type)
  
} // end of namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WRAP_TRAITS_HPP
