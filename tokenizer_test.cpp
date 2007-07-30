#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/tokenizer.hpp>
#include <borg/wx.hpp>
//#include <borg/js.hpp>
#include <borg/juce.hpp>
#include <borg/libxml2.hpp>
#include <borg/xerces.hpp>

template<class Traits, class CharT, class OutputCharT>
typename boost::enable_if_c< (sizeof(CharT) == sizeof(OutputCharT)) >::type
test_tokenizer(const borg::string<CharT, Traits> &xstr, std::basic_ostream<OutputCharT> &os)
{
  using namespace boost;
  using namespace borg;
  
  typedef borg::string<CharT, Traits> string_type;
  

  typedef tokenizer< 
    char_delimiters_separator<char>,
    typename string_type::const_iterator,
    string_type
  > tokenizer_type;
  
  tokenizer_type tokseq(xstr);
  
  int i = 0;
  
  for(typename tokenizer_type::iterator it = tokseq.begin();
      it != tokseq.end(); ++it)
  {
    os << ++i << ": " << *it << "\n";
  }
  
  
  
}

int main()
{
  try
  {
    borg::xerces::initialize();
    borg::libxml2::initialize();
    
    #define TEST_STR "this is a  test"
    #define PRINT_EXPR(expr) std::cout << #expr << std::endl; expr;
    
    PRINT_EXPR( test_tokenizer(borg::juce::string(TEST_STR), std::wcout) )
    PRINT_EXPR( test_tokenizer(borg::wx::string(TEST_STR), std::cout) )
    PRINT_EXPR( test_tokenizer(borg::libxml2::string(TEST_STR), std::cout) )
//    PRINT_EXPR( test_tokenizer(borg::xerces::string(TEST_STR), std::wcout) )
    
    
/*    test_tokenizer(borg::xerces::wstring(TEST_STR), std::wcout);
    test_tokenizer(borg::js::string(TEST_STR), std::wcout);*/
    
    borg::libxml2::shutdown();
    borg::xerces::shutdown();
  }
  catch(const std::exception &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  catch(...)
  {
    std::cerr << "Unknown exception" << std::endl;
  }
  
  return 0;
}
