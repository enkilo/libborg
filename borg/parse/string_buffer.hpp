#ifndef BORG_PARSE_STRING_BUFFER_HPP
#define BORG_PARSE_STRING_BUFFER_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/noncopyable.hpp>

#define BORG_PARSE_STRING_BUFFER_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, token_type) \
    BORG_PP_USE_TYPE(Traits, string_type) \
    BORG_PP_USE_TYPE(Traits, string_buffer_type) \
    BORG_PP_USE_TYPE(Traits, length_type)

//---------------------------------------------------------------------------
namespace borg {
namespace parse {
  
//---------------------------------------------------------------------------
template<class CharT, class Traits>
struct string_buffer_impl;
    
//---------------------------------------------------------------------------
template<class Derived, class CharT, class Traits>
struct string_buffer_interface : string_buffer_impl<CharT, Traits>
{
  BORG_PARSE_STRING_BUFFER_TYPES(typename Traits)
    
  typedef CharT char_type;
  typedef string_buffer_impl<CharT, Traits> impl;

/*  void
  init()
  {
    impl::init(dereference_cast<Derived>(this));
  }

  void
  finish()
  {
    impl::finish(dereference_cast<Derived>(this));
  }*/

  void
  repeat(char_type ch, length_type count)
  {
    impl::repeat(dereference_cast<Derived>(this), ch, count);
  }

  void
  write(const char *s)
  {
    impl::write(dereference_cast<Derived>(this), s);
  }

/*  template<class A1, class A2>
  void
  write(A1 a1, A2 a2)
  {
    impl::write(dereference_cast<Derived>(this), a1, a2);
  }*/

  char_type *
  begin()
  {
    return impl::begin(dereference_cast<Derived>(this));
  }

  char_type *
  end()
  {
    return impl::end(dereference_cast<Derived>(this));
  }

  length_type
  size() const
  {
    return impl::size(dereference_cast<Derived const>(this));
  }
};
    
//---------------------------------------------------------------------------
template<class Derived, class CharT, class Traits>
struct string_buffer_facade
{
  BORG_PARSE_STRING_BUFFER_TYPES(typename Traits)
    
  typedef CharT char_type;
  typedef boost::iostreams::sink_tag category;

  Derived &
  operator+=(const char *asciiz)
  {
    dereference_cast<Derived>(this).append_c_str(asciiz);
    return *this;
  }
  
};
  
//---------------------------------------------------------------------------
template<class CharT, class Traits>
class string_buffer_t 
    : public wrapper< typename Traits::string_buffer_type * >
    , public string_buffer_facade< string_buffer_t<CharT, Traits>, CharT, Traits >
    , public string_buffer_interface< string_buffer_t<CharT, Traits>, CharT, Traits >
{
  BORG_PARSE_STRING_BUFFER_TYPES(typename Traits)

  typedef CharT char_type;
  typedef string_buffer_type *wrapped_type;
  typedef wrapper<string_buffer_type *> base;
    
public:
  string_buffer_t(string_buffer_type *const sb) : base(sb)
  {}
};

//---------------------------------------------------------------------------
template<class CharT, class Traits>
class string_buffer
    : public boost::noncopyable
    , public string_buffer_facade< string_buffer_t<CharT, Traits>, CharT, Traits >
    , public string_buffer_interface< string_buffer_t<CharT, Traits>, CharT, Traits >
{
public:
  BORG_PARSE_STRING_BUFFER_TYPES(typename Traits)
    
//  typedef CharT char_type;
//  typedef boost::iostreams::sink_tag category;

  typedef string_buffer_type wrapped_type;
  typedef string_buffer_impl< CharT, Traits > impl;
  
  string_buffer() 
    : m_buffer()
  { impl::init(&m_buffer); }
  
  ~string_buffer() 
  { impl::finish(&m_buffer); }
  
  operator string_buffer_type *() { return &m_buffer; }
  operator string_buffer_type const *() const { return &m_buffer; }
  
private:
  wrapped_type m_buffer;
/*  wrapped_type &get() { return m_buffer; }
  wrapped_type const &get() const { return m_buffer; }*/
};

//---------------------------------------------------------------------------

} // namespace parse
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_PARSE_STRING_BUFFER_HPP
