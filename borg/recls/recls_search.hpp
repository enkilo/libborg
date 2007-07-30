#ifndef RECLS_SEARCH_HPP
#define RECLS_SEARCH_HPP

#include <recls/cpp/filesearch.hpp>

#include <borg/recls/recls_iterator.hpp>
#include <borg/util/string.hpp>

namespace recls {

using boost::filesystem::path;

//----------------------------------------------------------------------------
enum flag
{
  files =       RECLS_F_FILES,
  directories = RECLS_F_DIRECTORIES,
  links =       RECLS_F_LINKS,
  devices =     RECLS_F_DEVICES,
  recursive =   RECLS_F_RECURSIVE
};
  
//----------------------------------------------------------------------------
template<class SearchT>
class search_adapter
{
public:
  typedef iterator_wrapper iterator;
  
  /// start a new search, starting from the specified directory, searching
  /// entries matching the specified mask.
/*  recls_search(const string &dir, const string &mask, uint32_t flags = 0) 
    : m_search(dir.c_str(), mask.c_str(), flags)
  {}*/

  search_adapter(const path &dir, const borg::stdcxx::string &mask, 
                 uint32_t flags = 0) 
    : m_search(dir.string().c_str(), mask.c_str(), flags)
  {}

  /// return an iterator
  iterator
  begin() { return iterator(m_search); }

  /// return an iterator
  iterator
  end() { return iterator(); }
  
private:
  /// underlying search instance.
  SearchT m_search;
};

//---------------------------------------------------------------------------
typedef search_adapter<recls::cpp::FileSearch> file_search;

} // namespace recls
//---------------------------------------------------------------------------
#endif //ndef RECLS_SEARCH_HPP
