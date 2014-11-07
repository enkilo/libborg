#ifndef BORG_XML_DOM_FORWARD_HPP
#define BORG_XML_DOM_FORWARD_HPP

#include <borg/xml/lib/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
//! Forward declare all DOM classes.
//---------------------------------------------------------------------------
XML_FORWARD_DECL_0(implementation)
XML_FORWARD_DECL_0(parser)
XML_FORWARD_DECL_0(exception)
XML_FORWARD_DECL_0(document)
XML_FORWARD_DECL_0(element)
XML_FORWARD_DECL_0(attribute)
XML_FORWARD_DECL_0(node)
XML_FORWARD_DECL_0(text)
XML_FORWARD_DECL_0(comment)
XML_FORWARD_DECL_0(cdata)
XML_FORWARD_DECL_0(processing_instruction)
XML_FORWARD_DECL_0(xpath_evaluator)
XML_FORWARD_DECL_0(xpath_expression)
XML_FORWARD_DECL_0(xpath_ns_resolver)
XML_FORWARD_DECL_0(writer)
//XML_FORWARD_DECL_T(nodelist, class NodeT = node_t<Traits>)
XML_FORWARD_DECL_T(nodemap, template<class> class T = attribute_t)
  
} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_DOM_FORWARD_HPP
