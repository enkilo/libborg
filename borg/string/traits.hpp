#ifndef BORG_STRING_TRAITS_HPP
#define BORG_STRING_TRAITS_HPP

#include <borg/preproc.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Macro to fetch all string-related typedefs from the traits class.
//!
//! The traits class delivers the types of the underlaying implementation.
//! Each line of this macro will expand to:
//!
//! typedef Traits::whatever_type whatever_type;
//!
//! ...that should already have explained why we decided to use the 
//! preprocessor here.
//---------------------------------------------------------------------------
#define BORG_STRING_TYPES(Traits) \
  BORG_PP_USE_TYPE(Traits, string_type) \
  BORG_PP_USE_TYPE(Traits, const_string_type) \
  BORG_PP_USE_TYPE(Traits, char_type) \
  BORG_PP_USE_TYPE(Traits, wchar_type) \
  BORG_PP_USE_TYPE(Traits, length_type) \
  BORG_PP_USE_TYPE(Traits, index_type)

//---------------------------------------------------------------------------

} // namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef BORG_STRING_TRAITS_HPP
