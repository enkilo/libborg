#ifndef BORG_JS_TOKEN_ITERATOR_HPP
#define BORG_JS_TOKEN_ITERATOR_HPP

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
struct token_iterator_impl<js::traits>
{
  BORG_PARSE_TOKEN_ITERATOR_TYPES(js::traits)
  BORG_PP_USE_TYPE(js::traits, wchar_type)
  BORG_PP_USE_TYPE(js::traits, token_id_type)

  static token_iterator_type
  create(context_type const &ctx, const char *file, FILE *fp)
  {
    return js_NewFileTokenStream(ctx, file, fp);
  }

  static token_iterator_type
  create(context_type const &ctx, wchar_type const *base, wchar_type const *limit)
  {
    return js_NewBufferTokenStream(ctx, base, limit - base);
  }
  
  static void
  destroy(context_type const &ctx, token_iterator_type &it)
  {
    js_CloseTokenStream(ctx, it);
  }
  
  static void
  increment(context_type const &ctx, token_iterator_type it)
  {
    js_GetToken(ctx, it);
  }
  
  static token_type &
  dereference(token_iterator_type const &it)
  {
    return CURRENT_TOKEN(it);
  }
  
  static bool
  equal(token_iterator_type const &it1, token_iterator_type const &it2)
  {
    if(it1 == it2) return true;
    if((it1->flags & TSF_EOF) && it2 == 0) return true;
    return false;
  }
};
  
//----------------------------------------------------------------------------
template<>
class token_iterator< js::traits >
    : public token_iterator_interface< js::traits, token_iterator< js::traits > >
    , public token_iterator_facade< js::traits, token_iterator< js::traits > >
{
  BORG_PARSE_TOKEN_ITERATOR_TYPES( js::traits )
  BORG_PP_USE_TYPE( js::traits, wchar_type )

  typedef token_iterator_impl< js::traits > impl;
  
  context_type m_cx;
  token_iterator_type m_it;

public:

  token_iterator(context_t<js::traits> const &ctx, const char *name, FILE *fp)
    : m_cx(ctx)
    , m_it(impl::create(ctx, name, fp))
  {}
  
  token_iterator(context_t<js::traits> const &ctx,
                 wchar_type const *base, wchar_type const *limit)
    : m_cx(ctx)
    , m_it(impl::create(ctx, base, limit))
  {}
  
  token_iterator()
  {}
  
  ~token_iterator()
  {
    impl::destroy(m_cx, m_it);
  }

  token_iterator_type 
  operator->() const { return m_it; }
  operator token_iterator_type() const { return m_it; }
  
  context_type
  get_context() const
  {
    return m_cx;
  }
};  
  
//----------------------------------------------------------------------------

} // namespace parse

namespace js {

//typedef borg::parse::token_iterator_impl<traits> token_iterator_a;
//typedef borg::parse::token_iterator_t<traits> token_iterator_t;
typedef borg::parse::token_iterator<traits> token_iterator;

} // namespace js
} // namespace borg

//----------------------------------------------------------------------------
#endif //ndef BORG_JS_TOKEN_ITERATOR_HPP
