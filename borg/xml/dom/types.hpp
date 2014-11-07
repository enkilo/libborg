#ifndef XML_DOM_TYPES_HPP
#define XML_DOM_TYPES_HPP

#include <borg/xml/lib/types.hpp>

namespace xml {
namespace dom {

//---------------------------------------------------------------------------
//! Macro to slurp in the typedefs from the traits.
//---------------------------------------------------------------------------
#define XML_DOM_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, id_type); \
  BORG_PP_USE_TYPE(Traits, node_type); \
  BORG_PP_USE_TYPE(Traits, nodelist_type); \
  BORG_PP_USE_TYPE(Traits, nodemap_type); \
  BORG_PP_USE_TYPE(Traits, attribute_type); \
  BORG_PP_USE_TYPE(Traits, element_type); \
  BORG_PP_USE_TYPE(Traits, document_type); \
  BORG_PP_USE_TYPE(Traits, parser_type); \
  BORG_PP_USE_TYPE(Traits, exception_type); \
  typedef Traits::implementation_type implementation_type; \
  typedef Traits::text_type text_type; \
  typedef Traits::cdata_type cdata_type; \
  typedef Traits::comment_type comment_type; \
  typedef Traits::writer_type writer_type; \
  typedef Traits::options_type options_type; \
  typedef Traits::url_type url_type; \
  typedef Traits::return_type return_type; \
  XML_LIB_TYPES(Traits)
  
//---------------------------------------------------------------------------

}// namespace dom
}// namespace xml

//---------------------------------------------------------------------------
#endif //ndef XML_DOM_TYPES_HPP
