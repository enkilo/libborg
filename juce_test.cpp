#include <iostream>
#include <string>

#include <borg/juce.hpp>


int main()
{
  using namespace borg;
  
  borg::juce::string str = "test";
  
  str += ' ';
  str += "blah\nhaha";
  
  std::cout << "juce str len: " << str.length() << std::endl;
  
  std::cout << std::string(str.begin(), str.end()) << std::endl;
  
  return 0;
}
