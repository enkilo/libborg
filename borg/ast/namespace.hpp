#ifndef BORG_AST_NAMESPACE_HPP
#define BORG_AST_NAMESPACE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/declaration.hpp>
#include <borg/ast/named.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_NAMESPACE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, namespace_type)
  
//---------------------------------------------------------------------------
BORG_AST_FORWARD(namespace)

//---------------------------------------------------------------------------
//! Represents a namespace. Namespaces are not necessarily named (anonymous
//! namespaces are possible) and not necessarily scoped (although the root 
//! namespace is usually the only exception).
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct namespace_interface
    : public node_interface<Traits, Derived>
//    , public scoped_interface<Traits, Derived>
{  
  BORG_AST_NAMESPACE_TYPES(typename Traits)
 
  typedef namespace_impl<Traits> impl;
  
  bool 
  is_root() const { return impl::is_root(dereference_cast<Derived const>(this)); }

  string_type
  name() const
  { return named_impl<Traits>::get_name(dereference_cast<Derived const>(this)); }

  namespace_t<Traits>
  context() const
  { return scoped_impl<Traits>::get_context(dereference_cast<Derived const>(this)); }
    
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct namespace_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class namespace_t
    : public wrapper<typename Traits::namespace_type>
    , public namespace_interface< Traits, namespace_t<Traits> >
    , public namespace_facade< Traits, namespace_t<Traits> >
{
public:
  BORG_AST_NAMESPACE_TYPES(typename Traits)
    
  typedef wrapper<typename Traits::namespace_type> base_type;
    
  namespace_t(const namespace_type &fn)
    : base_type(fn)
  {}
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os, 
           const borg::ast::namespace_t<AstTraits> &ns)
{
  std::basic_ostringstream<CharT, CharTraits> ostr;
  
  if(!ns.is_root() && !ns.context().is_root())
    ostr << ns.context() << "::";
  
  if(!ns.is_named())
    ostr << "<anonymous namespace>";
  else
    ostr << ns.name();
  
  os << ostr.str();
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NAMESPACE_HPP
