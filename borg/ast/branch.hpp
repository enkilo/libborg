#ifndef BORG_AST_BRANCH_HPP
#define BORG_AST_BRANCH_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/node.hpp>
#include <borg/ast/sequence.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_BRANCH_TYPES(Traits) \
  BORG_AST_SEQUENCE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, branch_type)
  
//---------------------------------------------------------------------------
template<class Children, class Parent, class Traits>
struct branch_impl;

//---------------------------------------------------------------------------
template<class T, class Sequence, class Traits, class Node, class Impl>
class sequence_proxy;
    
//---------------------------------------------------------------------------
template<class Children, class Parent, class Traits, class Derived>
struct branch_interface
    : public node_interface<Traits, Derived>
    , public sequence_interface<typename Children::value_type, Children, Traits, Derived>
{  
  typedef branch_impl<Children, Parent, Traits> impl;
    
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct branch_facade
{
  
  
};
  
//---------------------------------------------------------------------------
template<class Children, class Parent, class Traits>
class branch_t
    : public branch_interface< Children, Parent, Traits, branch_t<Children, Parent, Traits> >
    , public branch_facade< Traits, branch_t<Children, Parent, Traits> >
{
public:
  typedef branch_impl<Children, Parent, Traits> impl;
  
  sequence_proxy< node_t<Traits>, sequence_t< node_t<Traits>, Children, Traits >, Traits, Parent, impl > children;

  branch_t(const Parent &p)
    : children(p)
  {}
  
  
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_BRANCH_HPP
