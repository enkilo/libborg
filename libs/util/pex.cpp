#include <ansidecl.h>
#include <borg/ext/libiberty.h>
#include <borg/util/pex.hpp>

namespace borg {

//---------------------------------------------------------------------------
pex::pex(int flags, const string &pname)
{
  m_obj = ::pex_init(flags, pname.c_str(), NULL);
}  

//---------------------------------------------------------------------------
pex::~pex()
{
  if(m_obj)
    ::pex_free(static_cast<pex_obj *>(m_obj));
}

//---------------------------------------------------------------------------
pex::pex(int flags, const string &pname, const string &tempbase)
{
  m_obj = ::pex_init(flags, pname.c_str(), tempbase.c_str());
}  
  
//---------------------------------------------------------------------------
string
pex::run(int flags, const string &executable, const vector<string> &argv)
{
  const char *av[argv.size() + 1];
  
  for(vector<string>::const_iterator
      it = argv.begin(); it != argv.end(); ++it)
    av[it - argv.begin()] = (*it).c_str();

  av[argv.end() - argv.begin()] = NULL;
  
  const char *ret = 
    ::pex_run(static_cast<pex_obj *>(m_obj), flags, executable.c_str(), 
              const_cast<char *const *>(av), NULL, NULL, &m_err);

  return ret ? ret : "";
}

//---------------------------------------------------------------------------
string
pex::run(int flags, const string &executable, const vector<string> &argv,
         const string &outname)
{
  const char *av[argv.size() + 1];
  
  for(vector<string>::const_iterator
      it = argv.begin(); it != argv.end(); ++it)
    av[it - argv.begin()] = (*it).c_str();

  av[argv.end() - argv.begin()] = NULL;
  
  const char *ret =
    ::pex_run(static_cast<pex_obj *>(m_obj), flags, executable.c_str(), 
              const_cast<char *const *>(av), outname.c_str(), NULL, &m_err);

  return ret ? ret : "";
}  

//---------------------------------------------------------------------------
string
pex::run(int flags, const string &executable, const vector<string> &argv,
         const string &outname, const string &errname)
{
  const char *av[argv.size() + 1];
  
  for(vector<string>::const_iterator
      it = argv.begin(); it != argv.end(); ++it)
    av[it - argv.begin()] = (*it).c_str();

  av[argv.size()] = NULL;  
  
  const char *ret =
    ::pex_run(static_cast<pex_obj *>(m_obj), flags, executable.c_str(), 
              const_cast<char *const *>(av), outname.c_str(), errname.c_str(), &m_err);
  
  return ret ? ret : "";
}

//---------------------------------------------------------------------------
string
pex::one(int flags, const string &executable, const vector<string> &argv,
         int &status, int &err)
{
  const char *av[argv.size() + 1];
  
  for(vector<string>::const_iterator
      it = argv.begin(); it != argv.end(); ++it)
    av[it - argv.begin()] = (*it).c_str();

  av[argv.size()] = NULL;  
  
  const char *ret =
    ::pex_one(flags, executable.c_str(), const_cast<char *const *>(av),
              av[0], NULL, NULL, &status, &err);
  
  return ret ? ret : "";  
}

//---------------------------------------------------------------------------
string
pex::one(int flags, const string &executable, const vector<string> &argv,
         const string &pname, const string &outname, const string &errname,
         int &status, int &err)
{
  const char *av[argv.size() + 1];
  
  for(vector<string>::const_iterator
      it = argv.begin(); it != argv.end(); ++it)
    av[it - argv.begin()] = (*it).c_str();

  av[argv.size()] = NULL;  
  
  const char *ret =
    ::pex_one(flags, executable.c_str(), const_cast<char *const *>(av),
              pname.c_str(), outname.c_str(), errname.c_str(), &status, &err);
  
  return ret ? ret : "";  
}

//---------------------------------------------------------------------------
int
pex::get_status(int count, vector<int> &vec)
{
  vec.resize(count);
  return ::pex_get_status(static_cast<pex_obj *>(m_obj), count, &vec.front());
}
  
  
} // namespace borg
