#ifndef BORG_WX_HPP
#define BORG_WX_HPP

#include <wx/init.h>

#include <borg/wx/traits.hpp>
#include <borg/wx/string.hpp>
#include <borg/wx/array.hpp>
#include <borg/wx/application.hpp>

namespace borg {
namespace wx {

static const traits::id_type         default_id          = -1;
static const traits::point_type     &default_position    = wxDefaultPosition;
static const traits::size_type      &default_size        = wxDefaultSize;
static const traits::validator_type &default_validator   = wxDefaultValidator;
static const traits::style_type      default_frame_style = wxDEFAULT_FRAME_STYLE;

//----------------------------------------------------------------------------
inline static
void initialize()
{
  wxInitialize();
}
  
//---------------------------------------------------------------------------
inline static
void terminate()
{
  wxUninitialize();
}
  
//---------------------------------------------------------------------------

} // namespace wx
} // namespace borg

#endif //ndef BORG_WX_HPP
