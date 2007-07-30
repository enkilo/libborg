#ifndef BORG_LIBXML2_DOM_NODE_HPP
#define BORG_LIBXML2_DOM_NODE_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/interface.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//----------------------------------------------------------------------------
template<>
struct node_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

 //! Return the node name as string.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static const wchar_type *
  name(NodeT const &node)
  {
    return node->name;
  }

  //! Return the node value as string.
  //-----------------------------------------------------------------------
//  template<typename NodeT>
  static const wchar_type *
  value(attribute_type const node)
  {
    return value(node->children);
  }

  static const wchar_type *
  value(node_type const node)
  {
    return xmlNodeGetContent(node);
  }

  static const wchar_type *
  path(node_type const node)
  {
    return xmlGetNodePath(node);
  }

  //! Return the numeric node type id.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static id_type
  type(NodeT const &node)
  {
    return node->type;
  }

  //! Get a nodelist with all child nodes.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static nodelist_type
  child_nodes(NodeT const &node)
  {
    return node->children;
  }
  
  //! Get a nodelist with all child nodes.
  //-----------------------------------------------------------------------
  template<class NodeT>
  static document_type
  owner_document(NodeT const &node)
  {
    return node->doc;
  }
  
  //! Gets the first child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  first_child(NodeT const &node)
  {
    return node->children;
  }

  //! Gets the last child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  last_child(NodeT const &node)
  {
    return ::xmlGetLastChild(node);
  }

  //! Gets the next sibling to this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  next_sibling(NodeT const &node)
  { 
    return node->next;
  }
  
  //! Gets the last child of this node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static node_type
  previous_sibling(NodeT const &node)
  {
    return node->prev;
  }

  //! Dumps a node.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static return_type
  dump(buffer_type const buf, document_type const doc, NodeT const &cur,
       int level, int format)
  {
    return xmlNodeDump
      (buf, doc, (node_type)cur, level, format);
  }

  //! Dumps a node to output.
  //-----------------------------------------------------------------------
  template<typename NodeT>
  static return_type
  dump_output(output_buffer_type const buf, document_type const doc,
              NodeT const &cur, int level, int format, 
              const char *const encoding)
  {
    return xmlNodeDumpOutput
      (buf, doc, (node_type)cur, level, format, encoding);
  }
  
};

//----------------------------------------------------------------------------
/*template<>
class node_t<libxml2::traits>
    : public wrapper<libxml2::traits::node_type>
    , public node_interface< libxml2::traits, node_t<libxml2::traits> >
{
public:
  XML_DOM_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::node_type> base_type;
  
  //! Wrapper constructor.
  node_t(node_type const &p) 
    : base_type(p)
  {}

};*/
  
} // namespace dom
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

BORG_XML_DOM_NODE_TYPEIDS()

//typedef xml::dom::node_t<Traits> node_t;
  
} // namespace libxml2
} // namespace dom
  
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_NODE_HPP
