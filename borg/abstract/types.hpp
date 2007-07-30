#ifndef BORG_ABSTRACT_TYPES_HPP
#define BORG_ABSTRACT_TYPES_HPP

#include <borg/preproc.hpp>

namespace borg {

#define BORG_ABSTRACT_LIST_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, list_type); \
  BORG_PP_USE_TYPE(Traits, length_type); \
  BORG_PP_USE_TYPE(Traits, index_type); \
  BORG_PP_USE_TYPE(Traits, deallocator_type); \
  BORG_PP_USE_TYPE(Traits, comparator_type); \
  BORG_PP_USE_TYPE(Traits, return_type);

}// namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ABSTRACT_TYPES_HPP
