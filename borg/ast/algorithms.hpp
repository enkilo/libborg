#ifndef BORG_AST_ALGORITHMS_HPP
#define BORG_AST_ALGORITHMS_HPP

#include <borg/wrap/preproc.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/util/dereference_cast.hpp>
#include <boost/mpl/void.hpp>
#include <borg/ast/node.hpp>

namespace borg {
namespace ast {

//---------------------------------------------------------------------------
template<class Node>
static inline
int
id(const Node &n)
{
  return Node::impl::id(n);
}
  
//---------------------------------------------------------------------------
template<class Node>
static inline
stdcxx::string
name(const Node &n)
{
  return Node::impl::nodename(n);
}
  
//---------------------------------------------------------------------------

} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_ALGORITHMS_HPP
