#ifndef UPDATE_MODE_HPP
#define UPDATE_MODE_HPP

namespace types {

enum update_mode
{
  update_none = 0x00,
  update_recurse = 0x01,
  update_fromidle = 0x02
};

} // namespace types
#endif // UPDATE_MODE_HPP
