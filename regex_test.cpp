#include <iostream>
#include <sstream>
#include <algorithm>
#include <borg/regex.hpp>
#include <borg/wx.hpp>
//#include <borg/js.hpp>
#include <borg/juce.hpp>
#include <borg/libxml2.hpp>
#include <borg/xerces.hpp>

template<class Traits, class CharT, class OutputCharT>
typename boost::enable_if_c< (sizeof(CharT) == sizeof(OutputCharT)) >::type
test_regex(const borg::string<CharT, Traits> &xstr, std::basic_ostream<OutputCharT> &os)
{
  using namespace boost;
  using namespace borg;
  
  typedef string<CharT, Traits> string_type;
  typedef CharT char_type;
  typedef OutputCharT ochar_type;

  basic_regex<char_type> expr(xstr.begin(), xstr.end());

  std::ostream_iterator<char_type, ochar_type> oi(os);
  string_type str = "well, 23 is a number\n";
  string_type replace = "twenty-three";

  oi = regex_replace(oi, str, expr, replace.c_str(), match_default);

  string_type number = "31337";
  
  if(regex_match(number, expr, match_default))
  {
    oi = std::copy(number.begin(), number.end(), oi);
    
    *oi++ = '\n';
  //  os << number << " matches " << expr << std::endl;
  }
  
  
  os.flush();
}

int main()
{
  try
  {
    borg::xerces::initialize();

    #define PRINT_EXPR(expr) std::cout << #expr << std::endl; expr;
    
    PRINT_EXPR( test_regex(borg::juce::string("[0-9]+"), std::wcout) )
    PRINT_EXPR( test_regex(borg::xerces::string("[0-9]+"), std::wcout) )
    PRINT_EXPR( test_regex(borg::string<char, borg::libxml2::traits>("[0-9]+"), std::cout) )
    PRINT_EXPR( test_regex(borg::wx::string("[0-9]+"), std::cout) )
/*    test_regex(borg::js::string("[0-9]+"), std::wcout);*/
    
    borg::xerces::shutdown();
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  
  return 0;
}
