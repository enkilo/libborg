#ifndef BORG_PARSE_TOKEN_HPP
#define BORG_PARSE_TOKEN_HPP

#include <borg/wrap/preproc.hpp>

//---------------------------------------------------------------------------
#define BORG_PARSE_TOKEN_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, char_type) \
    BORG_PP_USE_TYPE(Traits, wchar_type) \
    BORG_PP_USE_TYPE(Traits, length_type) \
    typedef Traits::token_type token_type; \
    typedef Traits::token_id_type token_id_type; \
    typedef Traits::position_type position_type;

//---------------------------------------------------------------------------
namespace borg {
namespace parse {

WRAP_PATTERN_FORWARD(token)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct token_interface : token_impl<Traits>
{
  BORG_PARSE_TOKEN_TYPES(typename Traits)
  
  typedef token_impl<Traits> impl;
  
  std::string
  get_value() const
  {
    return impl::get_value(dereference_cast<Derived const>(this));
  }
  
  typename impl::type
  get_id() const
  {
    return (typename impl::type)impl::get_id(dereference_cast<Derived const>(this));
  }
  
  void
  print(std::ostream &os) const
  {
    std::string value = get_value();
    
    os << get_token_name(get_id()) << "(";
    
    for(std::size_t i = 0; i < value.size(); ++i)
    {
      switch(value[i])
      {
        case '\r': os << "\\r"; break;
        case '\n': os << "\\n"; break;
        default: os << value[i]; break;
      }
    }
    
    os << ")";
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class token : public Traits::token_type
            , public token_interface< Traits, token<Traits> >
{
public:
};
  
    
} // namespace parse
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_PARSE_TOKEN_HPP
