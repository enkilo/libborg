#ifndef BORG_JS_ALLOCATOR_HPP
#define BORG_JS_ALLOCATOR_HPP

#include <borg/js/context.hpp>
#include <borg/allocator/allocator.hpp>
#include <js/jsapi.h>

namespace borg {

//----------------------------------------------------------------------------
template<class T>
class allocator_impl<T, js::traits>
{
public:
  BORG_PP_DEF_TRAITS(js::traits)
  BORG_PP_ALIAS_TYPEDEF(js::traits, context, allocator)
  BORG_PP_USE_TRAITS(context_type)
  BORG_PP_USE_TRAITS(runtime_type)
  BORG_PP_USE_TRAITS(size_type)
    
  struct category : reentrant_allocator_tag
                  , size_tracking_tag
                  , reallocation_tag
  {};
    
  //-------------------------------------------------------------------
  static allocator_type 
  singleton()
  {
    return script::context_impl<traits_type>::shared();
  }
  
  //-------------------------------------------------------------------
  //! Create an allocator.
  //-------------------------------------------------------------------
  static allocator_type
  create(runtime_type const &rt = script::runtime_impl<traits_type>::shared(),
//  create(runtime_type const &rt = js::runtime::shared(),
         size_type stack_chunk_size = 8192)
  {
    return ::JS_NewContext(rt, stack_chunk_size);
  }
    
  //-------------------------------------------------------------------
  //! Destroy an allocator.
  //-------------------------------------------------------------------
  static void
  destroy(allocator_type const &a)
  {
    ::JS_DestroyContext(a);
  }
    
  //-------------------------------------------------------------------
  //! Allocate a bunch of memory.
  //-------------------------------------------------------------------
  static T *
  allocate(const allocator_type &a, size_type n)
  {
    return (T *)::JS_malloc(a, n);
  }

  static T *
  allocate(const allocator_type &a, size_type n, T *hint)
  {
    return (T *)::JS_realloc(a, hint, n);
  }

  //-------------------------------------------------------------------
  //! Deallocate a bunch of memory.
  //-------------------------------------------------------------------
  static void
  deallocate(const allocator_type &a, T *ptr, 
             size_type const n = size_type())
  {
    ::JS_free(a, ptr);
  }
  
};
  
namespace js {
    
template<class T>
struct allocator : public borg::allocator<T, traits>
{
  typedef borg::allocator<T, traits> base_type;
  
  allocator() {}
  allocator(base_type const &a) : base_type(a) {}
};

typedef ::borg::allocator<traits::char_type, traits> char_allocator;
  
} // namespace js
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_JS_ALLOCATOR_HPP
