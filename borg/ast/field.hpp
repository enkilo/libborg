#ifndef BORG_AST_FIELD_HPP
#define BORG_AST_FIELD_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/branch.hpp>
#include <borg/ast/declaration.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_FIELD_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, compound_type); \
  BORG_PP_USE_TYPE(Traits, members_type)
  
//---------------------------------------------------------------------------
template<class Traits>
struct compound_impl;

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct compound_interface
    : public branch_interface< typename Traits::sequence_type, typename Traits::members_type, Traits, Derived >
    , public declaration_interface<Traits, Derived>
{
  BORG_AST_FIELD_TYPES(typename Traits)
 
  typedef compound_impl<Traits> impl;
   
  static bool
  is_compound() { return true; }  
   
  bool
  is_struct() const
    { return impl::is_struct(dereference_cast<Derived const>(this)); }
   
  bool
  is_class() const
    { return impl::is_class(dereference_cast<Derived const>(this)); }
   
  bool
  is_union() const
    { return impl::is_union(dereference_cast<Derived const>(this)); }
   
  bool
  is_enum() const
    { return impl::is_enum(dereference_cast<Derived const>(this)); }
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct compound_facade
{

  
};
  
//---------------------------------------------------------------------------
template<class Traits>
class compound_t
    : public compound_interface< Traits, compound_t<Traits> >
    , public compound_facade< Traits, compound_t<Traits> >
{
public:
  typedef compound_impl<Traits> impl;
  
  BORG_AST_FIELD_TYPES(typename impl)

  sequence_proxy< node_type, members_type, Traits, compound_type, impl > children;
  
  compound_t(const compound_type &fn) 
    : children(fn)
  {}
  
  operator compound_type const &() const
  {
    return children.get_parent();
  }
  
};

//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

template<class CharT, class CharTraits, class AstTraits>
std::basic_ostream<CharT, CharTraits> &
operator<<(std::basic_ostream<CharT, CharTraits> &os,
           const borg::ast::compound_t<AstTraits> &compound)
{
  if(compound.is_struct())
    os << "struct ";
  else if(compound.is_class())
    os << "class ";
  else if(compound.is_union())
    os << "union ";
  else if(compound.is_enum())
    os << "enum ";
  else
    os << "<no such compound type>";

  os << compound.name() << " { ";
  
  
  
  typeof(compound.children.begin()) itb = compound.children.begin();
  typeof(compound.children.end()) ite = compound.children.end();
  
  while(itb != ite)
  {
//    borg::ast::node_t<AstTraits> n = *itb;

    os << *itb;
//    os << "members...;";
    
    ++itb;
    
    if(itb != ite)
      os << ' ';
  }
  
/*  BOOST_FOREACH(borg::ast::node_t<AstTraits> n, compound.children)
  {
    os << n;
  }*/
  
  os << " };";
  
  return os;
}

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_FIELD_HPP
