#ifndef VECTOR_TYPES_HPP
#define VECTOR_TYPES_HPP

#include <borg/types/rect_type.hpp>

namespace traits {
  
//! Use this in your class templates that deal with geometrics on an
//! arbitrary vector type.
//---------------------------------------------------------------------------
#define VECTOR_TRAITS(_vector_type) \
  typedef _vector_type vector_type; \
  typedef ::tra##its::vector_types<vector_type> vector_traits; \
  typedef typename borg::point<vector_type> point_type; \
  typedef typename borg::size<vector_type> size_type; \
  typedef typename borg::rect<vector_type> rect_type;
  
//! Defines vector_type, point_type, size_type, rect_type.
//---------------------------------------------------------------------------
template<class vector> 
struct vector_types
{
  VECTOR_TRAITS(vector)
};

} // namespace traits
//---------------------------------------------------------------------------
#endif // VECTOR_TYPES_HPP
