#ifdef WIN32
#include <io.h>
#endif
#include <algorithm>
#include <iostream>
#include <exception>
#include <boost/filesystem/operations.hpp>

#include <borg/recls/recls_search.hpp>

static void
print_path(const boost::filesystem::path &p)
{
  std::cout << p.string() << std::endl;
//  std::cout << p.root_directory() << std::endl;
}

int main()
{
  using namespace std;
  using namespace boost;
  using namespace filesystem;
  
  try
  {
//    path dir = current_path();
//    for_each(directory_iterator(dir), directory_iterator(), print_path);
  
//    recls::entry e();
    
    
    //recls::search_adapter<recls::cpp::FileSearch> search(".", "*.cpp");
    
    path p("c:/WINDOWS", no_check);
    recls::entry e;

    cout << "e.empty() = " << e.empty() << endl;
    
    recls::file_search s(".", "*.cpp", recls::files|recls::recursive);
    
    for_each(s.begin(), s.end(), print_path);
  }
  catch(const exception &e)
  {
    cerr << "Exception: " << e.what() << endl;
  }
  
  return 0;
}
