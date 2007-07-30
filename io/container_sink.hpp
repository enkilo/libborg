//----------------------------------------------------------------------------
//! \file  container_sink.hpp  
//! \brief Implements container_sink.
//! \svn   $Id: wrapper.hpp 42 2007-03-23 01:49:14Z nexbyte $
//----------------------------------------------------------------------------
#ifndef CONTAINER_SINK_HPP
#define CONTAINER_SINK_HPP

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/ios.hpp>

namespace io {

//----------------------------------------------------------------------------
template<typename Ch, typename Container>
class container_sink
{
public:
  typedef Ch                                char_type;
  typedef boost::iostreams::sink_tag        category;
  typedef Container                         container_type;
  typedef typename container_type::iterator iterator_type;
  
  /// construct from existing container.
  explicit
  container_sink(Container &container) throw()
    : m_container(&container)
    , m_delete(false)
  {}
  
  /// construct with new container.
  explicit
  container_sink()
    : m_container(new Container)
    , m_delete(true)
  {}

  /// copy constructor.
  container_sink(const container_sink &sink) 
    : m_container(&sink.container())
    , m_delete(false)
  {}
  
  /// delete container if owned by us.
  ~container_sink()
  {
    if(m_delete)
      delete m_container;
  }

  /// \name container getters
  //@{
  container_type &
  container() const throw() { return *m_container; }
  //@}
  
  std::streamsize
  write(const Ch *s, std::streamsize n)
  {
    try
    {
      m_container->resize(m_container->size() + n);
    }
    catch(std::bad_alloc &ba)
    {
      return 0;
    }
    
    std::copy(s, s + n, m_container->end() - n);
    return n;
  }
  
private:
  container_type *const m_container;
  bool const m_delete;
  iterator_type m_ptr;
};

} // namespace io
//----------------------------------------------------------------------------
#endif //ndef CONTAINER_SINK_HPP
