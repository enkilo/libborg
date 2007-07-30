#warning "obsolete"
//----------------------------------------------------------------------------
//! \file  test_wrapper.cpp
//! \brief Tests the wrap::wrapper class.
//! \svn   $Id: wrapper.hpp 4 2007-03-14 00:48:00Z nexbyte $
//----------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include <boost/static_assert.hpp>
#include <wrap/pointer.hpp>
#include <iostream>

using namespace wrap;
using namespace boost;

namespace
{
  struct bigger_than_word
  {
    double a;
    double b;
  };
  
  class some_object
  {
    bigger_than_word m;
    
  public:
    some_object(double a, double b)
    {
      m.a = a;
      m.b = b;
    }
    
    double sum() const
    {
      return m.a + m.b;
    }
  };
}

void test_pointer()
{
  pointer<int> ptr = 0;
  
  if(!ptr)
    ++ptr;
  
  ptr++;
  
  std::cout << ptr.get() << std::endl;
  
  int a = 666;
  pointer<int> intptr = &a;
  
  std::cout << *intptr << std::endl;
  
  bigger_than_word st;
  st.a = 3.141592653589793;
  st.b = 4.5;
  pointer<bigger_than_word> stptr = &st;
  
  
  std::cout << stptr->a << std::endl;
//  std::cout << stptr.get_pointer() << std::endl;
  
  std::cout << "p" << boost::is_convertible<int *, int &>::value << std::endl;
}
