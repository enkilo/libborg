#ifndef BORG_UTIL_STRING_HPP
#define BORG_UTIL_STRING_HPP

#include <borg/util/basic_string_fwd.hpp>

namespace borg {
namespace stdcxx {

//----------------------------------------------------------------------------
// Forward declarations
//----------------------------------------------------------------------------
#ifndef BORG_STRING_FWD
#define BORG_STRING_FWD
  
//! Normal character (1-byte) strings.
typedef basic_string<char> string;
    
#endif //ndef BORG_STRING_FWD
  
} // namespace stdcxx
} // namespace borg

//----------------------------------------------------------------------------
// Now include the implementation.
//----------------------------------------------------------------------------
#include <borg/util/basic_string.hpp>

//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_STRING_HPP
