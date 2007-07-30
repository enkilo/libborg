#ifndef BORG_JS_TOKEN_STREAM_HPP
#define BORG_JS_TOKEN_STREAM_HPP

#include <borg/parse/token_stream.hpp>
#include <borg/parse/token_buf.hpp>
#include <borg/js/context.hpp>
#include <borg/js/string_buffer.hpp>
#include <borg/js/token.hpp>
#include <js/jsscan.h>

namespace borg {
namespace parse {

using borg::script::context_t;
  
//----------------------------------------------------------------------------
template<>
struct token_buf_impl<js::traits>
{
  BORG_PARSE_TOKEN_BUF_TYPES(js::traits)

  wchar_type *
  begin(token_buf_type &tb)
  {
    return tb.base;
  }
  
  wchar_type *
  end(token_buf_type &tb)
  {
    return tb.limit;
  }
  
  wchar_type *
  ptr(token_buf_type &tb)
  {
    return tb.ptr;
  }  
};  

//----------------------------------------------------------------------------
template<>
struct token_stream_impl<js::traits>
{
  BORG_PARSE_TOKEN_STREAM_TYPES(js::traits)

  static token_stream_type
  create(context_type cx, wchar_type const *base, length_type length, 
         const char *filename, length_type lineno)
  {
    return ::js_NewTokenStream(cx, base, length, filename, lineno, 0);
  }
  
  static token_stream_type
  create(context_type cx, wchar_type const *base, length_type length)
  {
    return ::js_NewBufferTokenStream(cx, base, length);
  }
  
  static token_stream_type
  create(context_type cx, wchar_type const *base, wchar_type const *limit)
  {
    return ::js_NewBufferTokenStream(cx, base, limit - base);
  }
  
  static token_stream_type
  create(context_type cx, char const *filename, FILE *defaultfp)
  {
    return ::js_NewFileTokenStream(cx, filename, defaultfp);
  }
  
  static bool_type
  destroy(token_stream_type ts, context_type cx)
  {
    return ::js_CloseTokenStream(cx, ts);
  }

  //-------------------------------------------------------------------
  //! Look ahead one token and return its type.
  //-------------------------------------------------------------------
  static token_id_type
  peek(token_stream_type ts, context_type cx)
  {
    return ::js_PeekToken(cx, ts);
  }
  
  //-------------------------------------------------------------------
  static token_id_type
  peek_token_same_line(token_stream_type ts, context_type cx)
  {
    return ::js_PeekTokenSameLine(cx, ts);
  }
  
  //-------------------------------------------------------------------
  //! Get the next token from ts.
  //-------------------------------------------------------------------
  static token_id_type
  get(token_stream_type ts, context_type cx)
  {
    return ::js_GetToken(cx, ts);
  }
  
  //-------------------------------------------------------------------
  //! Push back the last scanned token onto ts.
  //-------------------------------------------------------------------
  static void
  unget(token_stream_type ts)
  {
    ::js_UngetToken(ts);
  }
  
  //-------------------------------------------------------------------
  //! Get the next token from ts if its type is tt.
  //-------------------------------------------------------------------
  static bool_type
  match(token_stream_type ts, context_type cx, token_id_type tt)
  {
    return ::js_MatchToken(cx, ts, tt);
  }
  
  //-------------------------------------------------------------------
  //! Get the token buffer.
  //-------------------------------------------------------------------
  static string_buffer_type &
  tokenbuf(token_stream_type const ts)
  {
    return ts->tokenbuf;
  }
  
  static token_buf_type &
  linebuf(token_stream_type const ts)
  {
    return ts->linebuf;
  }
  
  static token_buf_type &
  userbuf(token_stream_type const ts)
  {
    return ts->userbuf;
  }
  
  static offset_type
  linelen(token_stream_type const ts)
  {
    return ts->linelen;
  }
  
  static offset_type
  linepos(token_stream_type const ts)
  {
    return ts->linepos;
  }
  
  //-------------------------------------------------------------------
  //! Get the current token.
  //-------------------------------------------------------------------
  static token_type &
  current(token_stream_type ts)
  {
    return CURRENT_TOKEN(ts);
  }
};
  
//----------------------------------------------------------------------------
template<>
class token_stream< js::traits >
    : public token_stream_interface< js::traits, token_stream< js::traits > >
    , public token_stream_facade< js::traits, token_stream< js::traits > >
{
  BORG_PARSE_TOKEN_STREAM_TYPES( js::traits )

  typedef token_stream_impl< js::traits > impl;
  
  context_type m_cx;
  token_stream_type m_ts;

  
/*  token_stream_type const &
  get() const { return m_ts; }
  
  token_stream_type &
  get() { return m_ts; }*/
  
public:

  token_stream(context_t<js::traits> const &ctx, const char *name, FILE *fp)
    : m_cx(ctx)
    , m_ts(impl::create(ctx, name, fp))
  {}
  
  token_stream(context_t<js::traits> const &ctx,
               wchar_type const *base, wchar_type const *limit)
    : m_cx(ctx)
    , m_ts(impl::create(ctx, base, limit))
  {}
  
  ~token_stream()
  {
    impl::destroy(m_ts, m_cx);
  }

  token_stream_type 
  operator->() const { return m_ts; }
  operator token_stream_type() const { return m_ts; }
};  
  
//----------------------------------------------------------------------------

} // namespace parse

namespace js {

typedef borg::parse::token_stream_impl<traits> token_stream_a;
typedef borg::parse::token_stream_t<traits> token_stream_t;
typedef borg::parse::token_stream<traits> token_stream;

inline void
init_scanner(const context_t &cx)
{
  ::js_InitScanner(cx);
}
  
} // namespace js
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_JS_TOKEN_STREAM_HPP
