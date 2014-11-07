
#include <borg/iconv.hpp>
#include <iostream>

namespace borg {
namespace iconv {
  
//----------------------------------------------------------------------------
base<std::string, std::string>::base
  (const std::string &tocode, const std::string &fromcode)
{
  m_iconv = ::iconv_open(tocode.c_str(), fromcode.c_str());
  
  if(m_iconv == 0)
    std::cerr << "ERROR: iconv_open(" << tocode << ", " << fromcode << ")" << std::endl;
}

//----------------------------------------------------------------------------
base<std::string, std::string>::~base()
{
  if(m_iconv)
    iconv_close(m_iconv);
}

//----------------------------------------------------------------------------
std::string 
base<std::string, std::string>::operator()(const std::string &from)
{
  size_t inbytes = from.length();
  const char *inb = from.c_str();

  size_t outbytes = (inbytes + 1) * 2;
  size_t outbytes_left = outbytes;
  char *buffer = new char[outbytes];
  char *outb = buffer;

#if defined(WIN32) || defined(_LIBICONV_H)
  ::libiconv
#else
  ::iconv
#endif
    (m_iconv, 
#if defined(WIN32) || defined(_LIBICONV_H)
     (const char **)
#else
     (char **)
#endif
     &inb, &inbytes, &outb, &outbytes_left);

  std::string ret;
  ret.append(buffer, outbytes - outbytes_left);

  delete[] outb;
  return ret;
}

//----------------------------------------------------------------------------
utf8_encode::utf8_encode() :
  base<std::string, std::string>("UTF-8", "LATIN-9")
{}

//----------------------------------------------------------------------------
utf8_encode::~utf8_encode()
{}
  
//----------------------------------------------------------------------------
} // namespace iconv
} // namespace borg
  
