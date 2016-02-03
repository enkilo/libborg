#ifndef XML_XPATH_TYPES_HPP
#define XML_XPATH_TYPES_HPP

#include <borg/xml/lib/types.hpp>

namespace xml {
namespace xpath {

//---------------------------------------------------------------------------
//! Macro to slurp in the typedefs from the traits.
//---------------------------------------------------------------------------
#define XML_XPATH_TYPES(Traits) \
  typedef Traits::evaluator_type evaluator_type; \
  typedef Traits::expression_type expression_type; \
  typedef Traits::ns_resolver_type ns_resolver_type; \
  typedef Traits::result_type result_type; \
  typedef Traits::nodeset_type nodeset_type; \
  typedef Traits::number_type number_type; \
  BORG_PP_USE_TYPE(Traits, xpath_function_type); \
  BORG_PP_USE_TYPE(Traits, xpath_parser_type); \
  XML_DOM_TYPES(Traits)
  
//---------------------------------------------------------------------------

}// namespace xpath
}// namespace xml

//---------------------------------------------------------------------------
#endif //ndef XML_XPATH_TYPES_HPP
