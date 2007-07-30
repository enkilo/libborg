#ifndef BORG_PARSE_TOKEN_STREAM_HPP
#define BORG_PARSE_TOKEN_STREAM_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/script/context.hpp>
#include <borg/parse/token.hpp>
#include <borg/parse/string_buffer.hpp>
#include <borg/parse/token_buf.hpp>

#define BORG_PARSE_TOKEN_STREAM_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, char_type) \
    BORG_PP_USE_TYPE(Traits, wchar_type) \
    BORG_PP_USE_TYPE(Traits, offset_type) \
    typedef Traits::token_type token_type; \
    typedef Traits::token_id_type token_id_type; \
    typedef Traits::position_type position_type; \
    typedef Traits::token_ptr_type token_ptr_type; \
    typedef Traits::token_buf_type token_buf_type; \
    typedef Traits::token_stream_type token_stream_type; \
    typedef Traits::string_type string_type; \
    typedef Traits::string_buffer_type string_buffer_type; \
    BORG_PP_USE_TYPE(Traits, length_type) \
    BORG_PP_USE_TYPE(Traits, bool_type) \
    BORG_PP_USE_TYPE(Traits, context_type)

//---------------------------------------------------------------------------
namespace borg {
namespace parse {

/*using borg::wrap_traits;
using borg::wrapper;
using borg::dereference_cast;*/
using script::context_t;

WRAP_PATTERN_FORWARD(token_stream)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_stream_interface
     : token_stream_impl<Traits>
{
  BORG_PARSE_TOKEN_STREAM_TYPES(typename Traits)
  
  typedef token_stream_impl<Traits> impl;
  typedef typename token<Traits>::type token_id;
  
  token_id
  get(const context_t<Traits> &ctx)
  {
    return (token_id)impl::get(dereference_cast<Derived>(this), ctx);
  }
  
  token<Traits> &
  current()
  {
    return *reinterpret_cast< token<Traits> * >
      (&impl::current(dereference_cast<Derived>(this)));
  }
  
  token_buf_t<Traits> &
  linebuf() 
  {
    return *reinterpret_cast<token_buf_t<Traits> *>
      (&impl::linebuf(dereference_cast<Derived>(this)));
  }
  
  token_buf_t<Traits> &
  userbuf()
  {
    return *reinterpret_cast<token_buf_t<Traits> *>
      (&impl::userbuf(dereference_cast<Derived>(this)));
  }
  
  string_buffer_t<wchar_type, Traits>
  tokenbuf() 
  {
    return &impl::tokenbuf(dereference_cast<Derived>(this));
  }
  
  offset_type
  linelen() const
  {
    return impl::linelen(dereference_cast<Derived const>(this));
  }
  
  offset_type
  linepos() const
  {
    return impl::linepos(dereference_cast<Derived const>(this));
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_stream_facade
{
  typedef token_stream_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits>
class token_stream_t
    : public wrapper< typename Traits:: token_stream_type, 
         wrap_traits< typename Traits:: token_stream_type > >

    , public token_stream_interface< Traits, token_stream_t<Traits> >
//    , public token_stream_facade< Traits, token_stream_t<Traits> >
{
public:
  typedef typename Traits::token_stream_type token_stream_type;
  typedef wrapper<token_stream_type> base_type;

  token_stream_t(token_stream_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  token_stream_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace parse
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_PARSE_TOKEN_STREAM_HPP
