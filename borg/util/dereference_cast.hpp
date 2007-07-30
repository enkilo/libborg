#ifndef BORG_CRTP_CAST_HPP
#define BORG_CRTP_CAST_HPP

namespace borg {

//----------------------------------------------------------------------------
template<typename Derived, typename Facade>
static inline
Derived &
dereference_cast(Facade *ptr)
{
  return *static_cast<Derived *>(ptr);
}
  
//---------------------------------------------------------------------------

}// namespace borg

#endif //ndef BORG_CRTP_CAST_HPP
