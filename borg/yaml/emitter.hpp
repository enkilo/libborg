#ifndef BORG_YAML_EMITTER_HPP
#define BORG_YAML_EMITTER_HPP

#include <yaml.h>
#include <borg/util/exception.hpp>

namespace borg {
namespace yaml {

//----------------------------------------------------------------------------
//! Wrapper for a concrecte yaml_emitter_t instance.
//----------------------------------------------------------------------------
class emitter
{
  //-------------------------------------------------------------------
  void
  throw_exception(char const *const msg) throw(exception<emitter>)
  {
    throw exception<emitter>(msg);
  }
  
public:
  //-------------------------------------------------------------------
  //! Default constructor.
  //-------------------------------------------------------------------
  emitter()
  {
    if(!yaml_emitter_initialize(&m_emitter))
      throw_exception("initialization failed");
  }
  
  //-------------------------------------------------------------------
  //! Destroy the emitter.
  //-------------------------------------------------------------------
  ~emitter()
  {
    yaml_emitter_delete(&m_emitter);
  }

  //-------------------------------------------------------------------
  //! Set a string output.
  //-------------------------------------------------------------------
  void
  set_output_string(unsigned char *const output, ::size_t const size, 
                    ::size_t &size_written)
  {
    yaml_emitter_set_output_string(&m_emitter, output, size, &size_written);
  }

  //-------------------------------------------------------------------
  //! Set a file output.
  //-------------------------------------------------------------------
  void
  set_output_file(FILE *const file)
  {
    yaml_emitter_set_output_file(&m_emitter, file);
  }
  
  //-------------------------------------------------------------------
  //! \name Set a generic output handler.
  //-------------------------------------------------------------------
  //@{
  void
  set_output(yaml_write_handler_t *handler)
  {
    yaml_emitter_set_output(&m_emitter, handler, 0);
  }
  
  template<class Data>
  void
  set_output(yaml_write_handler_t *handler, Data const &data)
  {
    yaml_emitter_set_output(&m_emitter, handler, (void *)data);
  }
  //@}
  
  //-------------------------------------------------------------------
  //! Set the output encoding.
  //-------------------------------------------------------------------
  void
  set_encoding(yaml_encoding_t encoding)
  {
    yaml_emitter_set_encoding(&m_emitter, encoding);
  }
  
  //-------------------------------------------------------------------
  //! Set if the output should be in the "canonical" format as in the 
  //! YAML specification.
  //-------------------------------------------------------------------
  void
  set_canonical(bool canonical = true)
  {
    yaml_emitter_set_canonical(&m_emitter, canonical);
  }
  
  //-------------------------------------------------------------------
  //! Set the intendation increment.
  //-------------------------------------------------------------------
  void
  set_indent(int indent)
  {
    yaml_emitter_set_indent(&m_emitter, indent);
  }
  
  //-------------------------------------------------------------------
  //! Set the preferred line width. @c -1 means unlimited.
  //-------------------------------------------------------------------
  void
  set_width(int width)
  {
    yaml_emitter_set_width(&m_emitter, width);
  }
  
  //-------------------------------------------------------------------
  //! Set if unescaped non-ASCII characters are allowed.
  //-------------------------------------------------------------------
  void
  set_unicode(bool unicode = true)
  {
    yaml_emitter_set_unicode(&m_emitter, unicode);
  }
  
  //-------------------------------------------------------------------
  //! Set the preferred line break.
  //-------------------------------------------------------------------
  void
  set_break(yaml_break_t line_break)
  {
    yaml_emitter_set_break(&m_emitter, line_break);
  }
  
  //-------------------------------------------------------------------
  //! Emit an event.
  //-------------------------------------------------------------------
  bool
  emit(yaml_event_t *event)
  {
    return yaml_emitter_emit(&m_emitter, event);
  }
  
  //-------------------------------------------------------------------
  //! Start a YAML stream.
  //-------------------------------------------------------------------
  bool
  open()
  {
    return yaml_emitter_open(&m_emitter);
  }
  
  //-------------------------------------------------------------------
  //! Finish a YAML stream.
  //-------------------------------------------------------------------
  bool
  close()
  {
    return yaml_emitter_close(&m_emitter);
  }
  
  //-------------------------------------------------------------------
  //! Emit a YAML document.
  //-------------------------------------------------------------------
  bool
  dump(yaml_document_t *document)
  {
    return yaml_emitter_dump(&m_emitter, document);
  }
  
  //-------------------------------------------------------------------
  //! Flush the accumulated characters to the output.
  //-------------------------------------------------------------------
  bool
  flush()
  {
    return yaml_emitter_flush(&m_emitter);
  }
  
  //-------------------------------------------------------------------
  operator yaml_emitter_t *()
  {
    return &m_emitter;
  }
  
  operator yaml_emitter_t const *() const
  {
    return &m_emitter;
  }
  
  //-------------------------------------------------------------------
  emitter &
  operator<<(yaml_event_t *event)
  {
    if(!emit(event))
      throw_exception("Failed to emit event");
      
    return *this;
  }
  
  emitter &
  operator<<(yaml_document_t *doc)
  {
    if(!dump(doc))
      throw_exception("Failed to dump document");

    return *this;
  }
  
private:
  yaml_emitter_t m_emitter;
};

} // namespace yaml
} // namespace borg


//---------------------------------------------------------------------------
#endif //ndef BORG_YAML_EMITTER_HPP
