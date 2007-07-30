#ifndef BORG_ALLOCATOR_INTERFACE_HPP
#define BORG_ALLOCATOR_INTERFACE_HPP

#include <borg/allocator/fwd.hpp>
#include <borg/allocator/types.hpp>

namespace borg {

//---------------------------------------------------------------------------
template<class Derived, class T, class Traits>
struct allocator_interface
{
  //-----------------------------------------------------------------------
  //! Impl class which provides the implementation.
  //-----------------------------------------------------------------------
  typedef allocator_impl<T, Traits> impl;
//  typedef allocator_interface<Derived, T, Traits> iface;
  
  BORG_ALLOCATOR_TYPES(typename impl, T)

  T *
  allocate(size_type n)
  {
    return impl::allocate
      (dereference_cast<Derived>(this), n);
  }
  
  T *
  allocate(size_type n, T *hint)
  {
    return impl::allocate
      (dereference_cast<Derived>(this), n, hint);
  }
  
  void
  deallocate(T *ptr)
  {
    return impl::deallocate
      (dereference_cast<Derived>(this), ptr);
  }
  
  void
  deallocate(T *ptr, size_type n)
  {
    return impl::deallocate
      (dereference_cast<Derived>(this), ptr, n);
  }
  
};

//---------------------------------------------------------------------------

} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_INTERFACE_HPP
