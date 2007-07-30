#ifndef BORG_AST_FILE_HPP
#define BORG_AST_FILE_HPP

#include <borg/ast/named.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(file)

//---------------------------------------------------------------------------
#define BORG_AST_FILE_TYPES(Traits) \
    BORG_AST_NODE_TYPES(Traits) \
    BORG_PP_USE_TYPE(Traits, file_type)
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct file_interface
    : public named_interface<Traits, Derived>
{  
  BORG_AST_FILE_TYPES(typename Traits)
 
  typedef named_impl<Traits> impl;
  typedef typename Traits::id_type id_type;
  
/*  string_type
  name() const
  {
    return impl::get_name(dereference_cast<Derived const>(this));
  }*/
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct file_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class file_t
    : public wrapper<typename Traits::file_type>
    , public file_interface< Traits, file_t<Traits> >
    , public file_facade< Traits, file_t<Traits> >
{
public:
  BORG_AST_FILE_TYPES(typename Traits)

  typedef wrapper<file_type> base_type;
    
  file_t(const file_type &fn) 
    : base_type(fn)
  {
    if(unwrap_cast(*this) == 0)
      throw exception<Traits>("null file!");
  }
};
  
  
//---------------------------------------------------------------------------
/*template<class Traits>
class file
{
};*/
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::file_t<AstTraits> &file)
{
  os << file.name();

  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_FILE_HPP
