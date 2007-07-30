#ifndef BORG_GCCXML_TREE_HPP
#define BORG_GCCXML_TREE_HPP

#include <borg/gccxml/traits.hpp>
#include <borg/ast/tree.hpp>
#include <borg/util/exception.hpp>

namespace borg {
namespace ast  {

//----------------------------------------------------------------------------
template<class XmlTraits>
struct branch_impl<
      typename gccxml::traits<XmlTraits>::sequence_type,
      typename gccxml::traits<XmlTraits>::tree_type,
      gccxml::traits<XmlTraits> 
    >
{
  typedef gccxml::traits<XmlTraits> traits;
  
  BORG_AST_TREE_TYPES(typename traits)

  static sequence_type
  get_children(const tree_type &tree)
  {
    xml::dom::node_t<XmlTraits> n = tree.first_child();
    return n.child_nodes();
  }
  
};

//----------------------------------------------------------------------------

}// namespace ast
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_TREE_HPP
