#ifndef BORG_UTIL_ARRAY_FWD_HPP
#define BORG_UTIL_ARRAY_FWD_HPP

#include <borg/util/basic_string_fwd.hpp>

namespace borg {
namespace util {

//----------------------------------------------------------------------------
//! Array template. (Defaults to array of strings).
//----------------------------------------------------------------------------
template< class ValueT = stdcxx::basic_string<char> >
class array;

} // namespace util
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_ARRAY_FWD_HPP
