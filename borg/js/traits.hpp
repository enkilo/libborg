#ifndef JS_TRAITS_HPP
#define JS_TRAITS_HPP

#include <js/jsapi.h>
#include <js/jsscan.h>
#include <cstdlib>

namespace borg {
namespace js {

BOOST_STATIC_CONSTANT(std::size_t, default_runtime_size = 4 * 1024 * 1024);
BOOST_STATIC_CONSTANT(std::size_t, default_stack_size = 8192);
  
//----------------------------------------------------------------------------
struct traits
{
  typedef char              char_type;
  typedef ::jschar          wchar_type;
  typedef ::JSString const *const_string_type;
  typedef ::JSString       *string_type;
  typedef ::JSTokenType     token_id_type;
  typedef ::JSTokenPos      position_type;
  typedef ::JSTokenPtr      token_ptr_type;
  typedef ::JSTokenBuf      token_buf_type;
  typedef ::JSTokenStream  *token_stream_type;
  typedef ::JSTokenStream  *token_iterator_type;
  typedef ::JSToken         token_type;
  typedef ::intN            index_type;
  typedef ::uintN           length_type;
  typedef ::ptrdiff_t       offset_type;
  typedef ::JSStringBuffer  string_buffer_type;
  typedef ::JSContext      *context_type;
  typedef ::JSRuntime      *runtime_type;
  typedef ::JSBool          bool_type;
  typedef ::size_t          size_type;
};

//---------------------------------------------------------------------------

} // namespace js
} // namespace borg
  
#endif //ndef JS_TRAITS_HPP
