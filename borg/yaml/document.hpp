#ifndef BORG_YAML_DOCUMENT_HPP
#define BORG_YAML_DOCUMENT_HPP

#include <yaml.h>
#include <borg/util/exception.hpp>
#include <borg/yaml/node.hpp>

//---------------------------------------------------------------------------

namespace borg {
namespace yaml {

//----------------------------------------------------------------------------
//! Wrapper for a concrecte yaml_document_t instance.
//----------------------------------------------------------------------------
class document
{
  //-------------------------------------------------------------------
  //! Throws an exception, related to this document.
  //-------------------------------------------------------------------
  void
  throw_exception(char const *const msg) throw(exception< document >)
  {
    throw exception< document >(msg);
  }
  
public:
  //-------------------------------------------------------------------
  //! Create a YAML document.
  //-------------------------------------------------------------------
  document(yaml_version_directive_t *const version_directive = 0,
           yaml_tag_directive_t *const tag_directives_start = 0,
           yaml_tag_directive_t *const tag_directives_end = 0,
           bool const start_implicit = false, 
           bool const end_implicit = false)
  {
    if(!yaml_document_initialize
         (&m_document, version_directive, tag_directives_start, 
          tag_directives_end, start_implicit, end_implicit))
      throw_exception("Failed to initialize document");
  }

  //-------------------------------------------------------------------
  //! Destroy the document.
  //-------------------------------------------------------------------
  ~document()
  {
    if(m_document.nodes.start)
      yaml_document_delete(&m_document);
  }

  //-------------------------------------------------------------------
  //! Get node by id.
  //-------------------------------------------------------------------
  node_ptr
  get_node(int const index)
  {
    return yaml_document_get_node(&m_document, index);
  }
  
  //-------------------------------------------------------------------
  //! Get the root node.
  //-------------------------------------------------------------------
  node_ptr
  get_root_node()
  {
    return yaml_document_get_root_node(&m_document);
  }
  
  //-------------------------------------------------------------------
  //! Get the version directive.
  //-------------------------------------------------------------------
  yaml_version_directive_t const *
  get_version_directive() const
  {
    return m_document.version_directive;
  }
  
  //-------------------------------------------------------------------
  //! Create a SCALAR node and attach it to the document.
  //-------------------------------------------------------------------
  node_id
  add_scalar(yaml_char_t const *const tag, 
             yaml_char_t const *const value,
             int                const length,
             scalar_style       const style = any_scalar_style)
  {
    return yaml_document_add_scalar(
       &m_document,
        const_cast<yaml_char_t *>(tag),
        const_cast<yaml_char_t *>(value),
        length, 
        static_cast<yaml_scalar_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Create a SCALAR node and attach it to the document. The value
  //! is assumed to be NUL-terminated (as C strings).
  //-------------------------------------------------------------------
  node_id
  add_scalar(yaml_char_t const *const tag, 
             yaml_char_t const *const value,
             scalar_style       const style = any_scalar_style)
  {
    return yaml_document_add_scalar(
       &m_document, 
        const_cast<yaml_char_t *>(tag),
        const_cast<yaml_char_t *>(value),
      ::strlen(reinterpret_cast<char const *>(value)),
        static_cast<yaml_scalar_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Create a SCALAR node and attach it to the document. It takes
  //! the default scalar tag (string).
  //-------------------------------------------------------------------
  node_id
  add_scalar(yaml_char_t const *const value,
             int                const length,
             scalar_style       const style = any_scalar_style)
  {
    return yaml_document_add_scalar(
       &m_document,
        const_cast<yaml_char_t *>(default_scalar_tag),
        const_cast<yaml_char_t *>(value),
        length, 
        static_cast<yaml_scalar_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Create a SCALAR node and attach it to the document. It takes
  //! the default scalar tag (string) and assumes a NUL-terminated
  //! value.
  //-------------------------------------------------------------------
  node_id
  add_scalar(yaml_char_t const *const value,
             scalar_style       const style = any_scalar_style)
  {
    return yaml_document_add_scalar(
       &m_document, 
        const_cast<yaml_char_t *>(default_scalar_tag),
        const_cast<yaml_char_t *>(value),
        ::strlen((const char *)value), 
        static_cast<yaml_scalar_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Create a SEQUENCE node and attach it to the document.
  //-------------------------------------------------------------------
  node_id
  add_sequence(yaml_char_t const *const tag   = default_sequence_tag, 
               sequence_style     const style = any_sequence_style)
  {
    return yaml_document_add_sequence(
       &m_document, 
        const_cast<yaml_char_t *>(tag), 
        static_cast<yaml_sequence_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Create a MAPPING node and attach it to the document.
  //-------------------------------------------------------------------
  node_id
  add_mapping(yaml_char_t const *const tag   = default_mapping_tag,
              mapping_style      const style = any_mapping_style)
  {
    return yaml_document_add_mapping(
       &m_document,
        const_cast<yaml_char_t *>(tag),
        static_cast<yaml_mapping_style_t>(style)
    );
  }
  
  //-------------------------------------------------------------------
  //! Add an item to a SEQUENCE node.
  //-------------------------------------------------------------------
  bool
  append_sequence_item(int const sequence, int const item)
  {
    return yaml_document_append_sequence_item
        (&m_document, sequence, item);
  }
  
  //-------------------------------------------------------------------
  //! Add a pair of a key and a value to a MAPPING node.
  //-------------------------------------------------------------------
  bool
  append_mapping_pair(int const mapping, int const key, int const value)
  {
    return yaml_document_append_mapping_pair
        (&m_document, mapping, key, value);
  }
  
  //-------------------------------------------------------------------
  //! \name Type conversion to yaml_document_t *.
  //-------------------------------------------------------------------
  //@{
  operator yaml_document_t       *()       { return &m_document; }
  operator yaml_document_t const *() const { return &m_document; }
  //@}
  
private:
  yaml_document_t m_document; //!< The actual yaml_document_s structure.
};

//---------------------------------------------------------------------------

} // namespace yaml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_YAML_DOCUMENT_HPP
