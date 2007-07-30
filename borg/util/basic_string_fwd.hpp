#ifndef BORG_BASIC_STRING_FWD_HPP
#define BORG_BASIC_STRING_FWD_HPP

#include <string>

namespace borg {
namespace stdcxx {

using std::char_traits;
using std::allocator;
  
//----------------------------------------------------------------------------
//! Basic string template (supports arbitrary character types).
//----------------------------------------------------------------------------
template< class CharT, class Traits = char_traits<CharT>, 
          class Alloc = allocator<CharT> >
class basic_string;

} // namespace stdcxx
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_BASIC_STRING_FWD_HPP
