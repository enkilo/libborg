#include <iostream>
#include <borg/nspr/address.hpp>
#include <borg/nspr/socket.hpp>

#include <borg/apr/address.hpp>
#include <borg/apr/socket.hpp>

#define PRINT_RESULT(expr) std::cout << #expr ": " << (expr) << std::endl;

template<class Traits>
void http_connect()
{
  using namespace borg;
  
  net::tcp_socket< Traits > mysock;
  net::ipv4_address< Traits > myaddr("127.0.0.1");
  
  myaddr.set_port(80);
  
  std::cout << myaddr.to_string() << ":" << myaddr.get_port() << std::endl;
  
  PRINT_RESULT( mysock.connect(myaddr, PR_INTERVAL_NO_TIMEOUT) );
  
  std::string request = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\n\r\n";
  
  PRINT_RESULT( mysock.send(request.c_str(), request.length(), 0, PR_INTERVAL_NO_TIMEOUT) )
  
  char buf[8192];
  int ret;
  
  PRINT_RESULT( ret = mysock.recv(buf, sizeof(buf), 0, PR_INTERVAL_NO_TIMEOUT) )
    
  std::string str(buf, &buf[ret]);
  
  std::cout << "response: " << str << std::endl;
}

int main()
{
  http_connect< borg::nspr::traits >();
//  http_connect< borg::apr::traits >();
}
