#ifndef PEX_HPP
#define PEX_HPP

#include <fstream>
#include <string>
#include <vector>

namespace borg {

using std::ifstream;
using std::string;
using std::vector;
  
class pex
{
public:
  enum
  {
    last = 0x01,
    search = 0x02,
    suffix = 0x04,
    stderr_to_stdout = 0x08,
    binary_input = 0x10,
    binary_output = 0x20
  };
  
  struct time
  {
    unsigned long user_seconds;
    unsigned long user_microseconds;
    unsigned long system_seconds;
    unsigned long system_microseconds;
  };
  
  pex(int flags, const string &pname);
  pex(int flags, const string &pname, const string &tempbase);
  ~pex();
  
  string 
  run(int flags, const string &executable,
      const vector<string> &argv = vector<string>());
  
  string 
  run(int flags, const string &executable, const vector<string> &argv,
      const string &outname);
  
  string 
  run(int flags, const string &executable, const vector<string> &argv,
      const string &outname, const string &errname);
  
  ifstream
  read_output(bool binary = false);
  
  int
  get_status(int count, vector<int> &vec);
  
  int
  get_times(int count, vector<time> &vec);
  
  static string
  one(int flags, const string &executable, const vector<string> &argv,
      int &status, int &err);
  
  static string
  one(int flags, const string &executable, const vector<string> &argv,
      const string &pname, int &status, int &err);
  
  static string
  one(int flags, const string &executable, const vector<string> &argv,
      const string &pname, const string &outname, int &status, int &err);
  
  static string
  one(int flags, const string &executable, const vector<string> &argv,
      const string &pname, const string &outname, const string &errname, 
      int &status, int &err);
  
  static vector<string> 
  argv(const string &a0)
  {
    vector<string> ret;
    ret.push_back(a0);
    return ret;
  }

  static vector<string> 
  argv(const string &a0, const string &a1)
  {
    vector<string> ret;
    ret.push_back(a0);
    ret.push_back(a1);
    return ret;
  }

  static vector<string>
  argv(const string &a0, const string &a1, const string &a2)
  {
    vector<string> ret;
    ret.push_back(a0);
    ret.push_back(a1);
    ret.push_back(a2);
    return ret;
  }

  static vector<string>
  argv(const string &a0, const string &a1, const string &a2, const string &a3)
  {
    vector<string> ret;
    ret.push_back(a0);
    ret.push_back(a1);
    ret.push_back(a2);
    ret.push_back(a3);
    return ret;
  }
  
private:
  void *m_obj;
  int m_err;
};
  
}

#endif //ndef PEX_HPP
