#ifndef BORG_AST_NODE_HPP
#define BORG_AST_NODE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/util/exception.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/traits.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(node)

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct node_interface
{  
  BORG_AST_NODE_TYPES(typename Traits)
 
  typedef node_impl<Traits> impl;
  typedef typename Traits::id_type id_type;
  
  id_type
  id() const
  {
    return impl::get_id
      (dereference_cast<Derived const>(this));
  }
  
  string_type
  nodename() const
  {
    return impl::nodename
      (dereference_cast<Derived const>(this));
  }
  
  bool is_named() const
    { return impl::is_named
        (dereference_cast<Derived const>(this)); }
  
  bool is_typed() const
    { return impl::is_typed
        (dereference_cast<Derived const>(this)); }
  
  bool is_scoped() const 
    { return impl::is_scoped
        (dereference_cast<Derived const>(this)); }  
  
  bool is_compound() const 
    { return impl::is_compound
        (dereference_cast<Derived const>(this)); }  
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct node_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class node_t
    : public wrapper<typename Traits::node_type>
    , public node_interface< Traits, node_t<Traits> >
    , public node_facade< Traits, node_t<Traits> >
{
public:
  BORG_AST_NODE_TYPES(typename Traits)

  typedef wrapper<node_type> base_type;
    
  node_t(const node_type &fn) 
    : base_type(fn)
  {
    if(unwrap_cast(*this) == 0)
      throw exception<Traits>("null node!");
  }
};
  
  
//---------------------------------------------------------------------------
/*template<class Traits>
class node
{
};*/
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::node_t<AstTraits> &ns)
{
  throw borg::exception<AstTraits>("you need to specialize operator<<");  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_HPP
