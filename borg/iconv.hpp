#ifndef ICONV_HPP
#define ICONV_HPP

#include <string>
#include <iconv.h>

#undef iconv

namespace borg {
namespace iconv {

using std::string;
  
//---------------------------------------------------------------------------
template<typename _Tin, typename _Tout>
  class base
{
private:
  void *m_iconv;
  
public:
  base(const string &tocode, const string &fromcode)
  { m_iconv = iconv_open(tocode.c_str(), fromcode.c_str()); }
  
  virtual ~base()
  { if(m_iconv) iconv_close(m_iconv); }
  
  virtual _Tout operator()(const _Tin &from);
};

//---------------------------------------------------------------------------
template<>
  class base<string, string>
{
private:
  void *m_iconv;
  
public:
  base(const string &tocode, const string &fromcode);
  virtual ~base();
  
  virtual string operator()(const string &from);
};

//---------------------------------------------------------------------------
class utf8_encode : public base<string, string>
{
public:
  utf8_encode();
  virtual ~utf8_encode();
};

} // namespace iconv
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef ICONV_HPP
