#ifndef BORG_GCCXML_TRAITS_HPP
#define BORG_GCCXML_TRAITS_HPP

#include <borg/xml/dom/nodelist.hpp>
#include <borg/xml/dom/element.hpp>
#include <borg/xml/dom/idreflist.hpp>
#include <boost/tokenizer.hpp>
#include <borg/ast/traits.hpp>

namespace borg {
namespace gccxml {

//----------------------------------------------------------------------------
enum id
{
  argument_node,
  array_type_node,
  class_node,
  constructor_node,
  converter_node,
  cv_qualified_type_node,
  destructor_node,
  enum_value_node,
  enumeration_node,
  field_node,
  file_node,
  function_node,
  function_type_node,
  fundamental_type_node,
  method_node,
  method_type_node,
  namespace_node,
  offset_type_node,
  operator_function_node,
  operator_method_node,
  pointer_type_node,
  reference_type_node,
  struct_node,
  typedef_node,
  unimplemented_node,
  union_node,
  variable_node,
};

//----------------------------------------------------------------------------
template<class XmlTraits>
struct traits
{
  typedef XmlTraits xml_traits;
  typedef gccxml::id id_type;

  typedef typename XmlTraits::wchar_type         char_type;
  typedef borg::string_t< char_type, XmlTraits > string_type;
  typedef xml::dom::element_t< XmlTraits >       node_type;
  typedef xml::dom::element_t< XmlTraits >       declaration_type;
  typedef xml::dom::element_t< XmlTraits >       basic_type_type;
  typedef xml::dom::element_t< XmlTraits >       typed_type;
  typedef xml::dom::element_t< XmlTraits >       named_type;
  typedef xml::dom::element_t< XmlTraits >       context_type;
  typedef xml::dom::element_t< XmlTraits >       scoped_type;
  typedef xml::dom::element_t< XmlTraits >       function_type;
  typedef xml::dom::element_t< XmlTraits >       namespace_type;
  typedef xml::dom::element_t< XmlTraits >       argument_type;
  typedef xml::dom::element_t< XmlTraits >       variable_type;
  typedef xml::dom::element_t< XmlTraits >       compound_type;
  typedef xml::dom::element_t< XmlTraits >       file_type;
  typedef xml::dom::element_t< XmlTraits >       array_type_type;
  typedef borg::size_t                            size_type;

  typedef boost::tokenizer
  <
      boost::char_delimiters_separator<typename XmlTraits::wchar_type>,
      typename string_t<typename XmlTraits::wchar_type, XmlTraits>::const_iterator,
               string_t<typename XmlTraits::wchar_type, XmlTraits>
  > tokenizer_type;

  typedef xml::dom::idreflist_t< XmlTraits >     members_type;
  typedef xml::dom::nodelist_t< XmlTraits, xml::dom::element_t< XmlTraits > > sequence_type;
  typedef xml::dom::document_t< XmlTraits >      tree_type;
  typedef typename sequence_type::iterator       iterator;
  typedef typename sequence_type::const_iterator const_iterator;

  //typedef xml::string_t< XmlTraits >        attributes_type;
  
  typedef boost::tokenizer<
    boost::char_delimiters_separator<char_type>,
    typename string_type::const_iterator,
    string_type
  > attributes_type;
  
};
  
//----------------------------------------------------------------------------
#define BORG_GCCXML_NODE_TYPES(Traits) \
  BORG_AST_NODE_TYPES(Traits); \
  BORG_PP_USE_TYPE(Traits, typed_type);
  
}// namespace gccxml
}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_GCCXML_TRAITS_HPP
