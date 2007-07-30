#ifndef BORG_WX_WRAPPERS_HPP
#define BORG_WX_WRAPPERS_HPP

#include <borg/tk/wrappers.hpp>

namespace borg {
namespace wx {
  
typedef tk::dc_wrapper<traits> dc_wrapper;
typedef tk::widget_wrapper<traits> widget_wrapper;
typedef tk::frame_wrapper<traits> frame_wrapper;
typedef tk::bitmap_wrapper<traits> bitmap_wrapper;

} // namespace wx
} // namespace borg

//---------------------------------------------------------------------------
#endif // BORG_WX_WRAPPERS_HPP
