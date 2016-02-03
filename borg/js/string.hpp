#ifndef BORG_JS_STRING_HPP
#define BORG_JS_STRING_HPP

#include <borg/string.hpp>
#include <borg/js/traits.hpp>
#include <borg/js/context.hpp>

namespace borg {

template<>
struct sequence_impl<JSString *, jschar const *, jschar *, js::traits>
{
  typedef jschar       *      iterator;
  typedef jschar const *const_iterator;

  //------------------------------------------------------------------------
  static jschar       *begin(JSString       *s) { return s->chars; }
  static jschar const *begin(JSString const *s) { return s->chars; }
  
  //------------------------------------------------------------------------
  static jschar       *end  (JSString       *s) { return s->chars + s->length; }
  static jschar const *end  (JSString const *s) { return s->chars + s->length; }
};

//----------------------------------------------------------------------------
template<class CharT>
class string_impl<CharT, js::traits>
{
public:
  BORG_STRING_TYPES(js::traits)
  BORG_PP_USE_TYPE(js::traits, context_type)

  //------------------------------------------------------------------------
  //! Get the string length.
  //------------------------------------------------------------------------
  static length_type
  length(const_string_type s)
  {
//    return js_strlen(s->chars);
    return s->length;
  }

  //------------------------------------------------------------------------
  //! Create new string from UTF16 (jschar *).
  //------------------------------------------------------------------------
  static string_type
  create(const jschar *s, const context_type &ctx =
                script::context_impl<js::traits>::shared(), 
         uintN gcflag = 0)
  {
    return js_NewString(ctx, (jschar *)s, js_strlen(s), gcflag);
  }
  
  //------------------------------------------------------------------------
  //! Create new string from UTF16 (JSString).
  //------------------------------------------------------------------------
  static string_type
  create(const const_string_type &s, const context_type &ctx =
         script::context_impl<js::traits>::shared(),
                  uintN gcflag = 0)
  {
    return js_NewString(ctx, s->chars, s->length, gcflag);
  }
  
  //------------------------------------------------------------------------
  static wchar_type *
  transcode(const char_type *s, borg::size_t n, const context_type &ctx =
         script::context_impl<js::traits>::shared(),
                  uintN gcflag = 0)
  {
    return js_InflateString(ctx, s, n);
  }
  
  //------------------------------------------------------------------------
  static string_type
  append(const string_type &s1, const string_type &s2, const context_type &ctx =
            script::context_impl<js::traits>::shared())
  {
    return JS_ConcatStrings(ctx, s1, s2);
  }
  
  //------------------------------------------------------------------------
  static string_type
  append(const string_type &s1, jschar ch, const context_type &ctx =
            script::context_impl<js::traits>::shared())
  {
    jschar str[2] = { ch, 0 };
    return append(s1, create(str, ctx), ctx);
  }
  
  //------------------------------------------------------------------------
  //! Create new string from ISO-LATIN1 (char).
  //------------------------------------------------------------------------
  static string_type
  transcode(const char *s, const context_type &ctx =
                script::context_impl<js::traits>::shared())
  {
    return JS_NewString(ctx, (char *)s, strlen(s));
  }
  
  //------------------------------------------------------------------------
  static void
  destroy(string_type &s, const context_type &ctx =
                script::context_impl<js::traits>::shared())
  {
    js_FinalizeString(ctx, s);
    s = 0;
  }
  
  //------------------------------------------------------------------------
  static const jschar *
  c_str(const string_type &s)
  {
    return s->chars;
  }

  //------------------------------------------------------------------------
  static bool
  equal(const string_type &s1, const string_type &s2)
  {
    return js_CompareStrings(s1, s2) == 0;
  }  
  
  static bool
  equal(const string_type &s1, const wchar_type *s2)
  {
    JSString str2;
    str2.chars = (wchar_type *)s2;
    str2.length = 0;

    while(*s2++)
      str2.length++;      
    
    return js_CompareStrings(s1, &str2) == 0;
  }  
  
  //------------------------------------------------------------------------
  static bool
  empty(const string_type &s)
  {
    return s->chars == 0 || length(s) == 0;
  }  
};

namespace js {
  
//  typedef ::borg::string_t<xerces::traits, xerces::traits::char_type> string_t;
//  typedef ::borg::string<xerces::traits, xerces::traits::char_type> string;
 
typedef ::borg::string_t<traits::wchar_type, traits> string_t;
typedef ::borg::string<traits::wchar_type, traits> string;

} // namespace js
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_JS_STRING_HPP
