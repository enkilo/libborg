#ifndef BORG_LIBXML2_STRING_HPP
#define BORG_LIBXML2_STRING_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/lib/forward.hpp>
#include <borg/xml/lib/types.hpp>
#include <borg/wrap/wrapper.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class ConstIterator, class Iterator>
class sequence_impl<libxml2::traits::string_type, ConstIterator, Iterator, libxml2::traits>
{
public:
  BORG_STRING_TYPES(libxml2::traits)
    
  //------------------------------------------------------------------------
  //! \name Get the string beginning.
  //------------------------------------------------------------------------
  //@{
  static ConstIterator begin(wchar_type const *s) { return ConstIterator(&s[0]); }
  static      Iterator begin(wchar_type       *s) { return      Iterator(&s[0]); }
  //@}

  //------------------------------------------------------------------------
  //! \name Get the string end.
  //------------------------------------------------------------------------
  //@{
  static ConstIterator end(wchar_type const *s)   { return ConstIterator(&s[xmlStrlen((string_type)s)]); }
  static Iterator      end(wchar_type       *s)   { return      Iterator(&s[xmlStrlen((string_type)s)]); }
  //@}
};
  
//----------------------------------------------------------------------------
template<class CharT>
class string_impl<CharT, libxml2::traits>
{
public:
  BORG_STRING_TYPES(libxml2::traits)
    
  //------------------------------------------------------------------------
  //! Get the string length.
  //------------------------------------------------------------------------
  static length_type
  length(const CharT *s)
  {
    return xmlStrlen(reinterpret_cast<const wchar_type *>(s));
  }

  //------------------------------------------------------------------------
  //! Convert pointer values between typed which have same size.
  //------------------------------------------------------------------------
  template<class InT, class OutT>
  static typename boost::enable_if_c<
      !boost::is_same<InT, OutT>::value && (sizeof(InT) == sizeof(OutT)),
      OutT *
  >::type
  convert(const InT *str, const OutT *t = 0)
  {
    return const_cast<OutT *>(reinterpret_cast<const OutT *>(str));
  }
  
  //------------------------------------------------------------------------
  static wchar_type *
  convert(const const_string_type &str)
  {
    return const_cast<string_type>(str);
  }
  
  //------------------------------------------------------------------------
  static wchar_type *
  transcode(const char *s)
  {
    int inlen = strlen(s);
    int len = 2 * inlen + 1;
    wchar_type *out = (wchar_type *)xmlMalloc(len);
    int outlen = len;
    
//    std::cerr << "xmlMalloc(" << (inlen + 1) << ") = " << (void *)out << std::endl;
    
    isolat1ToUTF8(out, &outlen, (wchar_type *)s, &inlen);

    int remain = len - outlen - 1;
    if(remain > 0 && remain < len) out[remain] = '\0';
    return out;
//    return (wchar_type *)s;
  }
  
  static char *
  transcode(const wchar_type *s)
  {
    int inlen = xmlStrlen(s);
    int len = 1 * inlen + 1;
    char *out = (char *)xmlMalloc(len);
    int outlen = len;
    
//    std::cerr << "xmlMalloc(" << (inlen + 1) << ") = " << (void *)out << std::endl;
    
    UTF8Toisolat1((wchar_type *)out, &outlen, (const wchar_type *)s, &inlen);

    int remain = len - outlen - 1;
    if(remain > 0 && remain < len) out[remain] = '\0';
    return out;
  }

  //------------------------------------------------------------------------
/*  static char *
  transcode(const wchar_type *in, char *out, unsigned int n)
  {
    return out;
  }
  
  static wchar_type *
  transcode(const char *in, wchar_type *out, unsigned int n)
  {
    return out;
  }*/
 
  //-------------------------------------------------------------------------
  static int
  compare(const wchar_type *str1, const wchar_type *str2)
  {
    return xmlStrcmp(str1, str2);
  }
 
  //-------------------------------------------------------------------------
  static int
  equal(const wchar_type *str1, const wchar_type *str2)
  {
//    std::cout << "StrEqual(" << str1 << ", " << str2 << ") = " << xmlStrEqual(str1, str2) << std::endl;    
    return xmlStrEqual(str1, str2);
  }
  
  //-------------------------------------------------------------------------
  static CharT *
  append(CharT *cur, const CharT *add)
  {
    return (wchar_type *)
      xmlStrcat((wchar_type *)cur, (const wchar_type *)add);
  }
  
  //-------------------------------------------------------------------------
  template<class T>
  static CharT *
  append(T *&cur, CharT add)
  {
    CharT ch[2] = { add, 0 };
    
//    std::cout << "cur: " << (void *)cur << std::endl;
    
    if(cur == 0)
      reinterpret_cast<CharT *&>(cur) = (CharT *)xmlStrdup((const wchar_type *)ch);
    else
      reinterpret_cast<CharT *&>(cur) = (CharT *)xmlStrcat((wchar_type *)cur, (const wchar_type *)ch);

    return (CharT *)cur;
  }
  
  //-------------------------------------------------------------------------
  static const CharT *
  c_str(const void *s)
  {
    return (CharT *)s;
  }
  
  //-------------------------------------------------------------------------
  static bool
  empty(const void *s)
  {
    if(s == 0)
      return true;
    
    return ((CharT *)s)[0] == CharT();
  }
  
  //-------------------------------------------------------------------------
  template<class T>
  static void
  destroy(T *&s)
  {
    xmlFree((void *)s);
    s = 0;
  }

  template<class T>
  static CharT *
  create(const T *s)
  {
    return (CharT *)xmlStrdup((const xmlChar *)s);
  }  
  
  template<class T>
  static CharT *
  create(const T *s, unsigned int n)
  {
    return (CharT *)xmlStrndup((const xmlChar *)s, n);
  }  
  
};
  
namespace libxml2 {
  
typedef ::borg::string_t<traits::wchar_type, traits> string_t;
typedef ::borg::string<traits::wchar_type, traits> string;
  
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_STRING_HPP
