#ifndef BORG_AST_NODE_DECLARATION_HPP
#define BORG_AST_NODE_DECLARATION_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/named.hpp>
#include <borg/ast/typed.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_DECLARATION_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, attributes_type); \
  BORG_PP_USE_TYPE(Traits, declaration_type);
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(declaration)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct declaration_interface
    : public typed_interface<Traits, Derived>
    , public named_interface<Traits, Derived>
{
  BORG_AST_DECLARATION_TYPES(typename Traits)
 
  typedef declaration_impl<Traits> impl;
/*    
  string_type
  name() const
  {
    return impl::get_name
      (dereference_cast<Derived const>(this));
  }
*/
  bool
  is_extern() const
  {
    return impl::is_extern
      (dereference_cast<Derived const>(this));
  }  
    
  attributes_type
  attributes() const
  {
    return impl::get_attributes
      (dereference_cast<Derived const>(this));
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct declaration_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class declaration_t
    : public wrapper<typename Traits::declaration_type>
    , public declaration_interface< Traits, declaration_t<Traits> >
    , public declaration_facade< Traits, declaration_t<Traits> >
{
public:
  BORG_AST_DECLARATION_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::declaration_type> base_type;
    
  declaration_t(const declaration_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::declaration_t<AstTraits> &decl)
{
  BORG_AST_DECLARATION_TYPES(typename AstTraits)
  
  if(decl.is_extern())
    os << "extern ";

  if(decl.type())
    os << decl.type();
  
  if(decl.name())
  {
    string_type name = decl.name();
    
    if(name != "")
      os << ' ' << name;
  }
  
  os << ';';  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_DECLARATION_HPP
