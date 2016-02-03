#ifndef BORG_CHAR_TRAITS_HPP
#define BORG_CHAR_TRAITS_HPP

#include <string>
#include <cstring>
#include <borg/integer_traits.hpp>
#include <boost/integer.hpp>

namespace borg {

using std::size_t;
  
//---------------------------------------------------------------------------
//! Character traits template.
//---------------------------------------------------------------------------
template<class T, class Traits>
struct char_traits : std::char_traits<T>
{
  typedef T char_type;
  typedef typename boost::int_t< integer_traits<T>::const_bits + 1 >::fast int_type;
  typedef std::streamoff off_type;
  typedef std::streampos pos_type;
  typedef mbstate_t state_type;
  
  //-------------------------------------------------------------------
  //! Assign \a c1 to \a c2.
  //-------------------------------------------------------------------  
  static void 
  assign(char_type &c1, const char_type &c2)
  {
    c1 = c2;
  }
  
  //-------------------------------------------------------------------
  //! Compare \a c1 and \a c2 for equality.
  //-------------------------------------------------------------------  
  static bool 
  eq(const char_type &c1, const char_type &c2)
  {
    return c1 == c2;
  }
  
  //-------------------------------------------------------------------
  //! Check whether \a c1 is less than \a c2.
  //-------------------------------------------------------------------  
  static bool
  lt(const char_type &c1, const char_type &c2)
  {
    return c1 < c2;
  }
  
  //-------------------------------------------------------------------
  //! Compare \a n characters of sequence \a c1 against \a those of c2.
  //-------------------------------------------------------------------  
  static int
  compare(const char_type *s1, const char_type *s2, size_t n)
  {
    return std::strcmp(s1, s2);
  }
  
  //-------------------------------------------------------------------
  //! Determine the length of the character sequence \a s.
  //-------------------------------------------------------------------  
  static size_t
  length(const char_type* s)
  {
    return std::strlen(s);
  }
  
  //-------------------------------------------------------------------
  //! Find the character \a a within the first \a n bytes of the
  //! character sequence \a s.
  //-------------------------------------------------------------------  
  static const char_type * 
  find(const char_type *s, size_t n, const char_type &a)
  {
    return std::memchr(s, a, n);
  }
  
  //-------------------------------------------------------------------
  //! Copy \a n characters from character sequence \a s2 to \a s1. 
  //! The sequences may overlap.
  //-------------------------------------------------------------------  
  static char_type *
  move(char_type *s1, const char_type *s2, size_t n)
  {
    return std::memmove(s1, s2, n);
  }
  
  //-------------------------------------------------------------------
  //! Copy \a n characters from character sequence \a s2 to \a s1. 
  //! The sequences must not overlap.
  //-------------------------------------------------------------------  
  static char_type *
  copy(char_type *s1, const char_type *s2, size_t n)
  {
    return std::memcpy(s1, s2, n);
  }
  
  //-------------------------------------------------------------------
  //! Assign character \a a to the first \a n characters in character
  //! sequence \a s.
  //-------------------------------------------------------------------  
  static char_type *
  assign(char_type *s, size_t n, char_type a)
  {
    return std::memset(s, a, n);
  }
  
  //-------------------------------------------------------------------
  //! Test whether character \a c is the EOF indicator.
  //-------------------------------------------------------------------  
  static int_type 
  not_eof(const int_type &c)
  {
    return c != integer_traits<int_type>::const_max;
  }
  
  //-------------------------------------------------------------------
  //! Convert integer argument to character.
  //-------------------------------------------------------------------  
  static char_type 
  to_char_type(const int_type &c)
  {
    return char_type(c);
  }
  
  //-------------------------------------------------------------------
  //! Convert character argument to integer.
  //-------------------------------------------------------------------  
  static int_type 
  to_int_type(const char_type &c)
  {
    return int_type(c);
  }
  
  //-------------------------------------------------------------------
  //! Compare two integers.
  //-------------------------------------------------------------------  
  static bool
  eq_int_type(const int_type &c1, const int_type &c2)
  {
    return c1 == c2;
  }

  //-------------------------------------------------------------------
  //! Return the integer value which is used to indicate EOF.
  //-------------------------------------------------------------------
  static int_type 
  eof()
  {
    return integer_traits<int_type>::const_max 
         - integer_traits<int_type>::const_min;
  }
};

//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_CHAR_TRAITS_HPP
