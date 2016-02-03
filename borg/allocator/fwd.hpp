#ifndef BORG_ALLOCATOR_FWD_HPP
#define BORG_ALLOCATOR_FWD_HPP

namespace borg {

//---------------------------------------------------------------------------
//! Forward declare allocator classes.
//---------------------------------------------------------------------------
template<class T, class Traits>
struct allocator_impl;

template<class Derived, class T, class Traits>
struct allocator_interface;

//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_FWD_HPP
