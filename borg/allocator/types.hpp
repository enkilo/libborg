#ifndef BORG_ALLOCATOR_TYPES_HPP
#define BORG_ALLOCATOR_TYPES_HPP

#include <borg/preproc.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! Macro to fetch all allocator-related typedefs from the traits class.
//!
//! The traits class delivers the types of the underlaying implementation.
//! Each line of this macro will expand to:
//!
//! typedef Traits::whatever_type whatever_type;
//!
//! ...that should already have explained why we decided to use the 
//! preprocessor here.
//---------------------------------------------------------------------------
#define BORG_ALLOCATOR_TYPES(Traits, Type) \
  BORG_PP_USE_TYPE(Traits, allocator_type) \
  BORG_PP_USE_TYPE(Traits, size_type) \
  typedef ptrdiff_t         difference_type; \
  typedef Type        value_type; \
  typedef Type       *      pointer; \
  typedef Type const *const_pointer; \
  typedef Type       &      reference; \
  typedef Type const &const_reference;
  
//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_TYPES_HPP
