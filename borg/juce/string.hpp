#ifndef BORG_JUCE_STRING_HPP
#define BORG_JUCE_STRING_HPP

#include <borg/string.hpp>
#include <borg/juce/traits.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/ice.hpp>
#include <boost/type_traits/is_arithmetic.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<>
class sequence_impl<
#if JUCE_STRINGS_ARE_UNICODE
      juce::traits::string_type,
      juce::traits::wchar_type const *,
      juce::traits::wchar_type *
#else
      juce::traits::string_type,
      juce::traits::char_type const *,
      juce::traits::char_type *
#endif
      , juce::traits
      >
{
public:
  BORG_STRING_TYPES(juce::traits)

#if JUCE_STRINGS_ARE_UNICODE
  typedef juce::traits::wchar_type juce_char_t;
#else
  typedef juce::traits::char_type juce_char_t;
#endif

  //------------------------------------------------------------------------
  //! Get iterator to the beginning of the string.
  //------------------------------------------------------------------------
  static juce_char_t *
  begin(const string_type &s)
  {
    return const_cast<juce_char_t *>(static_cast<const juce_char_t *>(s));
  }
  
  //------------------------------------------------------------------------
  //! Get iterator to the end of the string.
  //------------------------------------------------------------------------
  static juce_char_t *
  end(const string_type &s)
  {
    return const_cast<juce_char_t *>
      (static_cast<const juce_char_t *>(s)) + s.length();
  }
};
  
//----------------------------------------------------------------------------
template<>
class string_impl<
#if JUCE_STRINGS_ARE_UNICODE
      juce::traits::wchar_type
#else
      juce::traits::char_type
#endif
      , juce::traits
      >
{
public:
  BORG_STRING_TYPES(juce::traits)
    
#if JUCE_STRINGS_ARE_UNICODE
  typedef juce::traits::wchar_type juce_char_t;
#else
  typedef juce::traits::char_type juce_char_t;
#endif

  //------------------------------------------------------------------------
  //! Construct string object from various types.
  //------------------------------------------------------------------------
  template<class S>
  static string_type 
  create(const S &str)
  {
    return string_type(str);
//    return *(new string_type(str));    
  }
    
  template<class S, class N>
  static typename boost::enable_if< boost::is_arithmetic<N>, string_type & >::type
  create(const S &str, N n)
  {
    return *(new string_type(str, n));
  }
    
  template<class P1, class P2>
  static typename boost::enable_if< 
    boost::type_traits::ice_and< boost::is_pointer<P1>::value,
    boost::is_pointer<P2>::value >, 
    string_type & 
  >::type
  create(const P1 &begin, const P2 &end)
  {
    return *(new string_type(begin, end - begin));
  }
    
  //------------------------------------------------------------------------
  //! Make a copy of the string object.
  //------------------------------------------------------------------------
  static string_type &
  replicate(const string_type &str)
  {
    return *(new string_type(str));
  }
    
  //------------------------------------------------------------------------
  //! Construct from single-byte string (possibly transcoding inbetween).
  //------------------------------------------------------------------------
#if JUCE_STRINGS_ARE_UNICODE
  static string_type 
  transcode(const char_type *str)
  {
    return string_type(str);
  }
#else
  template<class T>
  static typename boost::enable_if<
             boost::type_traits::ice_not< sizeof(T) == 1 >, 
             string_type 
         >::type
  transcode(const T *str)
  {
    return string_type(reinterpret_cast<const wchar_type *>(str));
  }
#endif
  
  //------------------------------------------------------------------------
  //! Destroy string object.
  //------------------------------------------------------------------------
  static void
  destroy(string_type &str)
  {
/*    string_type *ptr = &str;
    delete ptr;
    str = 0;*/
  }
  
  //------------------------------------------------------------------------
  //! Compare two strings.
  //------------------------------------------------------------------------
  static int
  compare(const string_type &str1, const string_type &str2)
  {
    return (str1 == str2);
  }
  
  //------------------------------------------------------------------------
  //! Convert string to character pointer.
  //------------------------------------------------------------------------
  template<class CharT>
  static CharT *
  convert(const string_type &str, const CharT *dummy = 0)
  {
    return const_cast<CharT *>(static_cast<const CharT *>(str));
  }
  
  //------------------------------------------------------------------------
  //! Get the string length.
  //------------------------------------------------------------------------
  static length_type
  length(const string_type &s)
  {
    return s.length();
  }
  
  //------------------------------------------------------------------------
  //! Get null-terminated C string.
  //------------------------------------------------------------------------
  static const juce_char_t *
  c_str(const string_type &s)
  {
    return static_cast<const juce_char_t *>(s);
  }
  
  //------------------------------------------------------------------------
  static bool
  empty(const string_type &s)
  {
    return s.length() == 0;
  }
  
  //------------------------------------------------------------------------
  static bool
  equal(const string_type &s1, const string_type &s2)
  {
    return s1 == s2;
  }
  
  //------------------------------------------------------------------------
  //! Append something to the string.
  //------------------------------------------------------------------------
  static string_type &
  append(string_type &s, juce_char_t const ch)
  {
    s += ch;
    return s;
  }

  static string_type &
  append(string_type &s, const string_type &a)
  {
    s += a;
    return s;
  }

  template<class T>
  static string_type &
  append(string_type &s, const T *a)
  {
    s += a;
    return s;
  }
  
};
  
//----------------------------------------------------------------------------
namespace juce {

#if JUCE_STRINGS_ARE_UNICODE
typedef ::borg::string_t<traits::wchar_type, traits> string_t;
typedef ::borg::string<traits::wchar_type, traits> string;
#else
typedef ::borg::string_t<traits::char_type, traits> string_t;
typedef ::borg::string<traits::char_type, traits> string;
#endif
  
} // namespace juce
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_JUCE_STRING_HPP
