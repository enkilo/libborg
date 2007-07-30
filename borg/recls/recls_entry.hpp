#ifndef RECLS_ENTRY_HPP
#define RECLS_ENTRY_HPP

#include <boost/filesystem/path.hpp>
#include <recls/cpp/fileentry.hpp>

#include <borg/wrap/wrapper_facade.hpp>
/*#include "util/string.hpp"*/

namespace recls {

//----------------------------------------------------------------------------
class entry 
    : public borg::wrapper_facade< entry, borg::wrap_traits<recls::cpp::FileEntry> >
{
public:
  /// underlying file entry type from recls.
  typedef recls::cpp::FileEntry value_type;

  /// default constructor.
  entry()
  {}

  /// adapting constructor.
  entry(const value_type &e)
    : m_entry(e)
  {}

  /// empty?
  bool
  empty() const { return m_entry.length() == 0; }    
  
  /// conversion to boost::filesystem::path.
  operator boost::filesystem::path() const
  {
    if(m_entry.length())
      return boost::filesystem::path(m_entry.GetPath(),  boost::filesystem::no_check);
    
    return boost::filesystem::path();
  }
  
private:
  value_type m_entry;
  
  // wrapper core interface
  friend class borg::wrapper_core_access;  
  
  /// getter
  const value_type &
  get() const { return m_entry; }

  /// setter
  void
  set(const value_type &v) { m_entry = v; }
};  
  
} // namespace recls
//---------------------------------------------------------------------------
#endif //ndef RECLS_ENTRY_HPP
