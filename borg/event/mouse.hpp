#ifndef BORG_EVENT_MOUSE_HPP
#define BORG_EVENT_MOUSE_HPP

namespace borg { 
namespace event { 
namespace mouse {

  enum button
  {
    nobutton = 0,
    lbutton = 1,
    rbutton = 2,
    mbutton = 4
  };

  typedef int buttons;
} // namespace mouse
} // namespace event
} // namespace borg

#endif /* BORG_EVENT_MOUSE_HPP */
