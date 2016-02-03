#ifndef BORG_PARSE_TOKEN_ITERATOR_HPP
#define BORG_PARSE_TOKEN_ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/parse/token.hpp>

#define BORG_PARSE_TOKEN_ITERATOR_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, token_iterator_type) \
    BORG_PP_USE_TYPE(Traits, context_type) \
    BORG_PP_USE_TYPE(Traits, token_type)

//---------------------------------------------------------------------------
namespace borg {
namespace parse {

using script::context_t;

WRAP_PATTERN_FORWARD(token_iterator)
    
//---------------------------------------------------------------------------
//! Generic implementation of token iterators.
//---------------------------------------------------------------------------
template<class Traits>
struct token_iterator_impl
{
  BORG_PARSE_TOKEN_ITERATOR_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, wchar_type)
  
  //-------------------------------------------------------------------
  //! Construct token iterator from bidirectional character iterator 
  //! pair.
  //-------------------------------------------------------------------
  static token_iterator_type
  create(wchar_type const *b, wchar_type const *e)
  {
    return token_iterator_type(b, e);
  }

  //-------------------------------------------------------------------
  //! Advance to next token.
  //-------------------------------------------------------------------
  static void
  increment(token_iterator_type &it)
  {
    ++it;
  }
  
  //-------------------------------------------------------------------
  //! Get current token.
  //-------------------------------------------------------------------
  static token_type &
  dereference(token_iterator_type const &it)
  {
    return *it;
  }  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_iterator_interface
{
  BORG_PARSE_TOKEN_ITERATOR_TYPES(typename Traits)
  
  typedef token_iterator_impl<Traits> impl;

  void
  increment()
  {
    impl::increment(dereference_cast<Derived>(this).get_context(),
                    dereference_cast<Derived>(this));
  }
  
  token<Traits> &
  dereference() const
  {
    return *reinterpret_cast<token<Traits> *>(&impl::dereference(dereference_cast<Derived const>(this)));
  }
  
  bool
  equal(Derived const &atok) const
  {
    return impl::equal(dereference_cast<Derived const>(this), atok);
  }
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_iterator_facade 
    : public boost::iterator_facade<
        Derived,
        token<Traits>,
        boost::forward_traversal_tag
      >
{
  typedef token_iterator_impl<Traits> impl;
  
};

//---------------------------------------------------------------------------
template<class Traits>
class token_iterator
    : public token_iterator_interface< Traits, token_iterator<Traits> >
    , public token_iterator_facade< Traits, token_iterator<Traits> >
{
public:
  BORG_PP_USE_TYPE(typename Traits, token_iterator_type)
  BORG_PP_USE_TYPE(typename Traits, wchar_type)
  BORG_PP_USE_TYPE(typename Traits, context_type)
    
  typedef token_iterator_impl<Traits> impl;

/*  token_iterator(token_iterator_type const &v) 
    : base_type(v) 
  {}*/
  token_iterator(context_type const &ctx, wchar_type const *b, wchar_type const *e)
    : m_iter(impl::create(b, e))
    , m_ctx(ctx)
  {}

  context_type
  get_context() const
  {
    return m_ctx;
  }
  
  operator token_iterator() const
  {
    return m_iter;
  }
  
private:
  token_iterator_type m_iter;
  context_type m_ctx; //!< bound context
};

} // namespace parse
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_PARSE_TOKEN_ITERATOR_HPP
