#ifndef BORG_JUCE_ALLOCATOR_HPP
#define BORG_JUCE_ALLOCATOR_HPP

#include <borg/juce/traits.hpp>
#include <borg/allocator/allocator.hpp>
#include <juce/src/juce_core/basics/juce_Memory.h>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class allocator_impl<T, juce::traits>
{
public:
  BORG_ALLOCATOR_TYPES(xerces::traits, T)

  struct category : singleton_allocator_tag
                  , size_tracking_tag
                  , reallocation_tag
  {};
    
  //-------------------------------------------------------------------
  //! Shared (singleton) allocator.
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
    return static_cast<T *>(::juce_malloc(n * sizeof(T)));
  }

  //-------------------------------------------------------------------
  //! Reallocate a bunch of memory.
  //-------------------------------------------------------------------
  static T *
  allocate(const allocator_type &a, size_type n, T *hint)
  {
    return ::juce_realloc(hint, n * sizeof(T));
  }

  //-------------------------------------------------------------------
  //! Deallocate a bunch of memory.
  //-------------------------------------------------------------------
  static void
  deallocate(const allocator_type &a, T *ptr, 
             size_type const n = size_type())
  {
    return ::juce_free(ptr);
  }
  
};
  
namespace juce {
    
template<class T>
struct allocator : public borg::allocator<T, traits>
{
};

typedef borg::allocator<traits::char_type, traits> char_allocator;
typedef borg::allocator<traits::wchar_type, traits> wchar_allocator;
  
} // namespace juce
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_JUCE_ALLOCATOR_HPP
