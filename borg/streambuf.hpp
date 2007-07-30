#ifndef BORG_STREAMBUF_HPP
#define BORG_STREAMBUF_HPP

#include <streambuf>

namespace borg {

//---------------------------------------------------------------------------
//! Forward declare string classes.
//---------------------------------------------------------------------------
template<class Traits, class CharT>
struct string_impl;
  
template<class Traits, class CharT>
struct string_t;
  
template<class Traits, class CharT>
struct string;
  
  //WRAP_PATTERN_FORWARD(string, (class CharT))

//---------------------------------------------------------------------------
//! Macro to fetch all string-related typedefs from the traits class.
//!
//! The traits class delivers the types of the underlaying implementation.
//! Each line of this macro will expand to:
//!
//! typedef Traits::whatever_type whatever_type;
//!
//! ...that should already have explained why we decided to use the 
//! preprocessor here.
//---------------------------------------------------------------------------
#define BORG_STREAMBUF_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, string_type) \
  BORG_PP_USE_TYPE(Traits, const_string_type) \
  BORG_PP_USE_TYPE(Traits, char_type) \
  BORG_PP_USE_TYPE(Traits, wchar_type) \
  BORG_PP_USE_TYPE(Traits, size_type) \
  BORG_PP_USE_TYPE(Traits, index_type)
  
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
template<class Traits, class Derived, class CharT>
struct string_interface
{
  BORG_STREAMBUF_TYPES(typename Traits)

  //-----------------------------------------------------------------------
  //! Impl class which provides the implementation.
  //-----------------------------------------------------------------------
  typedef string_impl<Traits, CharT> impl;

  //-----------------------------------------------------------------------
  //! \name Iterator types, which are no more than pointers.
  //-----------------------------------------------------------------------
  //@{
  typedef CharT *iterator;
  typedef const CharT *const_iterator;
  //@}

  //-----------------------------------------------------------------------
  size_type
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
  bool
  equal(const string_t<Traits, CharT> &str) const
  {
    return impl::equal
      (dereference_cast<Derived const>(this), str);
  }
  
  //-----------------------------------------------------------------------
  //! Append another string (of the same implementation).
  //-----------------------------------------------------------------------
  template<template<class, class> class Tmpl, class Other>
  Derived &
  append(const Tmpl<Other, CharT> &str)
  {
    impl::append
      (dereference_cast<Derived>(this).get(), str);

    return dereference_cast<Derived>(this);
  }
  
  //-----------------------------------------------------------------------
  //! Append a character.
  //-----------------------------------------------------------------------
  template<class T>
  typename boost::enable_if< boost::is_convertible<T, CharT>, Derived & >::type
  append(T const ch)
  {
    impl::append(dereference_cast<Derived>(this).get(), ch);
    return dereference_cast<Derived>(this);
  }
  
  //-----------------------------------------------------------------------
  //! Append any stuff.
  //-----------------------------------------------------------------------
  template<class T>
  //typename boost::enable_if< boost::is_convertible<T, CharT>, Derived & >::type
  Derived &
  append(const T *arg)
  {
    impl::append(dereference_cast<Derived>(this).get(), arg);
    return dereference_cast<Derived>(this);
  }
  
  //-----------------------------------------------------------------------
  //! Return null-terminated C string.
  //-----------------------------------------------------------------------
  const CharT *
  c_str()
  {
    return impl::c_str
      (dereference_cast<Derived>(this));
  }

  //-----------------------------------------------------------------------
  //! Return an iterator which points to the beginning of the string.
  //-----------------------------------------------------------------------
  iterator
  begin() 
  {
    return impl::begin
      (dereference_cast<Derived>(this));
  }

  //-----------------------------------------------------------------------
  //! Return a constant iterator which points to the beginning of the 
  //! string.
  //-----------------------------------------------------------------------
  const_iterator
  begin() const 
  { 
    return impl::begin
      (dereference_cast<Derived const>(this)); 
  }

