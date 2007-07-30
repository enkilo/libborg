#ifndef BORG_AST_TYPEDEF_HPP
#define BORG_AST_TYPEDEF_HPP

#include <borg/ast/declaration.hpp>

namespace borg {
namespace ast {

BORG_AST_FORWARD(typedef)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct typedef_interface
    : public function_interface<Traits, Derived>
{  
  BORG_AST_TYPED_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, sequence_type)
 
  typedef typedef_impl<Traits> impl;
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct typedef_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class typedef_t
    : public wrapper<typename Traits::function_type>
    , public typedef_interface< Traits, typedef_t<Traits> >
    , public typedef_facade< Traits, typedef_t<Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::function_type> base_type;
    
  typedef_t(const function_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::typedef_t<AstTraits> &fn)
{
  os << "typedef " << *(const borg::ast::declaration_t<AstTraits> *)&fn;
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_TYPEDEF_HPP
