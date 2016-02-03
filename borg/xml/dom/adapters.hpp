#ifndef BORG_XML_DOM_ADAPTERS_HPP
#define BORG_XML_DOM_ADAPTERS_HPP

#include <borg/string.hpp>
#include <borg/wrap/wrapper.hpp>
#include <borg/xml/adapter_macros.hpp>

#include <borg/xml/dom/types.hpp>
#include <borg/xml/dom/interface.hpp>
#include <borg/xml/dom/node.hpp>
#include <borg/xml/dom/nodelist.hpp>
#include <borg/xml/dom/nodemap.hpp>
#include <borg/xml/dom/element.hpp>
#include <borg/xml/dom/parser.hpp>
#include <borg/xml/dom/text.hpp>
#include <borg/xml/dom/cdata.hpp>
#include <borg/xml/dom/implementation.hpp>
#include <borg/xml/dom/writer.hpp>
//#include <borg/xml/xpath/evaluator.hpp>
//#include <borg/xml/xpath/expression.hpp>

namespace borg {
namespace xml {
namespace dom {

//---------------------------------------------------------------------------
//! Most adapters will want to use this wrapper.
//---------------------------------------------------------------------------
using borg::wrapper;
  
//---------------------------------------------------------------------------
XML_ADAPTER_CLASS_0(implementation)
XML_ADAPTER_CLASS_0(parser)
XML_ADAPTER_CLASS_0(exception)
//XML_ADAPTER_CLASS_0(document)
XML_ADAPTER_CLASS_0(text)
XML_ADAPTER_CLASS_0(comment)
XML_ADAPTER_CLASS_0(cdata)
XML_ADAPTER_CLASS_0(processing_instruction)
XML_ADAPTER_CLASS_0(writer)
/*XML_ADAPTER_CLASS_0(xpath_evaluator)
XML_ADAPTER_CLASS_0(xpath_expression)*/
        
//---------------------------------------------------------------------------
XML_ADAPTER_DECL_0(element)
{
public:
  XML_LIB_TYPES(typename Traits)
  typedef typename Traits::element_type element_type;
  typedef typename Traits::node_type node_type;
  typedef wrapper<element_type> base_type;

  element_t()
    : base_type(0)
  {}
  
  template<class ElementT>
  element_t(const ElementT &elm)
      : base_type(elm)
  {}
  
/*  element_t(element_type const &elm)
    : base_type(elm)
  {}

  element_t(element_t<Traits> const &elm)
    : base_type(elm)
  {}*/

  element_t(node_t<Traits> const &n)
    : base_type(n && n.type() == element_node ? (element_type)(node_type)n : 0)
  {}

/*  template<class Element>
  element_t(Element const &n)
    : base_type(n) 
  element_t(node_t<Traits> const &n)
    : base_type((element_type)n)
  {}*/

};
  
//---------------------------------------------------------------------------
XML_ADAPTER_DECL_0(attribute)
{
public:
  XML_LIB_TYPES(typename Traits)
  typedef typename Traits::attribute_type attribute_type;
  typedef typename Traits::node_type node_type;
  typedef wrapper<attribute_type> base_type;

  attribute_t(node_type const &a)
    : base_type((attribute_type)a)
  {}

  attribute_t(attribute_type const &a)
    : base_type(a)
  {}

  template<template<class> class Adapter>
  attribute_t(Adapter<Traits> const &a)
    : base_type((attribute_type)a)
  {}
};
    
//---------------------------------------------------------------------------
XML_ADAPTER_DECL_0(node)
{
public:
  XML_DOM_TYPES(typename Traits)
  typedef wrapper<node_type> base_type;

  node_t(node_type const &v) : base_type(v) {}
  

  template<template<class> class Adapter>
  node_t(Adapter<Traits> const &a)
    : base_type(a)
  {}

};
      
//---------------------------------------------------------------------------
/*XML_ADAPTER_DECL_1(nodelist)
{
public:
  XML_LIB_TYPES(typename Traits)
  typedef typename Traits::nodelist_type nodelist_type;
  typedef typename Traits::node_type node_type;
  typedef wrapper<nodelist_type> base_type;

  nodelist_t(nodelist_type const &v)
    : base_type(v)
  {}

  template<class NodeList>
  nodelist_t(NodeList const &n)
    : base_type(n)
  {}
};*/

//---------------------------------------------------------------------------
XML_ADAPTER_DECL_T(nodemap)
{
public:
  XML_LIB_TYPES(typename Traits)
  typedef typename Traits::nodemap_type nodemap_type;
  typedef typename Traits::node_type node_type;
  typedef wrapper<nodemap_type> base_type;

  nodemap_t(nodemap_type const &m)
    : base_type(m)
  {}

  template<class NodeMap>
  nodemap_t(NodeMap const &m)
    : base_type(m)
  {}
};

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_ADAPTERS_HPP
