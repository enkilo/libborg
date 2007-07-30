#ifndef BORG_ALLOCATOR_CONCEPTS_HPP
#define BORG_ALLOCATOR_CONCEPTS_HPP

#include <boost/concept_archetype.hpp>

namespace borg {

//----------------------------------------------------------------------------
template<class Allocator>

struct AllocatorConcept
{
  typedef Allocator allocator_type;
    
  void constraints()
  {
    allocator_type &a = boost::static_object<allocator_type>::get();

    // Must have at least a value_type allocate(size_t) method.
    typename allocator_type::value_type *vptr = a.allocate(10);
    
    // Must have at least a void deallocate(value_type *) method.
    a.deallocate(vptr, 10);
    
    // Check const stuff.....
    const_constraints();
  }
  
  void const_constraints()
  {
    allocator_type const &a = boost::static_object<allocator_type const>::get();
    
    // Must be copy-constructible.
    allocator_type copy = a;
  }
};


} // end of namespace borg
//----------------------------------------------------------------------------
#endif //ndef BORG_ALLOCATOR_CONCEPTS_HPP
