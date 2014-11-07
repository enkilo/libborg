#include <list>
#include <iostream>
#include <sstream>
#include <exception>
#include <cstddef>
#include <borg/util/array.hpp>
#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <borg/array.hpp>
#include <borg/wx/array.hpp>
#include <borg/wx/string.hpp>

using namespace std;

template<class T, int N>
inline static
boost::array<T, N> &
array_cast(T *a)
{
  return *reinterpret_cast< boost::array<T, N> * >(a);
}

void print(int i)
{
  cout << i << endl;
}

borg::stdcxx::string
to_string(int i)
{
  ostringstream os;
  os << i;
  return os.str();
}

int main()
{
  int blah[] = { 1, 2, 3, 4 };    
  
  borg::wx::array<short> borgarr;
  borg::wx::array<wxString> strarr;

  borgarr->Add(3);
  borgarr->Add(4);
  borgarr.push_back(5);
  
  strarr.push_back("ab");
  strarr.push_back("bc");
  strarr.push_back("cd");
  strarr.push_back("de");
  strarr.push_back("ef");
  
//  std::for_each(&wxarr.Item(0), &wxarr.Item(0) + wxarr.GetCount(), print);
//  std::for_each(borg::begin(borgarr), borg::end(borgarr), print);
  for_each(borgarr.begin(), borgarr.end(), print);
  
  std::cout << "array size: " << strarr.size() << std::endl;
  
//  for_each(&blah[0], &blah[4], print);
  for_each(array_cast<int, 4>(blah).begin(),
           array_cast<int, 4>(blah).end(), print);
  
  try
  {
    borg::util::array<int> test;
    
    test.push(0);
    test.push(1);
    test.push(2);
    test.push(3);
    test.push(4);
    test.push(5);
    test.push(6);
    test.push(7);
    
/*    cout << test.join(',') << endl;
    cout << test.splice(2, 2).join(',') << endl;
    cout << test << endl;
    
    cout << test.index_of(123) << endl;
    cout << test[test.index_of(123)] << endl;*/
    cout << test.last_index_of(123) << endl;
    cout << test.to_string() << endl;
    
//    test.length = 3;

//    cout << test.length << endl;
    
    cout << test.to_string() << endl;
    
    borg::stdcxx::string test_str = "this,is,a,test";
    istringstream is(test_str);
    
    is >> test;
    
    cout << test << endl;
    cout << test.join(':') << endl;
    
    borg::util::array<borg::stdcxx::string> numbers
      //= test.map(&to_string);
      = test.map(&boost::lexical_cast<borg::stdcxx::string, int>);
    
    cout << "numbers: " << numbers << endl;
  }
  catch(exception &e)
  {
    cerr << "exception: " << e.what() << endl;
  }
  return 0;
}
