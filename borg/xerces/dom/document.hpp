#ifndef BORG_XERCES_DOM_DOCUMENT_HPP
#define BORG_XERCES_DOM_DOCUMENT_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct document_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)

  static nodelist_type
  get_elements_by_tag_name(document_type doc, wchar_type const *name)
  {
    return doc->getElementsByTagName(name);
  }      

  static node_type
  get_element_by_id(document_type doc, wchar_type const *id)
  {
    return doc->getElementById(id);
  }      
  
  //! Creates a new element node.
  //-----------------------------------------------------------------------
  static element_t<xerces::traits>
  create_element(document_type doc, wchar_type const *str)
  {
    return doc->createElement(str);
  }
  
  //! Creates a new text node.
  //-----------------------------------------------------------------------
  static text_t<xerces::traits>
  create_text_node(document_type doc, wchar_type const *str)
  {
    return doc->createTextNode(str);
  }
  
  //! Creates a new comment node.
  //-----------------------------------------------------------------------
/*  static comment_t<xerces::traits>
  create_comment(document_type doc, wchar_type const *str)
  {
    return doc->createComment(str);
  }*/
  
  //! Creates a new CDATA section.
  //-----------------------------------------------------------------------
  static cdata_t<xerces::traits>
  create_cdata_section(document_type doc, wchar_type const *str)
  {
    return doc->createCDATASection(str);
  }
  
  //! Creates a new attribute node.
  //-----------------------------------------------------------------------
  static attribute_t<xerces::traits>
  create_attribute(document_type doc, wchar_type const *name)
  {
    return doc->createAttribute(name);
  }
  
  //! Gets the character encoding.
  //-----------------------------------------------------------------------
  static wchar_type const *
  get_encoding(document_type doc)
  {
    return doc->getEncoding();
  }

  static wchar_type const *
  get_actual_encoding(document_type doc)
  {
    return doc->getActualEncoding();
  }
  
  //! Sets the character encoding.
  //-----------------------------------------------------------------------
  static void
  set_encoding(document_type doc, const wchar_type *str)
  {
    doc->setEncoding(str);
  }

  static void
  set_actual_encoding(document_type doc, const wchar_type *str)
  {
    doc->setActualEncoding(str);
  }
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_DOCUMENT_HPP
