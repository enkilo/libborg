#ifndef BORG_EVENT_ID_HPP
#define BORG_EVENT_ID_HPP

#include <boost/mpl/int.hpp>

namespace borg {
namespace event {

using namespace boost::mpl;
  
typedef int_<1> move;
typedef int_<2> resize;
typedef int_<3> mouseup;
typedef int_<4> mousedown;
typedef int_<5> mousedclick;
typedef int_<6> mousemove;
typedef int_<7> mouseenter;
typedef int_<8> mouseleave;
typedef int_<9> redraw;
typedef int_<10> focusloose;
typedef int_<11> focusgain;

} // namespace event
} // namespace borg

#endif // BORG_EVENT_ID_HPP
