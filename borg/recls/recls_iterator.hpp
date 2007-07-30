#ifndef RECLS_ITERATOR_HPP
#define RECLS_ITERATOR_HPP

//#include <stdexcept>
#include <boost/iterator/iterator_facade.hpp>
#include <recls/cpp/search.hpp>

#include <borg/recls/recls_entry.hpp>

namespace recls {

//----------------------------------------------------------------------------
class iterator_wrapper
    : public boost::iterator_facade<
        iterator_wrapper,
        entry, 
        boost::single_pass_traversal_tag 
    >
{
public:
  typedef iterator_wrapper this_type;
  typedef entry entry_type;
  typedef entry_type &reference;
  
  /// construct iterator which indicates end of search.
  iterator_wrapper()
  {}
  
  /// construct iterator which points to the current entry within the search.
  iterator_wrapper(recls::cpp::Search &recls)
    : m_psearch(&recls)
  {
    if(m_psearch->HasMoreElements())
      m_entry = m_psearch->GetCurrentEntry();
  }

  /// is end of search?
  bool
  is_end() const
  {
    return (m_psearch == 0) || m_entry.empty();
  }
  
private:
  recls::cpp::Search *m_psearch;
  entry_type m_entry;
  
  // iterator core interface.
  friend class boost::iterator_core_access;
   
  reference
  dereference() const
  {
    return reference(m_entry);
  }
  
  void increment()
  {
    if(!is_end() && (m_psearch->GetNext(), m_psearch->HasMoreElements()))
      m_entry = m_psearch->GetCurrentEntry();
    else
      m_entry = entry_type();
  }
  
  bool
  equal(const this_type &rhs) const
  {
    if(is_end() && rhs.is_end())
      return true;
    
    return false;
//    return dereference() == *rhs;
  }
};  

} // namespace recls
//---------------------------------------------------------------------------
#endif //ndef RECLS_ITERATOR_HPP
