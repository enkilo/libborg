#ifndef BORG_AST_BASIC_TYPE_HPP
#define BORG_AST_BASIC_TYPE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/ast/declaration.hpp>
#include <borg/ast/node_cast.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_BASIC_TYPE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, basic_type_type)
  
//---------------------------------------------------------------------------
BORG_AST_FORWARD(named)
BORG_AST_FORWARD(typed)
BORG_AST_FORWARD(basic_type)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct basic_type_interface 
    : public node_interface<Traits, Derived>
{  
  BORG_AST_BASIC_TYPE_TYPES(typename Traits)
 
  typedef basic_type_impl<Traits> impl;
  
  bool
  is_alias() const
  {
    return impl::is_alias
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_array() const
  {
    return impl::is_array
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_cv_qualified() const
  {
    return impl::is_cv_qualified
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_function() const
  {
    return impl::is_function
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_fundamental() const
  {
    return impl::is_fundamental
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_method() const
  {
    return impl::is_method
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_offset() const
  {
    return impl::is_offset
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_pointer() const
  {
    return impl::is_pointer
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_reference() const
  {
    return impl::is_reference
      (dereference_cast<Derived const>(this));
  }
  
  bool
  is_sized() const
  {
    return impl::is_sized
      (dereference_cast<Derived const>(this));
  }
  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct basic_type_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class basic_type_t
    : public wrapper<typename Traits::basic_type_type>
    , public basic_type_interface< Traits, basic_type_t<Traits> >
    , public basic_type_facade< Traits, basic_type_t<Traits> >
{
public:
  BORG_AST_BASIC_TYPE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::basic_type_type> base_type;
    
  basic_type_t(const basic_type_type &fn) 
    : base_type(fn)
  {}
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::basic_type_t<AstTraits> &node)
{
  using namespace borg::ast;
  
  if(node.is_typed() && !node.is_alias())
    os << node_cast<typed_t>(node).type();
  else if(node.is_named())
    os << node_cast<named_t>(node);
  else
    os << "unknown-type";
  
  if(node.is_pointer())
    os << '*';

  if(node.is_reference())
    os << '&';

/*  if(node.is_sized())
    os << "(sized)";*/

  if(node.is_array())
    os << "[]";

  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_BASIC_TYPE_HPP
