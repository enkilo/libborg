#ifndef BORG_AST_NODE_CAST_HPP
#define BORG_AST_NODE_CAST_HPP

#include <borg/util/exception.hpp>

namespace borg {
namespace ast {

template<class Traits>
struct node_t;
  
template<class Traits>
struct named_t;
  
//---------------------------------------------------------------------------
template<template<class> class TargetN, template<class> class SourceN, class Traits>
TargetN<Traits> &
node_cast(SourceN<Traits> const &node)
{
  return (TargetN<Traits> &)node;
}
  
/*template<class Traits>
named_t<Traits> &
node_cast< named_t<Traits> >(node_t<Traits> const &node)
{
  if(!node.is_named())
    throw exception<Traits>("not a named node!");
  
  return (named_t<Traits> &)node;
}*/
  
    
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_NODE_CAST_HPP
