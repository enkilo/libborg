#ifndef BORG_WX_DOM_DOCUMENT_HPP
#define BORG_WX_DOM_DOCUMENT_HPP

#include <borg/wx/traits.hpp>
#include <borg/xml/dom/forward.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//---------------------------------------------------------------------------
template<>
struct document_impl<wx::traits>
{
  XML_DOM_TYPES(wx::traits)

  //-----------------------------------------------------------------------
  //! Get the document root node.
  //-----------------------------------------------------------------------
  template<class DocumentT>
  static node_type
  root(DocumentT const &doc)
  {
    return doc->GetRoot();
  }      

/*  template<class DocumentT, class StringT>
  static node_type
  get_element_by_id(DocumentT const &doc, StringT const &id)
  {
    return doc->getElementById(id);
  }      
  
  //! Creates a new element node.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static element_adapter<wx::traits>
  create_element(DocumentT const &doc, const StringT &str)
  {
    return doc->createElement(str);
  }
  
  //! Creates a new text node.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static text_adapter<wx::traits>
  create_text_node(DocumentT const &doc, const StringT &str)
  {
    return doc->createTextNode(str);
  }
  
  //! Creates a new comment node.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static text_adapter<wx::traits>
  create_comment(DocumentT const &doc, const StringT &str)
  {
    return doc->createComment(str);
  }
  
  //! Creates a new CDATA section.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static cdata_adapter<wx::traits>
  create_cdata_section(DocumentT const &doc, const StringT &str)
  {
    return doc->createCDATASection(str);
  }
  
  //! Creates a new attribute node.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static attribute_adapter<wx::traits>
  create_attribute(DocumentT const &doc, const StringT &name)
  {
    return doc->createAttribute(name);
  }
  
  //! Gets the character encoding.
  //-----------------------------------------------------------------------
  template<class DocumentT>
  static const wchar_type *
  get_encoding(DocumentT const &doc)
  {
    return doc->getEncoding();
  }

  template<class DocumentT>
  static const wchar_type *
  get_actual_encoding(DocumentT const &doc)
  {
    return doc->getActualEncoding();
  }
  
  //! Sets the character encoding.
  //-----------------------------------------------------------------------
  template<class DocumentT, class StringT>
  static void
  set_encoding(const DocumentT &doc, const StringT &str)
  {
    return doc->setEncoding(str);
  }

  template<class DocumentT, class StringT>
  static void
  set_actual_encoding(const DocumentT &doc, const StringT &str)
  {
    return doc->setActualEncoding(str);
  }*/
};
  
//---------------------------------------------------------------------------

} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_DOM_DOCUMENT_HPP