  //-----------------------------------------------------------------------
  //! Return an iterator which points to the end of the string.
  //-----------------------------------------------------------------------
  iterator
  end()
  { 
    return impl::end
      (dereference_cast<Derived>(this)); 
  }

  //-----------------------------------------------------------------------
  //! Return a const iterator which points to the end of the string.
  //-----------------------------------------------------------------------
  const_iterator
  end() const 
  {
    return impl::end
      (dereference_cast<Derived const>(this)); 
  }
  
  //-----------------------------------------------------------------------
  //! Convert the string to something.
  //-----------------------------------------------------------------------
  template<class T>
  typename boost::enable_if_c< !boost::is_same<T, CharT>::value, T const * >::type
  convert(T const *const &dummy = 0) const
  {
    typedef T const *ret_type;
    
    return impl::convert
      (dereference_cast<Derived const>(this), ret_type());
  }
  
  template<class T>
  typename boost::enable_if_c< !boost::is_same<T, CharT>::value, T * >::type
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
  substring(index_type i, size_type n) const
  {
    size_type len = dereference_cast<Derived const>(this).length();
    
    const_iterator const from = 
      dereference_cast<Derived const>(this).begin() + std::max(i, len);
    
    const_iterator const to =
      dereference_cast<Derived const>(this).begin() + std::max(i + n, len);

    return Derived(from, to);
  }
  
};

//---------------------------------------------------------------------------
//! The string facade implements the standard string operators and other
//! syntactic sugar ontop of the generic string interface.
//---------------------------------------------------------------------------
template<class Traits, class Derived, class CharT>
struct string_facade
    : public boost::equality_comparable< string_facade<Traits, Derived, CharT> >
{
  BORG_STREAMBUF_TYPES(typename Traits)

  typedef string_impl<Traits, CharT> impl;

  //-----------------------------------------------------------------------
  //! Equality comparision. Relies on the equal() const method of Derived.
  //-----------------------------------------------------------------------
  bool
  operator==(const string<Traits, CharT> &str) const
  {
    return dereference_cast<Derived const>(this).equal(str);
  }  

/*  template<class T>
  bool
  operator==(const T *str) const
  {
    return dereference_cast<Derived const>(this).equal(str);
  }*/
  
  //-----------------------------------------------------------------------
  //! Concatenation using the add operator method. 
  //! Relies on the append() method of Derived.
  //-----------------------------------------------------------------------
  template<class T>
  Derived &
  operator+=(const T &str)
  {
    return dereference_cast<Derived>(this).append(str);
  }

 /* operator std::basic_string<CharT>() const
  {
    return std::basic_string<CharT>
      (dereference_cast<Derived const>(this).begin(),
       dereference_cast<Derived const>(this).end());
  }*/
  
  
/*  operator const CharT *() const
  {
    return dereference_cast<Derived const>(this).get();
  }*/
  
/*  template<template<class, class> class Tmpl, class Other>
  Derived &
  operator+=(const Tmpl<Other, CharT> &str)
  {
    return dereference_cast<Derived>(this).append(str);
  }
  
  template<class T>
  typename boost::enable_if< boost::is_convertible<T, CharT>, Derived & >::type
  operator+=(T const ch)
  {
    return dereference_cast<Derived>(this).append(ch);
  }
*/
  //-----------------------------------------------------------------------
  //! Conversion operator.
  //-----------------------------------------------------------------------
/*  operator bool() const
  {
    return !dereference_cast<Derived const>(this).empty();
  }*/
  
/*  operator CharT const *() const
  {
    typedef CharT const *ret_type;
    return dereference_cast<Derived const>(this).convert(ret_type());
  }
  
  operator CharT *()
  {
    typedef CharT *ret_type;
    return dereference_cast<Derived>(this).convert(ret_type());
  }*/
  
/*  template<class T>
    operator typename boost::enable_if< boost::is_same<T, CharT>, T const * >::type() const
  {
    typedef T const *ret_type;
    
    return dereference_cast<Derived const>(this).convert(ret_type());
  }*/

/*  template<class T>
  operator T *()
  {
    typedef T *ret_type;

    return dereference_cast<Derived>(this).convert(ret_type());
  }*/
  
//  operator CharT *() const
//  {
//    return borg::wrapper_core_access::get(dereference_cast<Derived const>(this));
//    return (CharT *)dereference_cast<Derived const>(this);
//  }
};

//---------------------------------------------------------------------------
//! String adapter class. Models a wrapper of the underlaying character 
//! pointer which mixes in the generic string interface and facade.
//!
//! Used to instantiate temporary objects which hold a pointer to the 
//! underlaying string while emulating this pointers behaviour through
//! overloaded operators (not unlike an iterator).
//!
//! Thus it can be transparently used in the calls to the underlaying API. 
//---------------------------------------------------------------------------
template<class Traits, class CharT>
struct string_t 
    : public wrapper<CharT *>
    , public string_interface< Traits, string_t<Traits, CharT>, CharT >
    , public string_facade< Traits, string_t<Traits, CharT>, CharT >
{
  BORG_STREAMBUF_TYPES(typename Traits)

  typedef CharT value_type;
  typedef wrapper<CharT *> base_type;
  typedef string_impl<Traits, CharT> impl;

  //---------------------------------------------------------------------------
  //! Create unallocated (unlike empty) string. Specifically a null-pointer.
  //---------------------------------------------------------------------------
  string_t()
    : base_type(0)
  {}

  //---------------------------------------------------------------------------
  //! Create from a multibyte string constant.
  //---------------------------------------------------------------------------
/*  string_t(const wchar_type *str)
    : base_type((wchar_type *)str)
  {}*/
  template<class T>
  string_t(const T *str, typename boost::enable_if_c<
                 boost::type_traits::ice_or<
                     boost::is_same<T, CharT>::value,
                     (sizeof(T) == sizeof(CharT)) >::value
                 >::type *const = 0)
    : base_type((CharT *)str)
  {}

  //---------------------------------------------------------------------------
  //! Create from a single-byte string constant.
  //---------------------------------------------------------------------------
/*  template<class T>
  string_t(const T *str, typename boost::enable_if_c<
                             !boost::is_same<T, CharT>::value
                         >::type *const z = 0)
    : base_type(impl::convert((T *)str, (CharT *)0))
  {}*/

  //---------------------------------------------------------------------------
  //! Create from a string instance.
  //---------------------------------------------------------------------------
  template<class Other>
  string_t(const string<Other, CharT> &str)
    : base_type(const_cast<CharT *>(static_cast<const CharT *>(str)))
  {}
};  
    
//---------------------------------------------------------------------------
template<class Traits, class CharT>
class string 
    : public string_interface< Traits, string<Traits, CharT>, CharT >
    , public string_facade< Traits, string<Traits, CharT>, CharT >
{
  friend class wrapper_core_access;
  friend class string_interface< Traits, string<Traits, CharT>, CharT >;
  friend class string_facade< Traits, string<Traits, CharT>, CharT >;
  
public:
  BORG_STREAMBUF_TYPES(typename Traits)
  
  typedef CharT value_type;
  typedef string_t<Traits, CharT> base_type;
  typedef string_impl<Traits, CharT> impl;
  
  string()
    : m_str(), m_free(false)
  {}
  
  template<class A1>
  string(const A1 &a1, typename boost::enable_if<
             boost::type_traits::ice_and< !
                 boost::is_pointer<A1>::value,
                !boost::is_pointer<string_type>::value 
             > 
         >::type const *const d = 0)
    : m_str(impl::create(a1)), m_free(true)
  {}
  
  template<class A1, class A2>
  string(const A1 &a1, const A2 &a2) 
      : m_str(impl::create(a1, a2)), m_free(true)
  {}
  
/*  template<class P>
    string(const P *s, typename boost::enable_if< boost::is_same<P *, string_type> >::type const *const d = 0)
    : m_str(const_cast<P *>(s)), m_free(false)
  {}*/
  
  string(const string_t<Traits, CharT> &str)
    : m_str(const_cast<CharT *>(static_cast<const CharT *>(str))), m_free(false)
  {}
  
  template<class P>
    string(const P *s, typename boost::enable_if<
               boost::type_traits::ice_and<
                   boost::is_arithmetic<P>::value,
                   (sizeof(CharT) != sizeof(P))
               >
           >::type const *const d = 0)
      : m_str(impl::transcode(s)), m_free(true)
  {}
  
  template<class P>
    string(const P *s, typename boost::enable_if<
               boost::type_traits::ice_and<
                   boost::is_arithmetic<P>::value,
                   (sizeof(CharT) == sizeof(P))
               >
           >::type const *const d = 0)
      : m_str((string_type)impl::create(s)), m_free(true)
  {}
  
/*  template<class StringTraits, class Alloc>
  string(const std::basic_string< CharT, StringTraits, Alloc > &s)
    : m_str(s.c_str()), m_free(false)
  {}
  
  string(const string_t<Traits, wchar_type> &s)
    : m_str(s), m_free(false)
  {}
  
  template< template<class, class, class> class String, class StringTraits, class Alloc >
  string(const String<CharT, StringTraits, Alloc> &s)
    : m_str(s), m_free(false)
  {}

  template<class T>
  string(const T *s, typename boost::enable_if_c< !boost::is_same<T, CharT>::value >::type *d = 0)
    : m_str(impl::transcode(s)), m_free(true)
  {}
  
  template<class T>
  string(const string<Traits, T> &s, typename boost::enable_if_c< !boost::is_same<T, CharT>::value >::type *d = 0)
    : m_str((CharT *)impl::transcode((T *)s)), m_free(true)
  {}
  
  string(const CharT *s, const CharT *e)
    : m_str(impl::replicate(s, e))
  {}*/
  
  ~string()
  {
    if(m_free)
      impl::destroy(m_str);
  }

//  operator CharT *() const
  operator string_type() const
  {
    return m_str;
  }
  
/*  operator const_string_type() const
  {
    return *(const const_string_type *)&m_str;
  }*/
  
/*  operator string_type &() 
  {
    return m_str;
  }*/
  
private:
//  operator CharT *() { return m_str; }
  
  const string_type &
  get() const { return m_str; }

  string_type &
  get() { return m_str; }

  void 
  set(CharT *s) { m_str = s; }

  bool
  alloc()
  {
    if(m_free == false)
    {
      m_str = impl::replicate(m_str);
      m_free = true;
      return true;
    }
    return false;
  }
  
  string_type m_str;
  bool        m_free;
};
  
//---------------------------------------------------------------------------
} // namespace borg

//---------------------------------------------------------------------------
namespace boost
{
  
template<class Traits, class Derived, class CharT>
inline
CharT *
begin(borg::string_interface<Traits, Derived, CharT> &s)
{
  return s.begin();
}
  
template<class Traits, class Derived, class CharT>
inline
const CharT *
begin(const borg::string_interface<Traits, Derived, CharT> &s)
{
  return s.begin();
}
  
template<class Traits, class Derived, class CharT>
inline
CharT *
end(borg::string_interface<Traits, Derived, CharT> &s)
{
  return s.end();
}
  
template<class Traits, class Derived, class CharT>
inline
const CharT *
end(const borg::string_interface<Traits, Derived, CharT> &s)
{
  return s.end();
}
  
  
  
}

//---------------------------------------------------------------------------
#endif //ndef BORG_STREAMBUF_HPP
