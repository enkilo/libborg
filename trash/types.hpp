#ifndef INTERFACE_TYPES_HPP
#define INTERFACE_TYPES_HPP

#include <types/rect_type.hpp>
#include <types/rgba_type.hpp>

namespace abstract {

#define VECTOR_TRAITS(vectorT...) \
  typedef vectorT vector_type; \
  typedef typename std::point<vector_type> point_type; \
  typedef typename std::size<vector_type> size_type; \
  typedef typename borg::rect<vector_type> rect_type;
  
  //! Defines vector_type, point_type, size_type, rect_type.
  template<typename vectorT>
    struct vector_types
  {
    VECTOR_TRAITS(vectorT);
  };

#define COLOR_TRAITS(colorT...) \
  typedef colorT color_type; \
  typedef typename borg::rgba<color_type> rgba_type;
  
  //! Defines color_type, rgba_type.
  template<typename colorT>
    struct color_types
  {
    COLOR_TRAITS(colorT);
  };
  
/*  template<typename vectorT, typename colorT>
    struct types : public traits::vector_types<vectorT>,
                   public traits::color_types<colorT>
  {};*/
}

#endif // INTERFACE_TYPES_HPP
