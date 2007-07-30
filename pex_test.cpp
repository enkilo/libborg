#include <cstdlib>
#include <iostream>
#include <borg/util/pex.hpp>

int main()
{
  using namespace std;  
  using borg::pex;

  pex exec(0, "program");
  string out;
  
  try
  {
    exec.run(0, "c:\\Cygwin\\bin\\ls.exe", pex::argv("ls", "-la", "pex_test.cpp", "js_test.cpp"));
    exec.run(pex::last, "c:\\Cygwin\\bin\\sort.exe", pex::argv("sort", "-r"));
  }
  catch(exception &e)
  {
    cout << "warning: exception: " << e.what() << endl;
  }
  catch(...)
  {
    cout << "warning: exception" << endl;
  }

  int status, err;
  
  cout << "one: " <<
    pex::one(0, "c:\\Cygwin\\bin\\ls.exe", pex::argv("ls", "test.cpp"), "ls", "stdout.txt", "stderr.txt", status, err)
    << endl;
  
  cout << "one status: " << status << endl;
  cout << "one err: " << err << endl;  
  
  vector<int> states;
  
  cout << exec.get_status(2, states) << endl;
  cout << ios_base::hex << states[0] << endl;
  
  cout << out << endl;
  
//  std::cout << sizeof(exec) << std::endl;
  exit(0);
  
  
}
