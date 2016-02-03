#ifndef BORG_AST_TRAITS_HPP
#define BORG_AST_TRAITS_HPP

#include <borg/preproc.hpp>
#include <borg/wrap/preproc.hpp>

namespace borg {
namespace ast {

#define BORG_AST_PATTERN_SEQ \
    (_impl) \
    (_interface) \
    (_facade) \
    (_t)

#define BORG_AST_FORWARD(Name, Extra...) \
        WRAP_SEQ_FORWARD(Name, BORG_AST_PATTERN_SEQ, Extra)
  
  
//---------------------------------------------------------------------------
#define BORG_AST_NODE_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, string_type); \
  BORG_PP_USE_TYPE(Traits, node_type); \
  BORG_PP_USE_TYPE(Traits, function_type);
  
} // namespace ast
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_AST_TRAITS_HPP
