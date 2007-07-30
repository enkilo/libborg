#ifndef BORG_LIBXML2_ALLOCATOR_HPP
#define BORG_LIBXML2_ALLOCATOR_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/allocator/allocator.hpp>
#include <borg/util/dummy.hpp>

namespace borg {

//----------------------------------------------------------------------------
//! Implementation of allocator on top of xmlMalloc, xmlRealloc, xmlFree.
//----------------------------------------------------------------------------
template<class T>
struct allocator_impl<T, libxml2::traits>
{
  typedef ::size_t size_type;
  typedef dummy    allocator_type;

  struct category : singleton_allocator_tag
                  , size_tracking_tag
                  , reallocation_tag
  {};
  
  //-------------------------------------------------------------------
  static allocator_type
  singleton()
  {
    return allocator_type();
  }

  //-------------------------------------------------------------------
  //! Allocate \a n items of type T.
  //-------------------------------------------------------------------
  static T *
  allocate(allocator_type const &a, size_type const n)
  {
    return static_cast<T *>(xmlMalloc(n * sizeof(T)));
  }

  static T *
  allocate(allocator_type const &a, size_type const n, T *hint)
  {
    return static_cast<T *>(xmlRealloc(hint, n * sizeof(T)));
  }

  //-------------------------------------------------------------------
  //! Deallocate previously allocated memory.
  //-------------------------------------------------------------------
  static void
  deallocate(allocator_type const &a, T *const ptr, size_type const n = -1)
  {
    xmlFree(static_cast<void *>(ptr));
  }
};

namespace libxml2 {
  
template<class T>
class allocator : public borg::allocator<T, traits>
{
public:
  typedef borg::allocator<T, traits> base;
  
  allocator() {}
  allocator(base const &a) : base(a) {}  
};

typedef borg::allocator<traits::wchar_type, traits> char_allocator;
typedef borg::allocator<traits::wchar_type, traits> wchar_allocator;
  
  
} // namespace libxml2
} // namespace borg


//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_ALLOCATOR_HPP
