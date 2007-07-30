#include <iostream>
#include "expr.hpp"


extern "C" void test()
{
  operation::negate<int> neg1;
  
  std::cout << neg1.apply(1) << std::endl;
  
}

