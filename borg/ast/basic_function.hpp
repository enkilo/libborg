#ifndef BORG_AST_BASIC_FUNCTION_HPP
#define BORG_AST_BASIC_FUNCTION_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/declaration.hpp>
#include <borg/ast/named.hpp>
#include <borg/ast/node_cast.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(basic_function)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct basic_function_interface
    : public declaration_interface<Traits, Derived>
{  
  BORG_AST_TYPED_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, sequence_type)
 
  typedef basic_function_impl<Traits> impl;
  
  basic_type_t<Traits>
  type() const
  {
    return impl::get_type
      (dereference_cast<Derived const>(this));      
  }
  
  sequence_type
  arguments() const
  {
    return impl::get_arguments
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_operator() const
  {
    return impl::is_operator
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_method() const
  {
    return impl::is_method
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_constructor() const
  {
    return impl::is_constructor
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_destructor() const
  {
    return impl::is_destructor
      (dereference_cast<Derived const>(this));
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct basic_function_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class basic_function_t
    : public wrapper<typename Traits::function_type>
    , public basic_function_interface< Traits, basic_function_t<Traits> >
    , public basic_function_facade< Traits, basic_function_t<Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::function_type> base_type;
    
  basic_function_t(const function_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::basic_function_t<AstTraits> &fn)
{
  using namespace borg::ast;
  
  if(fn.is_extern())
        os << "extern ";
  
  if(!fn.is_constructor() && !fn.is_destructor())
    os << fn.type() << ' ';
  
  if(fn.is_operator())
    os << "operator";
  
  else if(fn.is_destructor())
    os << '~';
  
  if(node_cast<node_t>(fn).is_named())
    os << fn.name();
  
  os << "();";
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_BASIC_FUNCTION_HPP
