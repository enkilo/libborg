#ifndef BORG_XML_DOM_NODE_HPP
#define BORG_XML_DOM_NODE_HPP

#include <borg/string.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/xml/lib/adapter.hpp>
#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/forward.hpp>
#include <borg/xml/dom/nodelist.hpp>

namespace borg {
namespace xml {
namespace dom {

enum id_type
{
  element_node = 1,
  attribute_node = 2,
  text_node = 3,
  cdata_section_node = 4,
  entity_reference_node = 5,
  entity_node = 6,
  processing_instruction_node = 7,
  comment_node = 8,
  document_node = 9,
  document_type_node = 10,
  document_fragment_node = 11,
  notation_node = 12
};
  
#define BORG_XML_DOM_NODE_TYPEIDS() \
  BOOST_STATIC_CONSTANT(int, element_node = xml::dom::element_node); \
  BOOST_STATIC_CONSTANT(int, attribute_node = xml::dom::attribute_node); \
  BOOST_STATIC_CONSTANT(int, text_node = xml::dom::text_node);

  
//using borg::dereference_cast;
//using borg::string_t;

//---------------------------------------------------------------------------
#define XML_DOM_INTERFACE(name) \
  template<class Traits, class Derived> \
  struct name ## _interface

//---------------------------------------------------------------------------
//! Node interface.
//---------------------------------------------------------------------------
XML_DOM_INTERFACE(node)
{
  XML_DOM_TYPES(typename Traits)

  typedef node_impl<Traits> impl;

  //! Get the name of the node.
  //-----------------------------------------------------------------------
  string_t<wchar_type, Traits> const
  name() const
  {
    return impl::name(dereference_cast<Derived const>(this));
  }
  
  //! Get the value (content) of the node.
  //-----------------------------------------------------------------------
  string_t<wchar_type, Traits> const
  value() const
  {
    return impl::value(dereference_cast<Derived const>(this));
  }
  
  //! Get the path to the node.
  //-----------------------------------------------------------------------
  string_t<wchar_type, Traits> const
  path() const
  {
    return impl::path(dereference_cast<Derived const>(this));
  }
  
  //! Get numeric type of the node.
  //-----------------------------------------------------------------------
  id_type
  type() const
  {
    return impl::type(dereference_cast<Derived const>(this));
  }
  
  //! Get a nodelist with all child nodes.
  //-----------------------------------------------------------------------
  nodelist_t<Traits>
  child_nodes() const
  {
    return impl::child_nodes(dereference_cast<Derived const>(this));
  }
  
  //! Gets the first child of this node.
  //-----------------------------------------------------------------------
  node_t<Traits>
  first_child() const
  {
    return impl::first_child(dereference_cast<Derived const>(this));
  }
  
  //! Gets the last child of this node.
  //-----------------------------------------------------------------------
  node_t<Traits>
  last_child() const
  {
    return impl::last_child(dereference_cast<Derived const>(this));
  }
  
  //! Gets the node immediately preceding this node.
  //-----------------------------------------------------------------------
  node_t<Traits>
  previous_sibling() const
  {
    return impl::previous_sibling(dereference_cast<Derived const>(this));
  }
  
  //! Gets the node immediately following this node.
  //-----------------------------------------------------------------------
  node_t<Traits>
  next_sibling() const
  {
    return impl::next_sibling(dereference_cast<Derived const>(this));
  }
  
  //! Gets the owner document.
  //-----------------------------------------------------------------------
  document_t<Traits>
  owner_document() const
  {
    return impl::owner_document(dereference_cast<Derived const>(this));
  }
  
  //! Appends a child node.
  //-----------------------------------------------------------------------
  node_t<Traits>
  append_child(const node_t<Traits> &n) const
  {
    return impl::append_child(dereference_cast<Derived const>(this), n);
  }
  
};

//---------------------------------------------------------------------------
template<class Traits, class Derived>
struct node_facade
{
  XML_DOM_TYPES(typename Traits);
  
  typedef node_impl<Traits> impl;
  
/*  operator element_t<Traits>() const
  {
    return element_type(dereference_cast<Derived const>(this));
  }*/
  
/*  operator element_type() const
  {
    return element_type(dereference_cast<Derived const>(this));
  }*/
  
  operator attribute_t<Traits>() const
  {
    return attribute_type(dereference_cast<Derived const>(this));
  }
  
  operator attribute_type() const
  {
    return attribute_type(dereference_cast<Derived const>(this));
  }
  
/*  bool
  operator==(const id_type &id) const
  {
    return (int)impl::type(dereference_cast<Derived const>(this)) == (int)id;
  }*/
  
};
  
    
  
} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_NODE
