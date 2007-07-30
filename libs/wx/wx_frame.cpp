#include <borg/wx.hpp>
#include <borg/tk/impl.hpp>
#include <borg/wx/frame.hpp>

#define EVENTS_CLASS borg::tk::frame< ::borg::wx::traits >
#define EVENTS_BASE wxFrame

#include <borg/wx/events.ipp>

namespace borg {
namespace tk {
  
frame< ::borg::wx::traits >::~frame()
{
}

} // namespace tk
} // namespace borg
  
  
