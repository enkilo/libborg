#ifndef BORG_XML_XPATH_ADAPTERS_HPP
#define BORG_XML_XPATH_ADAPTERS_HPP

#include <borg/wrap/wrapper.hpp>
#include <borg/xml/adapter_macros.hpp>

#include <borg/xml/xpath/forward.hpp>
#include <borg/xml/xpath/types.hpp>
//#include <borg/xml/xpath/evaluator.hpp>
//#include <borg/xml/xpath/expression.hpp>
#include <borg/xml/xpath/nodeset.hpp>
#include <borg/xml/xpath/ns_resolver.hpp>

namespace borg {
namespace xml {
namespace xpath {

//---------------------------------------------------------------------------
XML_ADAPTER_CLASS_0(evaluator)
XML_ADAPTER_CLASS_0(expression)
XML_ADAPTER_CLASS_0(result)
XML_ADAPTER_CLASS_0(nodeset)
XML_ADAPTER_CLASS_0(ns_resolver)

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XML_XPATH_ADAPTERS_HPP
