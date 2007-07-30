#ifndef ALIGNMENT_TYPE_HPP
#define ALIGNMENT_TYPE_HPP

namespace types {

enum
{
  align_left       = 0x01,
  align_right      = 0x02,
  align_center     = 0x03,
  align_horizontal = 0x03,
  align_top        = 0x04,
  align_bottom     = 0x08,
  align_middle     = 0x0c,
  align_vertical   = 0x0c,
};

} // namespace types
#endif // ALIGNMENT_TYPE_HPP
