#ifndef BORG_YAML_NODE_HPP
#define BORG_YAML_NODE_HPP

#include <yaml.h>
#include <borg/util/exception.hpp>

namespace borg {
namespace yaml {

//----------------------------------------------------------------------------
//! Node types.
//----------------------------------------------------------------------------
enum node_type
{
  no_node,
  scalar_node,
  sequence_node,
  mapping_node,
};

//----------------------------------------------------------------------------
//! \name Type tags.
//----------------------------------------------------------------------------
//@{
static yaml_char_t const null_tag     [] = YAML_NULL_TAG;
static yaml_char_t const bool_tag     [] = YAML_BOOL_TAG;
static yaml_char_t const str_tag      [] = YAML_STR_TAG;
static yaml_char_t const int_tag      [] = YAML_INT_TAG;
static yaml_char_t const float_tag    [] = YAML_FLOAT_TAG;
static yaml_char_t const timestamp_tag[] = YAML_TIMESTAMP_TAG;
static yaml_char_t const seq_tag      [] = YAML_SEQ_TAG;
static yaml_char_t const map_tag      [] = YAML_MAP_TAG;
//@}
  
//----------------------------------------------------------------------------
//! \name Default tags.
//----------------------------------------------------------------------------
//@{
static yaml_char_t const default_scalar_tag  [] = YAML_DEFAULT_SCALAR_TAG;
static yaml_char_t const default_sequence_tag[] = YAML_DEFAULT_SEQUENCE_TAG;
static yaml_char_t const default_mapping_tag [] = YAML_DEFAULT_MAPPING_TAG;
//@}
  
//----------------------------------------------------------------------------
//! Style of scalar nodes.
//----------------------------------------------------------------------------
enum scalar_style
{
  any_scalar_style,
  plain_scalar_style,
  single_quoted_scalar_style,
  double_quoted_scalar_style,
  literal_scalar_style,
  folded_scalar_style,
};

//----------------------------------------------------------------------------
//! Style of sequence nodes.
//----------------------------------------------------------------------------
enum sequence_style
{
  any_sequence_style,
  block_sequence_style,
  flow_sequence_style,
};

//----------------------------------------------------------------------------
//! Style of mapping nodes.
//----------------------------------------------------------------------------
enum mapping_style
{
  any_mapping_style,
  block_mapping_style,
  flow_mapping_style,
};
  
//----------------------------------------------------------------------------
//! Access the node.
//----------------------------------------------------------------------------
template< class T >
struct node_access;
  
//----------------------------------------------------------------------------
//! Access the node as int.
//----------------------------------------------------------------------------
template<>
struct node_access<int>
{
  static int 
  get(int const index, yaml_document_t *doc = 0) { return index; }

  static int 
  get(yaml_node_t *const node, yaml_document_t *doc = 0)
  {
    throw exception< node_access<int> >("cannot convert pointer to index");
    return 0;
  }
};
  
//----------------------------------------------------------------------------
//! Access the node by index.
//----------------------------------------------------------------------------
template<>
struct node_access<yaml_node_t *>
{
  static yaml_node_t *
  get(yaml_node_t *ptr, yaml_document_t *doc = 0)
  {
    return ptr;
  }

  static yaml_node_t *
  get(int const index, yaml_document_t *doc)
  {
    return yaml_document_get_node(doc, index);
  }
};
  
//----------------------------------------------------------------------------
//! Wrapper for a concrecte yaml_node_t instance.
//----------------------------------------------------------------------------
template< class T >
struct is_node 
  { static bool const value = false; };
  
template<>
struct is_node< yaml_node_t * > 
  { static bool const value = true; };

template<>
struct is_node< int >
  { static bool const value = false; };

//----------------------------------------------------------------------------
//! Wrapper for a concrecte yaml_node_t instance.
//----------------------------------------------------------------------------
template< class T = yaml_node_t * >
class basic_node
{
  //-------------------------------------------------------------------
  void
  throw_exception(char const *const msg)
  {
    throw exception< basic_node<T> >(msg);
  }
  
public:
  
  //-------------------------------------------------------------------
  //! Construct from T.
  //-------------------------------------------------------------------
  basic_node(T const &n) 
    : m_node(n)
  {
  }
  
  //-------------------------------------------------------------------
  //! Copy constructor.
  //-------------------------------------------------------------------
  template< class U >
  basic_node(basic_node<U> const &n)
    : m_node(n)
  {
  }
  
  //-------------------------------------------------------------------
  //! Get the tag.
  //-------------------------------------------------------------------
  yaml_char_t const *
  get_tag(yaml_document_t *const doc) const
  {
    return node_access< yaml_node_t * >::get(m_node, doc)->tag;
  }
  
  //-------------------------------------------------------------------
  //! Get the type.
  //-------------------------------------------------------------------
  node_type
  get_type(yaml_document_t *const doc) const
  {
    return static_cast<node_type>(
        node_access< yaml_node_t * >::get(m_node, doc)->type
    );    
  }
  
  //-------------------------------------------------------------------
  //! Type conversion to T.
  //-------------------------------------------------------------------
  operator T() const
  {
    return m_node;
  }

private:
  T m_node;
};

typedef basic_node< int >           node_id;
typedef basic_node< yaml_node_t * > node_ptr;
  
} // namespace yaml
} // namespace borg


//---------------------------------------------------------------------------
#endif //ndef BORG_YAML_NODE_HPP
