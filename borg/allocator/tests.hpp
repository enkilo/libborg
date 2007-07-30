#ifndef BORG_MEMORY_TESTS_HPP
#define BORG_MEMORY_TESTS_HPP

#include <boost/foreach.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/concept_check.hpp>
#include <borg/preproc.hpp>
#include <borg/allocator/allocator.hpp>
#include <borg/allocator/concepts.hpp>
#include <string>

namespace borg {

//---------------------------------------------------------------------------
BOOST_TEST_CASE_TEMPLATE_FUNCTION( test_allocator, AllocatorT )
{
  // First check the concept...
  boost::function_requires< AllocatorConcept<AllocatorT> >();
  
  // Declare some types...
  typedef AllocatorT allocator_type;
  BORG_PP_USE_TYPE(typename AllocatorT, value_type)
  
  // Declare some variables...
  AllocatorT alloc;
  typename AllocatorT::size_type nbytes = 123;
  typename AllocatorT::value_type *vptr;
  
  // Checking whether allocation works...
  vptr = alloc.allocate(nbytes);
  
  BOOST_CHECK( vptr );
  
  AllocatorT alloc2 = alloc;
  
  // Checking access....
  vptr[0] = 'X';
  vptr[nbytes - 1] = 'Y';
  
  BOOST_CHECK_EQUAL( vptr[0], 'X' );
  BOOST_CHECK_EQUAL( vptr[nbytes - 1], 'Y' );
  
  // Checking whether deallocation works...
  alloc2.deallocate(vptr, nbytes);
  
  // Checking whether we can implement a string upon it.
  using namespace std;
  
  value_type init[] = { 't', 'e', 's', 't', 0 };

  basic_string< value_type, char_traits<value_type>, AllocatorT > str = init;
  
  str += ' ';

  value_type add[] = { 'b', 'l', 'a', 'h', 0 };

  str.append(add);
  
  BOOST_CHECK_EQUAL( str.length(), 9 );
  
  PRINT_EXPR(sizeof(basic_string< value_type, char_traits<value_type>, AllocatorT >))
    
  // Print capabilities...
  PRINT_EXPR( borg::allocator_traits< AllocatorT >::is_singleton )
  PRINT_EXPR( borg::allocator_traits< AllocatorT >::is_reentrant )
  PRINT_EXPR( borg::allocator_traits< AllocatorT >::supports_realloc )
          
   
}

//---------------------------------------------------------------------------

} // namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef BORG_MEMORY_TESTS_HPP
