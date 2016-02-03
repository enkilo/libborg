#ifndef COLOR_TYPES_HPP
#define COLOR_TYPES_HPP

#include <borg/types/rgba_type.hpp>

namespace traits {

//! Use this in your class templates that deal with geometrics on an
//! arbitrary vector type.
//---------------------------------------------------------------------------
#define COLOR_TRAITS(_color_type) \
  typedef _color_type color_type; \
  typedef typename borg::rgba<color_type> rgba_type;
  
//! Defines color_type, rgba_type.
template<class color> struct color_types
{
  COLOR_TRAITS(color)
};
  
} // namespace traits
//---------------------------------------------------------------------------
#endif // COLOR_TYPES_HPP
