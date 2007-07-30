#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test.cpp
//! \brief Main program of the libaudium unit test suite.
//! \svn   $Id: test.cpp 66 2007-04-03 17:06:06Z nexbyte $
//----------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>
#include <iostream>

using namespace std;
using boost::unit_test::test_suite;

void add_wrap_tests(test_suite *test);

test_suite *init_unit_test_suite(int , char *[])
{
  cout << "Test started..." << endl;
  
  test_suite *test = BOOST_TEST_SUITE("libaudium master test suite");
  add_wrap_tests(test);  
  return test;
}
