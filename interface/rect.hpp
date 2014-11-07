#warning "obsolete"
#ifndef _cxx_abstract_rect_
#define _cxx_abstract_rect_

#include <stdint.h>

namespace abstract {

//! Point forward declaration.
template<typename coord_type> 
  struct point;

//! Generic rectangle.
template<typename coord_type> 
  struct rect
{
};

//! Lets us write (<<) rects into character stream.
template<typename coord_type>
  template<typename char_type, class traits_class>
  std::basic_ostream<char_type, traits_class> &
  operator<<(std::basic_ostream<char_type, traits_class> &os, const rect<coord_type> &r)
  {
    std::basic_ostringstream<char_type, traits_class> s;

    s.flags(os.flags() | std::ios_base::hex);
    s.imbue(os.getloc());
    s.precision(os.precision());

    s << '[' << r.get_x() << ',' << r.get_y() << '|' << r.get_width() << 'x' << r.get_height() << ']';

    return os << s.str();
  }

#endif // _cxx_abstract_rect_
