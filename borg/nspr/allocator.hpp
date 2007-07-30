#ifndef BORG_NSPR_ALLOCATOR_HPP
#define BORG_NSPR_ALLOCATOR_HPP

#include <borg/nspr/traits.hpp>
#include <borg/allocator/allocator.hpp>
#include <nspr/prmem.h>
#include <boost/mpl/void.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class allocator_impl<T, nspr::traits>
{
public:
  BORG_PP_DEF_TRAITS(nspr::traits)
  BORG_PP_USE_TRAITS(size_type)

  typedef boost::mpl::void_ allocator_type;
    
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
  //! Allocate a bunch of memory.
  //-------------------------------------------------------------------
  static T *
  allocate(const allocator_type &a, size_type n)
  {
    return (T *)::PR_Malloc(n);
  }

  static T *
  allocate(const allocator_type &a, size_type n, T *hint)
  {
    return (T *)::PR_Realloc(hint, n);
  }

  //-------------------------------------------------------------------
  //! Deallocate a bunch of memory.
  //-------------------------------------------------------------------
  static void
  deallocate(const allocator_type &a, T *ptr, 
             size_type const n = size_type())
  {
    ::PR_Free(ptr);
  }
  
};
  
namespace nspr {
    
template<class T>
struct allocator : public borg::allocator<T, traits>
{
  typedef borg::allocator<T, traits> base_type;
  
  allocator() {}
  allocator(base_type const &a) : base_type(a) {}
};

typedef ::borg::allocator<traits::char_type, traits> char_allocator;
  
} // namespace nspr
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_NSPR_ALLOCATOR_HPP
