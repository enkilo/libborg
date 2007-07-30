#ifndef BORG_AST_OPERATOR_FUNCTION_HPP
#define BORG_AST_OPERATOR_FUNCTION_HPP

#include <borg/ast/function.hpp>

namespace borg {
namespace ast {

BORG_AST_FORWARD(operator_function)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct operator_function_interface
    : public function_interface<Traits, Derived>
{  
  BORG_AST_TYPED_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, sequence_type)
 
  typedef operator_function_impl<Traits> impl;
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct operator_function_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class operator_function_t
    : public wrapper<typename Traits::function_type>
    , public operator_function_interface< Traits, operator_function_t<Traits> >
    , public operator_function_facade< Traits, operator_function_t<Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::function_type> base_type;
    
  operator_function_t(const function_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::operator_function_t<AstTraits> &fn)
{
  os << *(const borg::ast::basic_function_t<AstTraits> *)&fn;
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_OPERATOR_FUNCTION_HPP
