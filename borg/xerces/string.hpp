#ifndef BORG_XERCES_STRING_HPP
#define BORG_XERCES_STRING_HPP

#include <borg/string.hpp>
#include <borg/xerces/traits.hpp>
#include <borg/xerces/allocator.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class CharT>
class sequence_impl<CharT *, CharT const *, CharT *, xerces::traits>
{
public:
  //! Get the string beginning.
  //------------------------------------------------------------------------
  template<typename StringT>
  static CharT *
  begin(const StringT &s)
  { 
    return (CharT *)&s[0]; 
  }

  //! Get the string end.
  //------------------------------------------------------------------------
  template<typename StringT>
  static CharT *
  end(const StringT &s)
  { 
    return (CharT *)&s[::XERCES_CPP_NAMESPACE::XMLString::stringLen(s)]; 
  }
};
  
//----------------------------------------------------------------------------
template<class CharT>
class string_impl<CharT, xerces::traits>
{
public:
  BORG_STRING_TYPES(xerces::traits)
    
  //! Get the string length.
  //------------------------------------------------------------------------
  template<typename StringT>
  static length_type
  length(const StringT &s)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::stringLen(s);
  }
  
  //! Transcode (BEWARE: Allocates string, must be free'd using ::release())
  //------------------------------------------------------------------------
  template<class T>
  static typename boost::enable_if_c< !boost::is_same<T, CharT>::value, CharT * >::type
  transcode(const T *in)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::transcode(in);
  }

/*  static wchar_type *
  transcode(const char_type *in)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::transcode(in);
  }*/
  
  static char_type *
  transcode(const wchar_type *in, char_type *out, unsigned int n)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::transcode(in, out, n) ? out : 0;
  }
  
  static wchar_type *
  transcode(const char_type *in, wchar_type *out, unsigned int n)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::transcode(in, out, n) ? out : 0;
  }
  
  //! Convert to pointer.
  //------------------------------------------------------------------------
  template<class Target>
  static typename boost::enable_if<
      boost::type_traits::ice_and<
          boost::is_pointer<Target>::value,
          !boost::is_same< typename boost::remove_const<Target>::type, wchar_type >::value
      >, 
      Target 
  >::type
  convert(const wchar_type *in, Target *t = 0)
  {
    return (Target)(in);
  }
  
  //! Replicate.
  //------------------------------------------------------------------------
  template<class T>
  static T *
  create(T const *in)
  {
    return ::XERCES_CPP_NAMESPACE::XMLString::replicate(in);
  }
  
  //------------------------------------------------------------------------
  static CharT *
  append(CharT *s1, CharT const *s2)
  { 
    using namespace ::XERCES_CPP_NAMESPACE;
    
    XMLSize_t n = XMLString::stringLen(s1) + XMLString::stringLen(s2);
    
    CharT *r = allocator<CharT, xerces::traits>::singleton().allocate(n + 1);
    
    XMLString::copyString(r, s1);
    XMLString::catString(r, s2);
    
    allocator<CharT, xerces::traits>::singleton().deallocate(s1);
    
    return r;
  }

  //------------------------------------------------------------------------
  static CharT *
  append(CharT *s1, CharT s2)
  { 
    CharT add[2] = { s2, 0 };    
    return append(s1, add);
  }

  //------------------------------------------------------------------------
  template<typename StringT>
  static const CharT *
  c_str(const StringT &s)
  { 
    return s;
  }

  static bool
  empty(const string_type &s)
  {
    if(s == 0)
      return true;
    
    return s[0] == '\0';
  }

  static bool
  equal(const CharT *s1, const CharT *s2)
  { 
    return ::XERCES_CPP_NAMESPACE::XMLString::equals(s1, s2);
  }

  template<class CharT1, class CharT2>
  static typename boost::enable_if_c< sizeof(CharT1) == sizeof(CharT2), bool >::type
  equal(const CharT1 *s1, const CharT2 *s2)
  { 
    return ::XERCES_CPP_NAMESPACE::XMLString::equals(s1, s2);
  }

  template<typename StringT>
  static bool
  equal(const StringT &s1, const StringT &s2)
  { 
    return ::XERCES_CPP_NAMESPACE::XMLString::equals(s1, s2);
  }

  //------------------------------------------------------------------------
  static void
  destroy(wchar_type *&str)
  {
    ::XERCES_CPP_NAMESPACE::XMLString::release(&str);
  }
  
  static void
  destroy(char_type *&str)
  {
    ::XERCES_CPP_NAMESPACE::XMLString::release(&str);
  }
  
      
/*  template<typename StringT>
  static char_type *
  end(StringT &s)
  { 
    return &s[::XERCES_CPP_NAMESPACE::XMLString::stringLen(s)]; 
  }*/
};

namespace xerces {
  
/*typedef ::borg::string_t<traits::char_type, traits> string_t;
typedef ::borg::string<traits::char_type, traits> string;*/
  
typedef ::borg::string_t<xerces::traits::wchar_type, traits> string_t;
typedef ::borg::string<xerces::traits::wchar_type, traits> string;

/*typedef std::basic_string
<
    traits::wchar_type
  , std::char_traits<traits::wchar_type>
  , borg::allocator<traits::wchar_type, traits>
> string;*/

} // namespace xerces
} // namespace borg


//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_STRING_HPP
