#ifndef BORG_XERCES_DOM_NODE_HPP
#define BORG_XERCES_DOM_NODE_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
class node_impl<xerces::traits>
{
public:
  XML_DOM_TYPES(xerces::traits)
  
  //! Return the node name as string.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static wchar_type const *
  name(NodeT const &node)
  {
    return node->getNodeName();
  }

  //! Return the node value as string.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static wchar_type const *
  value(NodeT const &node)
  {
    return node->getNodeValue();
  }

  //! Return the numeric node type id.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static id_type
  type(NodeT const &node)
  {
    return node->getNodeType();
  }

  //! Get a nodelist with all child nodes.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static nodelist_type
  child_nodes(NodeT const &node)
  {
    return node->getChildNodes();
  }

  //! Gets the first child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  first_child(NodeT const &node)
  {
    return node->getFirstChild();
  }

  //! Gets the last child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  last_child(NodeT const &node)
  {
    return node->getLastChild();
  }

  //! Gets the next sibling to this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  next_sibling(NodeT const &node)
  {
    return node->getNextSibling();
  }

  //! Gets the last child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  previous_sibling(NodeT const &node)
  {
    return node->getPreviousSibling();
  }

  //! Gets the owner document.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static document_type
  owner_document(NodeT const &node)
  {
    return node->getOwnerDocument();
  }

  //! Appends a child node.
  //-----------------------------------------------------------------------
  template<typename NodeT, typename ArgT>
  static node_type
  append_child(NodeT const &node, ArgT const &child)
  {
    return node->appendChild(child);
  }

};

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_NODE_HPP
