#ifndef BORG_APR_ALLOCATOR_HPP
#define BORG_APR_ALLOCATOR_HPP

#include <borg/apr/traits.hpp>
#include <borg/allocator/allocator.hpp>
#include <apr_allocator.h>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class allocator_impl<T, apr::traits>
{
public:
  BORG_ALLOCATOR_TYPES(apr::traits, T)

  struct category : reentrant_allocator_tag
                  , size_tracking_tag
  {};
    
  //-------------------------------------------------------------------
  static allocator_type &
  singleton()
  {
    static allocator_type a;

    if(!a)
      ::apr_allocator_create(&a);
    
    return a;
  }
  
  //-------------------------------------------------------------------
  //! Create an allocator.
  //-------------------------------------------------------------------
  static allocator_type
  create()
  {
    allocator_type ret;
    ::apr_allocator_create(&ret);
    return ret;
  }
    
  //-------------------------------------------------------------------
  //! Destroy an allocator.
  //-------------------------------------------------------------------
  static void
  destroy(allocator_type const &a)
  {
    ::apr_allocator_destroy(a);
  }
    
  //-------------------------------------------------------------------
  //! Allocate a bunch of memory.
  //-------------------------------------------------------------------
  static T *
  allocate(const allocator_type &a, size_type n)
  {
    ::apr_memnode_t *mem = ::apr_allocator_alloc(a, n * sizeof(T));
    return (T *)&mem[1];
  }

  //-------------------------------------------------------------------
  //! Deallocate a bunch of memory.
  //-------------------------------------------------------------------
  static void
  deallocate(const allocator_type &a, T *ptr, 
             size_type const n = size_type())
  {
    ::apr_memnode_t *mem = (::apr_memnode_t *)ptr;
    return ::apr_allocator_free(a, &mem[-1]);
  }
  
};
  
namespace apr {
    
template<class T>
struct allocator : public borg::allocator<T, traits>
{
  typedef borg::allocator<T, traits> base_type;
  
  allocator() {}
  allocator(base_type const &a) : base_type(a) {}
};

typedef ::borg::allocator<traits::char_type, traits> char_allocator;
  
} // namespace apr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_APR_ALLOCATOR_HPP
