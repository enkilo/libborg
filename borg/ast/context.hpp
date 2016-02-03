#ifndef BORG_AST_NODE_FUNCTION_HPP
#define BORG_AST_NODE_FUNCTION_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/node/declaration.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(function)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct function_interface 
    : declaration_interface<Traits, Derived>
{  
  BORG_AST_NODE_TYPES(typename Traits)
 
  typedef function_impl<Traits> impl;
    
  string_type
  name() const
  {
    return impl::get_name
      (dereference_cast<Derived const>(this));
  }  
    
  sequence_type
  arguments() const
  {
    return impl::get_arguments
      (dereference_cast<Derived const>(this));
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

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_FUNCTION_HPP
