#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_wrap_as_member.hpp
//! \brief Tests the wrap::wrap_as_member class.
//! \svn   $Id: wrapper.hpp 4 2007-03-14 00:48:00Z nexbyte $
//----------------------------------------------------------------------------

#ifndef TEST_EXPLICIT_WRAPPER_HPP
#define TEST_EXPLICIT_WRAPPER_HPP

#include <wrap/wrap_as_member.hpp>

using namespace wrap;

//! Test non-mutable wrappers.
template<typename T>
  static void test_nonmutable_wrap_as_member
    (typename remove_reference<T>::type wrapee, bool is_mutable = false)
{
  // Define wrapee and wrapper type.
  typedef T wrap_type;
  typedef wrap_as_member<T> wrapper_type;
  
  // Check the types:
  BOOST_CHECK((is_same<typename wrapper_type::wrap_type, typename wrap_reference<wrap_type>::type>::value));
  BOOST_CHECK((fits_word<typename wrapper_type::init_type>::value));
  BOOST_CHECK((fits_word<typename wrapper_type::unwrap_type>::value));
  
  // Check mutability.
  if(is_mutable == false)
  {
    BOOST_CHECK(wrapper_type::is_mutable == false);
  }
  
  // The wrapper must have the same size as the wrapee.
  BOOST_CHECK_EQUAL(sizeof(wrapper_type), sizeof(wrap_type));
  
  // Instantiate a wrapper.
  wrapper_type wrapper(wrapee);
  
  // Check runtime behaviour:
  wrap_type wrapped = wrapper.get();
  BOOST_CHECK(!::memcmp(&wrapped, &wrapee, sizeof(wrap_type)));
}

//! Test mutable wrappers. Be sure to provide two different arguments.
template<typename T>
  static void test_mutable_wrap_as_member
    (typename remove_reference<T>::type wrapee1,
     typename remove_reference<T>::type wrapee2)
{
  // Call the test for non-mutable wrappers.
  test_nonmutable_wrap_as_member<T>(wrapee1, true);
  
  // Define wrapee and wrapper type.
  typedef T wrap_type;
  typedef wrap_as_member<T> wrapper_type;
  
  // Check the parameter type:
  BOOST_CHECK((fits_word<typename wrapper_type::param_type>::value));
  
  // Check mutability.
  BOOST_CHECK(wrapper_type::is_mutable);
  
  // Instantiate a wrapper.
  wrap_as_member<wrap_type> wrapper(wrapee1);
  
  // Check runtime behaviour:
  wrapper.set(wrapee2);

  wrap_type wrapped = wrapper.get();
  BOOST_CHECK(!::memcmp(&wrapped, &wrapee2, sizeof(wrap_type)));
  BOOST_CHECK( ::memcmp(&wrapped, &wrapee1, sizeof(wrap_type)));
}

#endif //ndef TEST_EXPLICIT_WRAPPER_HPP
