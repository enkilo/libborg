#ifndef BORG_STRING_TESTS_HPP
#define BORG_STRING_TESTS_HPP

#include <boost/foreach.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/test/test_case_template.hpp>

namespace borg {

//---------------------------------------------------------------------------
//! The argument itself is already a test for the string to be default-
//! and copy-constructible and assignable.
//---------------------------------------------------------------------------
BOOST_TEST_CASE_TEMPLATE_FUNCTION( test_string, StringT )
{
  typedef typename StringT::value_type char_type;
  typename StringT::value_type const_1[] = { 't','e','s','t',' ','s','t','r','i','n','g',0 };
  typename StringT::value_type const_2[] = { 'u','f','t','u','!','t','u','s','j','o','h',0 };
    
  StringT str_1 = const_1;

//  BOOST_CHECK( str_1.length() == 11 );
  BOOST_CHECK( str_1.equal(const_1) );
  BOOST_CHECK( str_1 != &const_1[2] );
  BOOST_CHECK( !str_1.empty() );

  // Testing const iterator.
  typename StringT::const_iterator b = str_1.begin();
  typename StringT::const_iterator e = str_1.end();
  
  BOOST_CHECK( b != e );
  
  int i = 0;
  bool ok = true;
  
  BOOST_FOREACH(typename StringT::value_type ch, str_1)
  {
    if(ch != const_1[i])
    {
      ok = false;
      break;
    }
    
    ++i;
//    std::cout << "ch: " << ch << std::endl;
  }
  
  i = 0;
  ok = true;
  
  typename StringT::iterator mb = str_1.begin();
  typename StringT::iterator me = str_1.end();
  
  while(mb != me)
  {
    ++(*mb);
    ++mb;
  }
  
  BOOST_CHECK( str_1.equal(const_2) );  
  
  // Testing appending...
   
  borg::size_t n = str_1.length();
  
  BOOST_CHECK_EQUAL(str_1.length(), n);

  str_1.append('X');
//  str_1.append("ala");

  BOOST_CHECK_EQUAL(str_1.length(), (n + 1));
  
/*  BOOST_FOREACH(char_type ch, str_1)
  {
  std::cout << "char: " << (char)ch << std::endl;
  }*/
  
}

//---------------------------------------------------------------------------

} // namespace borg
  
//---------------------------------------------------------------------------
#endif //ndef BORG_STRING_TESTS_HPP
