#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <borg/xerces.hpp>
#include <borg/libxml2.hpp>
#include <borg/wx.hpp>
//#include <libxml/nanohttp.h>
#include <wx/init.h>
#include <wx/protocol/http.h>
#include <xercesc/util/XMLURL.hpp>

#ifdef WIN32
#include <xercesc/util/NetAccessors/WinSock/BinHTTPURLInputStream.hpp>
#else
#include <xercesc/util/NetAccessors/Socket/UnixHTTPURLInputStream.hpp>
#endif

#define PRINT_RESULT(expr) std::cout << #expr ": " << (expr) << std::endl;

using namespace std;
using namespace boost;

template<class Traits>
void test_http()
{
  using namespace borg;
  
  net::http_client<Traits> h("http://127.0.0.1/");
  
  boost::array<typename Traits::byte_type, 1024> buffer;
  typename Traits::length_type n;
  
  PRINT_RESULT( n = h.read(buffer.begin(), buffer.size()) )
//  PRINT_RESULT( h.return_code() )
//  PRINT_RESULT( h.content_type() )
//  PRINT_RESULT( h.content_length() )
  
  if(n > 0)
    PRINT_RESULT( std::string((char *)buffer.begin(), n) )
}

void test_wx_http_protocol()
{
  wxHTTP *http = new wxHTTP;
  wxInputStream *input;
  
  http->Connect("127.0.0.1");
  input = http->GetInputStream("/");
  
  if(input)
  {
    char buffer[1024];
    int n;

    input->Read(buffer, sizeof(buffer));
    PRINT_RESULT( n = input->LastRead() )
      
    if(n > 0)
      PRINT_RESULT( string(buffer, &buffer[n]) )

    delete input;
  }
  
  delete http;
}

int main()
{
  using namespace std;
  using namespace borg;
  
  try
  {
    libxml2::initialize();
    borg::xerces::initialize();
    wx::initialize();
    
    cout << "Using libxml2 NanoHTTP" << endl;
    cout << "----------------------------------------------------" << endl;
  
    test_http<libxml2::traits>();
    
    cout << endl;
    cout << "Using xerces BinHTTPURLInputStream" << endl;
    cout << "----------------------------------------------------" << endl;
    
    test_http<borg::xerces::traits>();

    
    cout << endl;
    cout << "Using wxwidgets wxHTTP" << endl;
    cout << "----------------------------------------------------" << endl;
  
//    test_http<wx::traits>();
    test_wx_http_protocol();
    
    cout << endl;
  
    wx::terminate();
    borg::xerces::shutdown();
    libxml2::shutdown();
  }
  catch(const ::xerces::NetAccessorException &e)
  {
    cerr << "xerces::NetAccessorException: " << e.getMessage() << endl;
  }
  catch(const std::exception &e)
  {
    cerr << "Exception: " << e.what() << endl;
  }

  return 0;
}
