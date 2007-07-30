#ifndef BORG_PARSE_TOKEN_BUF_HPP
#define BORG_PARSE_TOKEN_BUF_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/script/context.hpp>
#include <borg/parse/token.hpp>
#include <borg/parse/string_buffer.hpp>

#define BORG_PARSE_TOKEN_BUF_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, char_type) \
    BORG_PP_USE_TYPE(Traits, wchar_type) \
    BORG_PP_USE_TYPE(Traits, token_buf_type)

//---------------------------------------------------------------------------
namespace borg {
namespace parse {

WRAP_PATTERN_FORWARD(token_buf)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_buf_i 
     : token_buf_impl<Traits>
{
  BORG_PARSE_TOKEN_BUF_TYPES(typename Traits)
  
  typedef token_buf_impl<Traits> impl;
  
  wchar_type *
  begin()
  {
    return impl::begin(dereference_cast<Derived>(this));
  }
  
  wchar_type *
  end()
  {
    return impl::end(dereference_cast<Derived>(this));
  }
  
  wchar_type *
  ptr()
  {
    return impl::ptr(dereference_cast<Derived>(this));
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_buf_facade
{
  typedef token_buf_impl<Traits> impl;
  
  
};

//---------------------------------------------------------------------------
template<class Traits>
class token_buf_t
//    : public wrapper< typename Traits:: token_buf_type,
//         wrap_traits< typename Traits:: token_buf_type > >

    : public Traits::token_buf_type
    , public token_buf_interface< Traits, token_buf_t<Traits> >
//    , public token_buf_facade< Traits, token_buf_t<Traits> >
{
public:
  typedef typename Traits::token_buf_type token_buf_type;
  typedef typename Traits::token_buf_type base_type;
//  typedef wrapper<token_buf_type> base_type;

  token_buf_t(token_buf_type const &v) 
    : base_type(v) 
  {}

  template<template<class> class Adapter>
  token_buf_t(Adapter<Traits> const &a)
    : base_type(a)
  {}
};

} // namespace parse
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_PARSE_TOKEN_BUF_HPP
