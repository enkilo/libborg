#ifndef BORG_AST_TREE_HPP
#define BORG_AST_TREE_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/branch.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
#define BORG_AST_TREE_TYPES(Traits) \
  BORG_AST_SEQUENCE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, tree_type)

template<class Traits>
struct tree_impl;
/*  
//---------------------------------------------------------------------------
WRAP_PATTERN_FORWARD(tree)

//---------------------------------------------------------------------------
template<class Traits, class Node, class Impl>
class sequence_proxy;
    
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct tree_interface : public sequence_interface<Traits, Derived>
{  
  BORG_AST_TREE_TYPES(typename Traits)
 
  typedef tree_impl<Traits> impl;
    
};
  
//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct tree_facade
{
  
  
};
  */
//---------------------------------------------------------------------------
template<class Traits>
class tree_t
    : public branch_t<typename Traits::sequence_type, typename Traits::tree_type, Traits>
{
public:
  BORG_AST_TREE_TYPES(typename Traits)
    
  typedef branch_t<sequence_type, tree_type, Traits> base_type;
  
  tree_t(const tree_type &tree)
    : base_type(tree)
  {}
  
  
};
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_TREE_HPP
