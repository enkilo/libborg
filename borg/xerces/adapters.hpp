#ifndef BORG_XERCES_ADAPTERS_HPP
#define BORG_XERCES_ADAPTERS_HPP

#include <borg/xml/dom/adapters.hpp>

#include <borg/xerces/string.hpp>
#include <borg/xerces/allocator.hpp>
#include <borg/xerces/lib/output_buffer.hpp>

#include <borg/xerces/dom/node.hpp>
#include <borg/xerces/dom/nodelist.hpp>
#include <borg/xerces/dom/nodemap.hpp>
//#include <borg/xerces/dom/attribute.hpp>
#include <borg/xerces/dom/element.hpp>
#include <borg/xerces/dom/document.hpp>
#include <borg/xerces/dom/parser.hpp>
#include <borg/xerces/dom/exception.hpp>
#include <borg/xerces/dom/text.hpp>
#include <borg/xerces/dom/implementation.hpp>
#include <borg/xerces/dom/writer.hpp>

#include <borg/xerces/xpath/evaluator.hpp>
#include <borg/xerces/xpath/expression.hpp>
#include <borg/xerces/xpath/ns_resolver.hpp>

//---------------------------------------------------------------------------

namespace borg { 
namespace xerces {


/*typedef borg::string_t<traits::char_type, traits> string_t;
typedef borg::string<traits::char_type, traits> string;
typedef borg::string_t<traits::wchar_type, traits> wstring_t;
typedef borg::string<traits::wchar_type, traits> wstring;*/

/*template<class T>
struct allocator : public borg::allocator<traits, T>
{
  BORG_ALLOCATOR_TYPES(traits, T)
  
  typedef borg::allocator<traits, T> base_type;
  
  allocator(const allocator_type &a) : base_type(a)
  {}
  
};*/

/*template<class T>
struct allocator_t : public borg::allocator_t<traits, T> 
{
  BORG_ALLOCATOR_TYPES(traits, T)
  
  typedef borg::allocator_t<traits, T> base_type;
  
  allocator_t(const allocator_type &a) : base_type(a)
  {}
  
};*/
  
  
typedef xml::output_buffer<traits, traits::membuf_output_buffer_type> membuf_output_buffer_t;
typedef xml::output_buffer<traits, traits::localfile_output_buffer_type> localfile_output_buffer_t;
typedef xml::output_buffer<traits, traits::stdout_output_buffer_type> stdout_output_buffer_t;

//---------------------------------------------------------------------------

namespace dom
{
typedef xml::dom::parser<traits> parser;
typedef xml::dom::implementation<traits> implementation;
typedef xml::dom::writer<traits> writer;
};
  
XML_ADAPTER_USE_0(dom, node);
XML_ADAPTER_USE_0(dom, nodelist);
XML_ADAPTER_USE_0(dom, nodemap);
XML_ADAPTER_USE_0(dom, attribute);
XML_ADAPTER_USE_0(dom, text);
XML_ADAPTER_USE_0(dom, comment);
XML_ADAPTER_USE_0(dom, document);
XML_ADAPTER_USE_0(dom, element);
XML_ADAPTER_USE_0(dom, parser);
XML_ADAPTER_USE_0(dom, implementation);
XML_ADAPTER_USE_0(dom, writer);

XML_ADAPTER_USE_0(xpath, evaluator);
XML_ADAPTER_USE_0(xpath, expression);
XML_ADAPTER_USE_0(xpath, ns_resolver);

//---------------------------------------------------------------------------

}// namespace xerces
}// namespace borg

#endif //ndef BORG_XERCES_ADAPTERS_HPP
