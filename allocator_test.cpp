#define APR_DECLARE_STATIC 1
#define APU_DECLARE_STATIC 1

#include <iostream>

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>

#define PRINT_EXPR(expr) std::cout << #expr ": " << (expr) << std::endl;

#include <borg/allocator/tests.hpp>
#include <borg/libxml2/allocator.hpp>
#include <borg/xerces.hpp>
#include <borg/xerces/allocator.hpp>
#include <borg/apr/allocator.hpp>
#include <borg/js/allocator.hpp>
#include <borg/juce/allocator.hpp>
#include <borg/nspr/allocator.hpp>

using boost::unit_test::test_suite;

test_suite *init_unit_test_suite(int , char *[])
{
  test_suite *test = BOOST_TEST_SUITE("allocator test suite");

  using namespace borg;

  borg::xerces::initialize();
  
  
  typedef borg::allocator<char, borg::xerces::traits> alloc_type;
  
  alloc_type a1 = alloc_type::singleton();
  alloc_type a2 = alloc_type::singleton();
  alloc_type a3;
  
  
  PRINT_EXPR( sizeof(alloc_type::impl::allocator_type) )
  PRINT_EXPR( sizeof(alloc_type) )

  char *ptr3 = a3.allocate(10);
  a3.deallocate(ptr3);
  
  char *ptr1 = a1.allocate(10);
  a1.deallocate(ptr1);
  
  char *ptr2 = a2.allocate(10);
  a2.deallocate(ptr2);
  
  PRINT_EXPR( sizeof(std::allocator<char>) )
  
  test->add( BOOST_TEST_CASE( test_allocator::run< std::allocator<char> >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< libxml2::wchar_allocator >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< borg::xerces::allocator<XMLCh> >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< borg::juce::allocator<juce_wchar> >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< apr::allocator<char> >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< js::allocator<jschar> >  ) );
  test->add( BOOST_TEST_CASE( test_allocator::run< nspr::allocator<char> >  ) );

  borg::xerces::shutdown();
  
  return test;
}
