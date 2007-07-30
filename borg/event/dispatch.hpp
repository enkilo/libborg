#ifndef BORG_EVENT_DISPATCH_HPP
#define BORG_EVENT_DISPATCH_HPP

#include <borg/event/signal.hpp>

namespace borg {
namespace event {
namespace dispatch {

//! Position changes.
template<class toolkit>
  struct move
{
  typedef toolkit tk_type;
  signal<event::move, tk_type> onmove;
};

//! Size changes.
template<class toolkit>
  struct resize
{
  typedef toolkit tk_type;
  signal<event::resize, tk_type> onresize;
};

//! Button state changes.
template<class toolkit>
  struct mousebutton
{
  typedef toolkit tk_type;
  signal<event::mousedown, tk_type> onmousedown;
  signal<event::mouseup, tk_type> onmouseup;
};

//! Mouse position changes.
template<class toolkit>
  struct mousemove
{
  typedef toolkit tk_type;
  signal<event::mousemove, tk_type> onmousemove;
};

//! Mouse context changes.
template<class toolkit>
  struct mousecontext
{
  typedef toolkit tk_type;
  signal<event::mouseenter, tk_type> onmouseenter;
  signal<event::mouseleave, tk_type> onmouseleave;
};

//! All mouse events.
template<class toolkit>
  struct mouse : public mousebutton<toolkit>,
                 public mousemove<toolkit>, 
                 public mousecontext<toolkit>
{
  typedef toolkit tk_type;
};

//! Loose focus.
template<class toolkit>
  struct focusloose
{
  typedef toolkit tk_type;
  signal<event::focusloose, tk_type> onfocusloose;
};

//! Gain focus.
template<class toolkit>
  struct focusgain
{
  typedef toolkit tk_type;
  signal<event::focusgain, tk_type> onfocusgain;
};

//! All focus events.
template<class toolkit>
  struct focus : public focusloose<toolkit>,
                 public focusgain<toolkit> 
{
  typedef toolkit tk_type;
};

//! View events.
template<class toolkit>
  struct widget : public move<toolkit>, 
                  public resize<toolkit>,
                  public mouse<toolkit>,
                  public focus<toolkit>
{
  typedef toolkit tk_type;
  signal<event::redraw, tk_type> onredraw;
};

} // namespace dispatch
} // namespace event
} // namespace borg

#endif /* BORG_EVENT_DISPATCH_HPP */
