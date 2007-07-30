#ifndef BORG_LIBXML_DOM_ADAPTERS_HPP
#define BORG_LIBXML_DOM_ADAPTERS_HPP

#include <borg/libxml2/dom/parser.hpp>
#include <borg/libxml2/dom/node.hpp>
#include <borg/libxml2/dom/nodelist.hpp>
#include <borg/libxml2/dom/nodemap.hpp>
#include <borg/libxml2/dom/element.hpp>
#include <borg/libxml2/dom/document.hpp>
#include <borg/libxml2/dom/attribute.hpp>
#include <borg/libxml2/dom/writer.hpp>

#include <borg/xml/dom/idref.hpp>
#include <borg/xml/dom/idreflist.hpp>

namespace borg { 
namespace libxml2 { 
namespace dom {

//----------------------------------------------------------------------------
typedef xml::dom::parser_t<traits> parser_t;
typedef xml::dom::node_t<traits> node_t;
typedef xml::dom::element_t<traits> element_t;
typedef xml::dom::attribute_t<traits> attribute_t;
typedef xml::dom::document_t<traits> document_t;

typedef xml::dom::writer_t<traits> writer_t;
typedef xml::dom::writer<traits> writer;

typedef xml::dom::idref_t<traits> idref_t;
typedef xml::dom::idreflist_t<traits> idreflist_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML_DOM_ADAPTERS_HPP
