#ifndef BORG_JS_STRING_BUFFER_HPP
#define BORG_JS_STRING_BUFFER_HPP

#include <borg/parse/string_buffer.hpp>
#include <borg/js/traits.hpp>
#include <js/jsscan.h>

namespace borg {
namespace parse {

using borg::script::context_t;
  
//----------------------------------------------------------------------------
template<>
struct string_buffer_impl<js::traits::wchar_type, js::traits>
{
  BORG_PARSE_STRING_BUFFER_TYPES(js::traits)

  typedef js::traits::wchar_type char_type;
    
  static void
  init(string_buffer_type *sb)
  {
    ::js_InitStringBuffer(sb);
  }
  
  static void
  finish(string_buffer_type *sb)
  {
    ::js_FinishStringBuffer(sb);
  }
  
  static void
  repeat(string_buffer_type *sb, char_type const c, length_type n)
  {
    ::js_RepeatChar(sb, c, n);
  }
 
  static void
  write(string_buffer_type *sb, char_type const c)
  {
    ::js_AppendChar(sb, c);
  }
  
  static void
  write(string_buffer_type *sb, const char *asciiz)
  {
    ::js_AppendCString(sb, asciiz);
  }
 
  static void
  write(string_buffer_type *sb, string_type str)
  {
    ::js_AppendJSString(sb, str);
  } 
  
  static char_type *
  begin(string_buffer_type *sb)
  {
    return STRING_BUFFER_OK(sb) ? sb->base : 0;
  }
  
  static char_type *
  end(string_buffer_type *sb)
  {
    return STRING_BUFFER_OK(sb) ? sb->ptr : 0;
  }  
  
  static length_type
  size(string_buffer_type const *sb)
  {
    return STRING_BUFFER_OFFSET(sb);
  }  
};
  
//----------------------------------------------------------------------------

} // namespace parse

namespace js {

typedef borg::parse::string_buffer_t<traits::wchar_type, traits> string_buffer_t;
typedef borg::parse::string_buffer<traits::wchar_type, traits> string_buffer;

} // namespace js
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_JS_STRING_BUFFER_HPP
