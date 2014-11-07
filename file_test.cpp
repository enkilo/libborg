#define APR_DECLARE_STATIC

#include <iostream>
#include <nspr/prerror.h>
#include <borg/nspr/file.hpp>
#include <borg/apr/file_io.hpp>

#define PRINT_RESULT(expr) std::cout << #expr ": " << (expr) << std::endl;

template<class Traits>
void test_file(typename Traits::string_type name)
{
  using namespace borg;
  
  typedef fs::file<Traits> file_type;
  
  file_type test(name, file_type::o_wronly|file_type::o_create|file_type::o_truncate, 0644);
  
  PRINT_RESULT( test.write("this is a test!\n", 16) )
  test.close();
  
//  std::cout << "error: " << ::PR_ErrorToString(::PR_GetError(), PR_LANGUAGE_I_DEFAULT) << std::endl;
}

int main()
{
  test_file< borg::nspr::traits >("nspr_test.txt");
  test_file< borg::apr::traits >("apr_test.txt");

//  http_connect< borg::apr::traits >();
}
