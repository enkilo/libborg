#ifndef BORG_STRING_INTERFACE_HPP
#define BORG_STRING_INTERFACE_HPP

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/sequence.hpp>
#include <borg/string/traits.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Forward declare the string_impl class.
//---------------------------------------------------------------------------
template<class CharT, class Traits>
struct string_impl;
  
//---------------------------------------------------------------------------
//! Defines a generic interface for strings.
//!
//! Calls to any method are forwarded to static methods within the string
//! impl class. Arguments are passed using the implementation dependant
//! types defined by the Traits class.
//!
//! The Derived class which inherits from string_interface should be 
//! convertible to some type which is accepted as first argument of the 
//! static impl methods.
//---------------------------------------------------------------------------
template<class Derived, class CharT, class Traits>
struct string_interface 
    : public sequence_interface
      <
          Derived
        , typename Traits::string_type
        , CharT const *
        , CharT *
        , Traits
      >
{
  BORG_STRING_TYPES(typename Traits)

  //-----------------------------------------------------------------------
  //! Impl class which provides the implementation.
  //-----------------------------------------------------------------------
  typedef string_impl<CharT, Traits> impl;

  //-----------------------------------------------------------------------
  //! \name Iterator types, which are no more than pointers.
  //-----------------------------------------------------------------------
  //@{
  typedef CharT *iterator;
  typedef const CharT *const_iterator;
  //@}

  //-----------------------------------------------------------------------
  length_type
  length() const
  {
    return impl::length
      (dereference_cast<Derived const>(this));
  }
  
  //-----------------------------------------------------------------------
  //! Transcode string, which is possibly multibyte into a single-byte
  //! string (like std::string), preferrably using LATIN 1 resp. ISO-8859-1
  //! charset.
  //-----------------------------------------------------------------------
  char *
  transcode() const
  {
    return impl::transcode
      (dereference_cast<Derived const>(this));
  }
  
  //-----------------------------------------------------------------------
  //! Compare against another string (of the same implementation).
  //-----------------------------------------------------------------------
  template<template<class, class> class Tmpl, class Other>
  bool
  equal(const Tmpl<CharT, Other> &str) const
  {
    return impl::equal
      (dereference_cast<Derived const>(this), str);
  }

  template<class CharU>
  typename boost::enable_if_c< (boost::is_integral<CharT>::value && sizeof(CharT) == sizeof(CharU)), bool >::type
  equal(CharU const *str) const
  {
    return impl::equal
      (dereference_cast<Derived const>(this), (CharT const *)str);
  }
  
  //-----------------------------------------------------------------------
  //! Append another string (of the same implementation).
  //-----------------------------------------------------------------------
  Derived &
  append(Derived const &str)
  {
    dereference_cast<Derived>(this).set(
        impl::append(dereference_cast<Derived>(this).get(), str)
    );
    return dereference_cast<Derived>(this);
  }
  
  //-----------------------------------------------------------------------
  //! Append a character.
  //-----------------------------------------------------------------------
//  template<class T>
//  typename boost::enable_if< boost::is_convertible<CharT, T>, Derived & >::type
//  typename boost::enable_if_c< sizeof(CharT) == sizeof(T), Derived & >::type 
  Derived &
  append(CharT const ch)
  {
    dereference_cast<Derived>(this).set(
        impl::append(dereference_cast<Derived>(this).get(), ch)
    );
    return dereference_cast<Derived>(this);
  }
  
  //-----------------------------------------------------------------------
  //! Append any stuff.
  //-----------------------------------------------------------------------
  template<class T>
  typename boost::enable_if_c< sizeof(T) == sizeof(CharT), Derived & >::type
  append(T const *arg)
  {
    dereference_cast<Derived>(this).set(
      impl::append(dereference_cast<Derived>(this).get(), (CharT const *)arg)
    );
    return dereference_cast<Derived>(this);
  }
  
/*  Derived &
  append(Derived const &arg)
  {
    impl::append(dereference_cast<Derived>(this).get(), arg.get());
    return dereference_cast<Derived>(this);
  }*/
  
  //-----------------------------------------------------------------------
  //! Return null-terminated C string.
  //-----------------------------------------------------------------------
  const CharT *
  c_str()
  {
    return impl::c_str
      (dereference_cast<Derived>(this));
  }

  bool
  empty() const
  {
    return impl::empty
      (dereference_cast<Derived const>(this));
  }

  //-----------------------------------------------------------------------
  //! Convert the string to something.
  //-----------------------------------------------------------------------
  template<class T>
  typename boost::enable_if_c< !boost::is_same<CharT, T>::value, T const * >::type
  convert(T const *const &dummy = 0) const
  {
    typedef T const *ret_type;
    
    return impl::convert
      (dereference_cast<Derived const>(this), ret_type());
  }
  
  template<class T>
  typename boost::enable_if_c< !boost::is_same<CharT, T>::value, T * >::type
  convert(T const *const &dummy = 0)
  {
    typedef T *ret_type;
    
    return impl::convert
      (dereference_cast<Derived>(this), ret_type());
  }
  
  //-----------------------------------------------------------------------
  //! Extract substring.
  //-----------------------------------------------------------------------
  Derived
  substring(index_type i, length_type n) const
  {
    length_type len = dereference_cast<Derived const>(this).length();
    
    const_iterator const from = 
      dereference_cast<Derived const>(this).begin() + std::max(i, len);
    
    const_iterator const to =
      dereference_cast<Derived const>(this).begin() + std::max(i + n, len);

    return Derived(from, to);
  }
  
};

//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_STRING_INTERFACE_HPP
