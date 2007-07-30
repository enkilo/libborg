#ifndef BORG_XERCES_ALLOCATOR_HPP
#define BORG_XERCES_ALLOCATOR_HPP

#include <borg/xerces/traits.hpp>
#include <borg/allocator/allocator.hpp>
#include <xercesc/internal/MemoryManagerImpl.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class allocator_impl<T, xerces::traits>
{
public:
  BORG_ALLOCATOR_TYPES(xerces::traits, T)

  struct category : singleton_allocator_tag
                  , reentrant_allocator_tag 
                  , size_tracking_tag
  {};
    
  //-------------------------------------------------------------------
  //! Create a new allocator.
  //-------------------------------------------------------------------
  static allocator_type
  create()
  {
    using namespace ::XERCES_CPP_NAMESPACE;
    
    MemoryManagerImpl *mman = new MemoryManagerImpl();

    std::cout << "new memory manager: " << mman << std::endl;
    
    return mman;
  }
  
  //-------------------------------------------------------------------
  //! Destroy allocator.
  //-------------------------------------------------------------------
  static void
  destroy(allocator_type &a)
  {
    using namespace ::XERCES_CPP_NAMESPACE;
    
    std::cout << "destroy: " << (void *)a << std::endl;
    
    delete a;
    a = 0;
  }
  
  //-------------------------------------------------------------------
  //! Shared (singleton) allocator.
  //-------------------------------------------------------------------
  static allocator_type
  singleton()
  {
    using namespace ::XERCES_CPP_NAMESPACE;
    
    allocator_type a = 0;
    
    if(XMLPlatformUtils::fgMemoryManager == 0)
    {
      a = new MemoryManagerImpl();

      XMLPlatformUtils::fgMemoryManager = a;
      
//      std::cout << "new singleton memory manager: " << a << std::endl;
    }
//    else
//      std::cout << "existing singleton memory manager: " << XMLPlatformUtils::fgMemoryManager << std::endl;

    if(a)
      return a;

    return dynamic_cast<MemoryManagerImpl *>(XMLPlatformUtils::fgMemoryManager);
  }
    
  //-------------------------------------------------------------------
  //! Allocate a bunch of memory.
  //-------------------------------------------------------------------
  static T *
  allocate(const allocator_type &a, size_type n)
  {
    return (T *)a->allocate(n * sizeof(T));
  }

  //-------------------------------------------------------------------
  //! Deallocate a bunch of memory.
  //-------------------------------------------------------------------
  static void
  deallocate(const allocator_type &a, T *ptr, 
             size_type const n = size_type())
  {
    return a->deallocate(ptr);
  }
  
};
  
namespace xerces {
    
template<class T>
struct allocator : public borg::allocator<T, traits>
{
};

typedef borg::allocator<traits::char_type, traits> char_allocator;
typedef borg::allocator<traits::wchar_type, traits> wchar_allocator;
  
} // namespace xerces
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_ALLOCATOR_HPP
