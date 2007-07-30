#ifndef DIMENSION_TYPE_HPP
#define DIMENSION_TYPE_HPP

#include <boost/static_assert.hpp>
#include <borg/magnitude.hpp>

namespace types {

enum dimension
{
  horizontal = 0x01,
  vertical = 0x02,
  both = 0x03
};

} // namespace std
#endif // DIMENSION_TYPE_HPP
