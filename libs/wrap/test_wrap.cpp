#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_wrap.cpp
//! \brief Tests the wrap library.
//! \svn   $Id: test_wrap.cpp 66 2007-04-03 17:06:06Z nexbyte $
//----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>

using boost::unit_test::test_suite;

// Test prototypes:
void test_is_mutable();
void test_wrap_traits();
void test_wrap_as_member();
void test_wrapper();
void test_pointer();

// Add tests for the wrap library.
void add_wrap_tests(test_suite *test)
{ 
  test->add(BOOST_TEST_CASE(test_is_mutable));
  test->add(BOOST_TEST_CASE(test_wrap_traits));
  test->add(BOOST_TEST_CASE(test_wrap_as_member));
  test->add(BOOST_TEST_CASE(test_wrapper));
  test->add(BOOST_TEST_CASE(test_pointer));
}
