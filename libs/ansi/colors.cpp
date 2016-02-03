#include <borg/color/rgb.hpp>

// TODO: separate into 1 file per struct and the linker will account 
//       for the "you only pay for what you use" philosophy.

namespace borg {
  
const rgb_value<bool> ansi_colors[16] =
{
  { 0 }, // 0 = black
  { 1 }, // 1 = red
  { 2 }, // 2 = green
  { 3 }, // 3 = yellow
  { 4 }, // 4 = blue
  { 5 }, // 5 = magenta
  { 6 }, // 6 = cyan
  { 7 }, // 7 = white
};
  
} // namespace borg
