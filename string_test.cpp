#include <iostream>

#include <borg/color/rgb.hpp>
#include <boost/function.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <borg/util/string.hpp>
#include <borg/xerces.hpp>
#include <borg/string/tests.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>

#include <borg/wx/string.hpp>
#include <borg/libxml2/string.hpp>
#include <borg/js/string.hpp>
#include <borg/juce/string.hpp>

using boost::unit_test::test_suite;

#define PRINT_EXPR(expr) std::cout << #expr ": " << (expr) << std::endl;

test_suite *init_unit_test_suite(int , char *[])
{
  test_suite *test = BOOST_TEST_SUITE("string test suite");

  using namespace borg;
/*
  test->add(BOOST_TEST_CASE_TEMPLATE(test_string, borg::stdcxx::string));
  test->add(BOOST_TEST_CASE_TEMPLATE(test_string, borg::wx::string));
  test->add(BOOST_TEST_CASE_TEMPLATE(test_string, borg::juce::string));
  test->add(BOOST_TEST_CASE_TEMPLATE(test_string, borg::xerces::string));
  test->add(BOOST_TEST_CASE_TEMPLATE(test_string, borg::libxml2::string));
*/
//  test->add( BOOST_TEST_CASE( test_string::run< borg::stdcxx::string >  ) );

  test->add( BOOST_TEST_CASE( test_string::run< borg::wx::string >      ) );
  test->add( BOOST_TEST_CASE( test_string::run< borg::juce::string >    ) );
  test->add( BOOST_TEST_CASE( test_string::run< borg::xerces::string >  ) );
  test->add( BOOST_TEST_CASE( test_string::run< borg::libxml2::string > ) );
  test->add( BOOST_TEST_CASE( test_string::run< borg::js::string >      ) );

/*  PRINT_EXPR( sizeof(borg::stdcxx::string) )
  PRINT_EXPR( sizeof(borg::wx::string) )
  PRINT_EXPR( sizeof(borg::juce::string) )
  PRINT_EXPR( sizeof(borg::xerces::string) )
  PRINT_EXPR( sizeof(borg::libxml2::string) ) */

  return test;
}
