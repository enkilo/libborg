#ifndef BORG_AST_FUNCTION_HPP
#define BORG_AST_FUNCTION_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/basic_function.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(function)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct function_interface
    : public basic_function_interface<Traits, Derived>
{  
  BORG_AST_TYPED_TYPES(typename Traits)
  BORG_PP_USE_TYPE(typename Traits, sequence_type)
 
  typedef function_impl<Traits> impl;
  
  basic_type_t<Traits>
  return_type() const
  {
    return impl::get_return_type
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
  
  static bool
  is_constructor()
  {
    return false;
  }
  
  static bool
  is_destructor() 
  {
    return false;
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct function_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class function_t
    : public wrapper<typename Traits::function_type>
    , public function_interface< Traits, function_t<Traits> >
    , public function_facade< Traits, function_t<Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::function_type> base_type;
    
  function_t(const function_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::function_t<AstTraits> &fn)
{
  if(fn.is_extern())
        os << "extern ";
  
  os << fn.return_type() << ' ';
  
  if(fn.is_operator())
    os << "operator ";
  
  os << fn.name() << "();";
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_FUNCTION_HPP
