#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_wrap_traits.cpp
//! \brief Tests the wrap::wrap_traits class.
//! \svn   $Id: wrapper.hpp 4 2007-03-14 00:48:00Z nexbyte $
//----------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <wrap/wrap_traits.hpp>

using namespace wrap;
using namespace boost;

namespace
{
  struct bigger_than_word
  {
    double a;
    double b;
  };
}

void test_wrap_traits()
{
  // The following must not be mutable:
  BOOST_CHECK(!wrap_traits<const int>::is_mutable);
  BOOST_CHECK(!wrap_traits<int const>::is_mutable);
  BOOST_CHECK(!wrap_traits<int &>::is_mutable);
  BOOST_CHECK(!wrap_traits<int *const>::is_mutable);
  
  // The following must be mutable:
  BOOST_CHECK(wrap_traits<int>::is_mutable);
  BOOST_CHECK(wrap_traits<int *>::is_mutable);
  BOOST_CHECK(wrap_traits<bigger_than_word>::is_mutable);
  
  // The following must match:
  BOOST_CHECK((is_same< wrap_traits<int>::wrap_type, int >::value));
  BOOST_CHECK((is_same< wrap_traits<int &>::wrap_type, reference_wrapper<int> >::value));
  BOOST_CHECK((is_same< wrap_traits<int *>::wrap_type, int * >::value));
  BOOST_CHECK((is_same< wrap_traits<const int>::wrap_type, const int >::value));
  BOOST_CHECK((is_same< wrap_traits<const int &>::wrap_type, reference_wrapper<const int> >::value));
  BOOST_CHECK((is_same< wrap_traits<const int *>::wrap_type, const int * >::value));
  BOOST_CHECK((is_same< wrap_traits<int const>::wrap_type, int const >::value));
  BOOST_CHECK((is_same< wrap_traits<int const&>::wrap_type, reference_wrapper<int const> >::value));
  BOOST_CHECK((is_same< wrap_traits<int const*>::wrap_type, int const* >::value));
  BOOST_CHECK((is_same< wrap_traits<int *const>::wrap_type, int *const>::value));
  
  // These must fit a word:
  BOOST_CHECK((fits_word< wrap_traits<bigger_than_word>::init_type >::value));
  BOOST_CHECK((fits_word< wrap_traits<bigger_than_word>::param_type >::value));
  BOOST_CHECK((fits_word< wrap_traits<bigger_than_word>::unwrap_type >::value));
}
