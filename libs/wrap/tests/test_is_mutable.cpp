#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_is_mutable.cpp
//! \brief Tests the wrap::is_mutable metafunction.
//! \svn   $Id: wrapper.hpp 4 2007-03-14 00:48:00Z nexbyte $
//----------------------------------------------------------------------------
#include <boost/test/unit_test.hpp>
#include <wrap/wrap_traits.hpp>

using namespace wrap;
using namespace boost;

namespace
{
  // struct with trivial assign
  struct trivial_assign_struct
  {
    double a;
    double b;
  };

  struct assign_operator_struct
  {
    double a;
    double b;
    
    assign_operator_struct &operator=(const assign_operator_struct &x)
    {
      a = x.a;
      b = x.b;
      return *this;
    }
  };
}

namespace boost
{
  template<>
    struct has_trivial_assign<trivial_assign_struct>
  {
    BOOST_STATIC_CONSTANT(bool, value = true);
  };
}

void test_is_mutable()
{
  trivial_assign_struct a;
  trivial_assign_struct b;
  
  b = a;
  
  // The following must not be mutable:
  BOOST_CHECK((!is_mutable<const int>::value));
  BOOST_CHECK((!is_mutable<int const>::value));
  BOOST_CHECK((!is_mutable<int &>::value));
  BOOST_CHECK((!is_mutable<int *const>::value));
  BOOST_CHECK((!is_mutable<const trivial_assign_struct>::value));
  
  // The following must be trivially mutable:
  BOOST_CHECK((is_mutable<int, true>::value));
  BOOST_CHECK((is_mutable<int *, true>::value));
  BOOST_CHECK((is_mutable<trivial_assign_struct, true>::value));
  
  // The following must not be trivially mutable:
  BOOST_CHECK((!is_mutable<assign_operator_struct, true>::value));
  
  // The following must be mutable:
  BOOST_CHECK((is_mutable<assign_operator_struct>::value));
}
