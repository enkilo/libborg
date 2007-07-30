#ifndef BORG_YAML_EVENT_HPP
#define BORG_YAML_EVENT_HPP

#include <yaml.h>
#include <borg/util/exception.hpp>

namespace borg {
namespace yaml {

//----------------------------------------------------------------------------
//! Event type constants.
//----------------------------------------------------------------------------
enum event_type
{
  no_event,

  stream_start_event,   //!< The STREAM-START event.
  stream_end_event,     //!< The STREAM-END event.

  document_start_event, //!< The DOCUMENT-START event.
  document_end_event,   //!< The DOCUMENT-END event.
    
  alias_event,          //!< An ALIAS event.
  scalar_event,         //!< A SCALAR event.
  
  sequence_start_event, //!< A SEQUENCE-START event.
  sequence_end_event,   //!< A SEQUENCE-END event.
    
  mapping_start_event,  //!< A MAPPING-START event.
  mapping_end_event,    //!< A MAPPING-END event.
};  
  
//----------------------------------------------------------------------------
//! Wrapper for a concrecte yaml_event_t instance.
//----------------------------------------------------------------------------
class event
{
  //-------------------------------------------------------------------
  //! Internal constructor. Use one of the static methods to create
  //! a new event.
  //-------------------------------------------------------------------
  event()
  {
  }

  //-------------------------------------------------------------------
  void
  throw_exception(char const *const msg)
  {
    throw exception< event >(msg);
  }
  
public:
  //-------------------------------------------------------------------
  //! Destroy the event.
  //-------------------------------------------------------------------
  ~event()
  {
    // Here we rely on the fact that yaml_event_delete() 
    // sets the type member to 0.
    if(m_event.type)
      yaml_event_delete(&m_event);
  }

  //-------------------------------------------------------------------
  //! Create the STREAM-START event.
  //-------------------------------------------------------------------
  static event
  stream_start(yaml_encoding_t const encoding = YAML_UTF8_ENCODING)
  {
    event e;

    if(!yaml_stream_start_event_initialize(&e.m_event, encoding))
      e.throw_exception("Failed initializing STREAM-START event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create the STREAM-END event.
  //-------------------------------------------------------------------
  inline static event
  stream_end()
  {
    event e;

    if(!yaml_stream_end_event_initialize(&e.m_event))
      e.throw_exception("Failed initializing STREAM-END event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create the DOCUMENT-START event.
  //-------------------------------------------------------------------
  static event
  document_start(yaml_version_directive_t *const version_directive = 0,
                 yaml_tag_directive_t *const tag_directives_start = 0,
                 yaml_tag_directive_t *const tag_directives_end = 0,
                 bool const implicit = false)
  {
    event e;

    if(!yaml_document_start_event_initialize
         (&e.m_event, version_directive, tag_directives_start,
          tag_directives_end, implicit))
      e.throw_exception("Failed initializing DOCUMENT-START event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create the DOCUMENT-END event.
  //-------------------------------------------------------------------
  static event
  document_end(bool const implicit = false)
  {
    event e;

    if(!yaml_document_end_event_initialize(&e.m_event, implicit))
      e.throw_exception("Failed initializing DOCUMENT-END event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create an ALIAS event.
  //-------------------------------------------------------------------
  static event
  alias(yaml_char_t *const anchor)
  {
    event e;

    if(!yaml_alias_event_initialize(&e.m_event, anchor))
      e.throw_exception("Failed initializing ALIAS event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create a SCALAR event.
  //-------------------------------------------------------------------
  static event
  scalar(yaml_char_t *const anchor, yaml_char_t *const tag, 
         yaml_char_t *const value, int const length,
         bool const plain_implicit = false,
         bool const quoted_implicit = false,
         yaml_scalar_style_t const style = YAML_PLAIN_SCALAR_STYLE)
  {
    event e;

    if(!yaml_scalar_event_initialize
          (&e.m_event, anchor, tag, value, length, 
           plain_implicit, quoted_implicit, style))
      e.throw_exception("Failed initializing SCALAR event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create a SEQUENCE-START event.
  //-------------------------------------------------------------------
  static event
  sequence_start(yaml_char_t *const anchor, yaml_char_t *const tag,
                 bool const implicit = false,
                 yaml_sequence_style_t const style = YAML_ANY_SEQUENCE_STYLE)
  {
    event e;

    if(!yaml_sequence_start_event_initialize
         (&e.m_event, anchor, tag, implicit, style))
      e.throw_exception("Failed initializing SEQUENCE-START event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create a SEQUENCE-END event.
  //-------------------------------------------------------------------
  static event
  sequence_end()
  {
    event e;

    if(!yaml_sequence_end_event_initialize(&e.m_event))
      e.throw_exception("Failed initializing SEQUENCE-END event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create a MAPPING-START event.
  //-------------------------------------------------------------------
  static event
  mapping_start(yaml_char_t *const anchor, yaml_char_t *const tag,
                bool const implicit = false,
                yaml_mapping_style_t const style = YAML_ANY_MAPPING_STYLE)
  {
    event e;

    if(!yaml_mapping_start_event_initialize
         (&e.m_event, anchor, tag, implicit, style))
      e.throw_exception("Failed initializing MAPPING-START event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Create a MAPPING-END event.
  //-------------------------------------------------------------------
  static event
  mapping_end()
  {
    event e;

    if(!yaml_mapping_end_event_initialize(&e.m_event))
      e.throw_exception("Failed initializing MAPPING-END event");

    return e;
  }

  //-------------------------------------------------------------------
  //! Gets the type of the event.
  //-------------------------------------------------------------------
  event_type
  get_type() const
  {
    return static_cast<event_type>(m_event.type);
  }
  
  //-------------------------------------------------------------------
  //! \name Type conversion to yaml_event_t *.
  //-------------------------------------------------------------------
  //@{
  operator yaml_event_t *()
  {
    return &m_event;
  }
  
  operator yaml_event_t const *() const
  {
    return &m_event;
  }
  //@}
  
private:
  yaml_event_t m_event; //!< The actual yaml_event_s structure.
};

} // namespace yaml
} // namespace borg


//---------------------------------------------------------------------------
#endif //ndef BORG_YAML_EVENT_HPP
