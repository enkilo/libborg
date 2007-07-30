#ifndef BORG_LIBXML2_DOM_DOCUMENT_HPP
#define BORG_LIBXML2_DOM_DOCUMENT_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/interface.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct document_impl<libxml2::traits> : node_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

  //! Create empty document.
  //-----------------------------------------------------------------------
  static document_type
  create(const wchar_type *version)
  {
    return xmlNewDoc(version);
  }
    
  //! Destroy document.
  //-----------------------------------------------------------------------
  static void
  destroy(document_type const doc)
  {
    return xmlFreeDoc(doc);
  }
    
  //! Get root element.
  //-----------------------------------------------------------------------
  static element_type
  root(document_type const doc)
  {
    return xmlDocGetRootElement(doc);
  }
    
  //-----------------------------------------------------------------------
  static attribute_type
  get_id(document_type const doc, const wchar_type *id)
  {
    return xmlGetID(doc, id);
  }
    
  //-----------------------------------------------------------------------
  static element_type
  get_element_by_id(document_type const doc, const wchar_type *id)
  {
    attribute_type attr = xmlGetID(doc, id);    
    return (attr ? attr->parent : 0);
  }
    
  //-----------------------------------------------------------------------
  static bool
  is_id(document_type const doc, element_type const elem, 
        attribute_type const attr)
  {
    return xmlIsID(doc, elem, attr);
  }
    
  //-----------------------------------------------------------------------
  static bool
  remove_id(document_type const doc, attribute_type const attr)
  {
    return xmlRemoveID(doc, attr);
  }
    
  //-----------------------------------------------------------------------
  static bool
  is_ref(document_type const doc, element_type const elem,
         attribute_type const attr)
  {
    return xmlIsRef(doc, elem, attr);
  }
  
  //-----------------------------------------------------------------------
  static bool
  remove_ref(document_type const doc, attribute_type const attr)
  {
    return xmlRemoveRef(doc, attr);
  }
  
};

//----------------------------------------------------------------------------
/*template<>
class document_t<libxml2::traits>
    : public wrapper<libxml2::traits::document_type>
    , public document_interface< libxml2::traits, document_t<libxml2::traits> >
{
public:
  XML_DOM_TYPES(libxml2::traits)

  typedef wrapper<libxml2::traits::document_type> base_type;
  
  //! Wrapper constructor.
  document_t(document_type const &p) 
    : base_type(p)
  {}

};*/
  
} // namespace dom
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::document_t<traits> document_t;

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_DOCUMENT_HPP
