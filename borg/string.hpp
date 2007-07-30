#ifndef BORG_STRING_HPP
#define BORG_STRING_HPP

#include <borg/string/traits.hpp>
#include <borg/string/interface.hpp>
#include <boost/operators.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/remove_pointer.hpp>
//#include <boost/type_traits/is_same.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/wrap/preproc.hpp>
#include <borg/string/char_traits.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Forward declare string classes.
//---------------------------------------------------------------------------
template<class CharT, class Traits>
struct string_t;
  
template<class CharT, class Traits>
struct string;
  
//---------------------------------------------------------------------------
//! The string facade implements the standard string operators and other
//! syntactic sugar ontop of the generic string interface.
//---------------------------------------------------------------------------
template<class Derived, class CharT, class Traits>
struct string_facade
    : public boost::equality_comparable< string_facade<Derived, CharT, Traits> >
{
  BORG_STRING_TYPES(typename Traits)

  typedef string_impl<CharT, Traits> impl;

  //-----------------------------------------------------------------------
  //! Equality comparision. Relies on the equal() const method of Derived.
  //-----------------------------------------------------------------------
  bool
  operator==(const CharT *str) const
  {
    return dereference_cast<Derived const>(this).equal(str);
  }  

  template<class T>
  typename boost::enable_if_c< (sizeof(CharT) == sizeof(T)) && !boost::is_same<T, CharT>::value, bool >::type
  operator==(const T *str) const
  {
    return dereference_cast<Derived const>(this).equal(str);
  }  

  bool
  operator==(const string<CharT, Traits> &str) const
  {
    return dereference_cast<Derived const>(this).equal(str);
  }  

  template<class StringT>
  bool
  operator!=(const StringT &str) const
  {
    return !operator==(str);
  }  

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

  template<class T>
  typename boost::enable_if_c< (sizeof(CharT) == sizeof(T)) && !boost::is_same<T, CharT>::value, Derived & >::type
  operator+=(const T *str)
  {
    return dereference_cast<Derived const>(this).append(str);
  }  
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
template<class CharT, class Traits>
struct string_t 
    : public wrapper<CharT *>
    , public string_interface< string_t<CharT, Traits>, CharT, Traits >
    , public string_facade< string_t<CharT, Traits>, CharT, Traits >
{
  BORG_STRING_TYPES(typename Traits)

  typedef CharT value_type;
  typedef wrapper<CharT *> base_type;
  typedef string_impl<CharT, Traits> impl;

  //---------------------------------------------------------------------------
  //! Create unallocated (unlike empty) string. Specifically a null-pointer.
  //---------------------------------------------------------------------------
  string_t()
    : base_type(0)
  {}

  //---------------------------------------------------------------------------
  //! Create from a string constant.
  //---------------------------------------------------------------------------
  template<class T>
  string_t(const T *str, typename boost::enable_if_c<
                 boost::type_traits::ice_or<
                     boost::is_same<CharT, T>::value,
                     (sizeof(T) == sizeof(CharT)) >::value
                 >::type *const = 0)
    : base_type((CharT *)str)
  {}

  //---------------------------------------------------------------------------
  //! Create from a string instance.
  //---------------------------------------------------------------------------
  template<class Other>
  string_t(const string<CharT, Other> &str)
    : base_type(const_cast<CharT *>(static_cast<const CharT *>(str)))
  {}
};  
    
//---------------------------------------------------------------------------
template<class CharT, class Traits>
class string 
    : public string_interface< string<CharT, Traits>, CharT, Traits >
    , public string_facade< string<CharT, Traits>, CharT, Traits >
{
public:
  BORG_STRING_TYPES(typename Traits)
  
  typedef CharT value_type;
  typedef string_interface< string<CharT, Traits>, CharT, Traits > iface;
  typedef string<CharT, Traits> this_type;
  typedef string_impl<CharT, Traits> impl;

  string()
    : m_str(), m_free(false)
  {}
  
  string(string<CharT, Traits> const &s)
    : m_str((string_type)impl::create((const_string_type)s)), m_free(true)
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
  
  string(const string_t<CharT, Traits> &str)
    : m_str(const_cast<CharT *>(static_cast<const CharT *>(str))), m_free(false)
  {}
  
  //-------------------------------------------------------------------------
  //! Create from a pointer to a constant character sequence of a character
  //! type different from this string. 
  //-------------------------------------------------------------------------
  template<class P>
  string(const P *s, typename boost::enable_if
         <
             boost::type_traits::ice_and
             <
                 boost::is_arithmetic< P >::value,
                !boost::type_traits::ice_eq< sizeof(CharT), sizeof(P) >::value
             >
         >::type *const d = 0)
    : m_str(impl::transcode(s))
    , m_free(true)
  {}
  
  //-------------------------------------------------------------------------
  //! Create from a pointer to a constant character sequence of the character
  //! type of this string. 
  //-------------------------------------------------------------------------
  template<class P>
  string(const P *s, typename boost::enable_if
         <
             boost::type_traits::ice_and
             <
                 boost::is_arithmetic<P>::value,
                 boost::type_traits::ice_eq< sizeof(CharT), sizeof(P) >::value
             >
         >::type *const d = 0)
    : m_str((string_type)impl::create(s)), m_free(true)
  {}
  
  ~string()
  {
    if(m_free)
      impl::destroy(m_str);
  }

  operator string_type const &() const { return m_str; }
  operator string_type &() { return m_str; }
  
  template<class T>
  string<CharT, Traits> &
  append(T a)
  {
    alloc();
    
    iface::append(a);
    return *this;
  }

  template<class T>
  string<CharT, Traits> &
  assign(T a)
  {
    if(m_free)
      impl::destroy(m_str);
    
    m_str = a;
    m_free = false;
    return *this;
  }

  template<class T>
  string<CharT, Traits> &
  assign(T a1, T a2)
  {
    if(m_free)
      impl::destroy(m_str);
    
    m_str = impl::create(a1, (a2 - a1));
    m_free = true;
    return *this;
  }

private:
  friend class sequence_impl<string_type, const CharT *, CharT *, Traits>;
  friend class sequence_interface<this_type, string_type, const CharT *, CharT *, Traits>;
  friend class string_interface<this_type, CharT, Traits>;
//  operator CharT *() { return m_str; }
  
  const string_type &
  get() const { return m_str; }

  string_type &
  get() { return m_str; }

  void
  set(string_type const &s) { m_str = s; }

  bool
  alloc()
  {
    if(m_free == false || !(CharT const *)m_str)
    {
      m_str = impl::create(m_str);
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
  
template<class Derived, class CharT, class Traits>
inline
CharT *
begin(borg::string_interface<Derived, CharT, Traits> &s)
{
  return s.begin();
}
  
template<class Derived, class CharT, class Traits>
inline
const CharT *
begin(const borg::string_interface<Derived, CharT, Traits> &s)
{
  return s.begin();
}
  
template<class Derived, class CharT, class Traits>
inline
CharT *
end(borg::string_interface<Derived, CharT, Traits> &s)
{
  return s.end();
}
  
template<class Derived, class CharT, class Traits>
inline
const CharT *
end(const borg::string_interface<Derived, CharT, Traits> &s)
{
  return s.end();
}
  
  
  
}

//---------------------------------------------------------------------------

template<class T, template<class, class> class Tmpl, class Traits, class CharT>
static inline
typename boost::enable_if<
    boost::type_traits::ice_and<
        !boost::is_same< std::char_traits<T>, Traits >::value,
        !boost::is_same< std::char_traits<CharT>, Traits >::value, 
        !boost::is_same< std::basic_string< CharT, Traits >, Tmpl< CharT, Traits> >::value, 
        (sizeof(T) == sizeof(CharT)), 
        boost::is_arithmetic<CharT>::value 
    >,
    std::basic_ostream< T, std::char_traits<T> > 
>::type &
operator<<(std::basic_ostream< T, std::char_traits<T> > &os,
           const Tmpl< CharT, Traits > &str)
{
  BORG_PP_USE_TYPE(typename Traits, string_type)
  BORG_PP_USE_TYPE(typename Traits, const_string_type)
  
 // os << reinterpret_cast<const T *>(static_cast<const CharT *>(static_cast<const_string_type>(str)));
  os << (const T *)(static_cast<const_string_type>(str));
  return os;
}

//---------------------------------------------------------------------------

template<class T, class Derived, class CharT, class Traits>
static inline
typename boost::enable_if<
    boost::type_traits::ice_and<
        (sizeof(T) == sizeof(CharT))
      , boost::is_arithmetic<CharT>::value
      , boost::is_arithmetic<T>::value 
    >
  , borg::string<CharT, Traits>
>::type
operator+(T const *cstr, borg::string_facade<Derived, CharT, Traits> const &str)
{
  borg::string<CharT, Traits> ret((CharT const *)cstr);
  
  ret += static_cast<Derived const &>(str);
  return ret;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_STRING_HPP
