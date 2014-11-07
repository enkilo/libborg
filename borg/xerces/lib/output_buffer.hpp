#ifndef BORG_XERCES_OUTPUT_BUFFER_HPP
#define BORG_XERCES_OUTPUT_BUFFER_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/lib/output_buffer.hpp>

namespace borg { 
namespace xml {

//----------------------------------------------------------------------------
template<class T>
class output_buffer_impl<xerces::traits, T>
{
public:
  XML_LIB_TYPES(xerces::traits)
  
  //-----------------------------------------------------------------------
  template<class FormatTarget>
  static const byte_type *
  get_raw_buffer(const FormatTarget &target)
  {
    return target->getRawBuffer();
  }
  
};

//----------------------------------------------------------------------------
template<class Derived, class T>
struct output_buffer_interface<xerces::traits, Derived, T>
{
  XML_LIB_TYPES(xerces::traits)
    
  typedef output_buffer_impl<xerces::traits, T> impl;
    
  const byte_type *
  get_raw_buffer() const
  {
    return impl::get_raw_buffer(dereference_cast<Derived const>(this));
  }
};
    
//----------------------------------------------------------------------------
template<>
class output_buffer<xerces::traits, xerces::traits::membuf_output_buffer_type>
    : public output_buffer_t<xerces::traits, xerces::traits::membuf_output_buffer_type>
{
public:
  XML_LIB_TYPES(xerces::traits)

  typedef output_buffer_t<xerces::traits, xerces::traits::membuf_output_buffer_type> base_type;
  
  output_buffer(length_type capacity = 1023)
    : base_type(new ::XERCES_CPP_NAMESPACE::MemBufFormatTarget(capacity))
  {}
};

//----------------------------------------------------------------------------
template<>
class output_buffer<xerces::traits, xerces::traits::localfile_output_buffer_type>
    : public output_buffer_t<xerces::traits, xerces::traits::localfile_output_buffer_type>
{
public:
  typedef output_buffer_t<xerces::traits, xerces::traits::localfile_output_buffer_type> base_type;
  
  template<class String>
  output_buffer(const String &path)
    : base_type(new ::XERCES_CPP_NAMESPACE::LocalFileFormatTarget(path))
  {}
};

//----------------------------------------------------------------------------
template<>
class output_buffer<xerces::traits, xerces::traits::stdout_output_buffer_type>
    : public output_buffer_t<xerces::traits, xerces::traits::stdout_output_buffer_type>
{
public:
  typedef output_buffer_t<xerces::traits, xerces::traits::stdout_output_buffer_type> base_type;
  
  output_buffer()
    : base_type(new ::XERCES_CPP_NAMESPACE::StdOutFormatTarget())
  {}
};

} // namespace xml

namespace xerces {

using borg::pointer_facade;
using borg::wrap_traits;
  
class stream_output_buffer 
    : public ::XERCES_CPP_NAMESPACE::XMLFormatTarget
    , public pointer_facade< stream_output_buffer, wrap_traits< ::XERCES_CPP_NAMESPACE::XMLFormatTarget * >  >
    , public xml::output_buffer_interface< xerces::traits, stream_output_buffer, ::XERCES_CPP_NAMESPACE::XMLFormatTarget * >
{
public:
  XML_LIB_TYPES(xerces::traits)

  typedef ::XERCES_CPP_NAMESPACE::XMLFormatTarget base_type;
    
  stream_output_buffer(std::ostream &os) 
    : m_stream(&os)
  {}
  
  virtual void
  writeChars(const byte_type *const toWrite,
             const unsigned int count,
             xerces::traits::formatter_type const formatter)
  {
    m_stream->write((const char *)toWrite, count);
  }
  
  virtual void
  flush()
  {
    m_stream->flush();
  }

  std::ostream &
  stream() { return *m_stream; }      
  
private:
  std::ostream *m_stream;

  friend class borg::wrapper_core_access;
  
  base_type *
  get() { return this; }    

};
  
} // namespace xerces
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_OUTPUT_BUFFER_HPP
