#ifndef BORG_AST_NODE_VARIABLE_HPP
#define BORG_AST_NODE_VARIABLE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/named.hpp>
#include <borg/ast/typed.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_VARIABLE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, attributes_type); \
  BORG_PP_USE_TYPE(Traits, variable_type);
  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(variable)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct variable_interface
    : public typed_interface<Traits, Derived>
    , public named_interface<Traits, Derived>
{
  BORG_AST_VARIABLE_TYPES(typename Traits)
 
  typedef variable_impl<Traits> impl;
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
struct variable_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class variable_t
    : public wrapper<typename Traits::variable_type>
    , public variable_interface< Traits, variable_t<Traits> >
    , public variable_facade< Traits, variable_t<Traits> >
{
public:
  BORG_AST_VARIABLE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::variable_type> base_type;
    
  variable_t(const variable_type &fn) 
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::variable_t<AstTraits> &var)
{
  os << *(const borg::ast::declaration_t<AstTraits> *)&var;
  
  // init & attrs?
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_VARIABLE_HPP
