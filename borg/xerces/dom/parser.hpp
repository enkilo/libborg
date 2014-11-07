#ifndef BORG_XERCES_DOM_PARSER_HPP
#define BORG_XERCES_DOM_PARSER_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/dom/interface.hpp>
#include <borg/xml/dom/parser.hpp>
#include <borg/wrap/core/inherit.hpp>
#include <borg/wrap/core/convertible.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct parser_impl<xerces::traits>
{
  XML_DOM_TYPES(xerces::traits)

  typedef int options; //!< FIXME
    
  //------------------------------------------------------------------------
  static parser_type 
  create()
  {
    return new ::XERCES_CPP_NAMESPACE::XercesDOMParser;
  }
  
  //------------------------------------------------------------------------
  //! Parse a file.
  //------------------------------------------------------------------------
  static bool
  parse_file(const parser_type &p, const path_type &path,
             const options_type &opt = options_type())
  {
    // FIXME: implement options
    
    p->parse(path);
    return (p->getDocument() != 0);
  }

  //------------------------------------------------------------------------
  //! Return the parsed document.
  //------------------------------------------------------------------------
  static document_type
  document(const parser_type &p)
  {
    return p->getDocument();
  }        

  //------------------------------------------------------------------------
  //! Return number of errors.
  //------------------------------------------------------------------------
  static bool
  error(const parser_type &p)
  {
    return (p->getErrorCount() > 0);
  }
  
  //------------------------------------------------------------------------
  static void
  destroy(const parser_type &p)
  {
    delete p;
  }
};

//----------------------------------------------------------------------------
/*template<>
class parser<xerces::traits>
    : public borg::pointer_facade
      <
        parser<xerces::traits>, 
        borg::wrap_traits<xerces::traits::parser_type> 
      >
    , public parser_interface< xerces::traits, parser<xerces::traits> >
{
public:
  XML_DOM_TYPES(xerces::traits)

  typedef ::XERCES_CPP_NAMESPACE::XercesDOMParser wrap_type;

  parser() : m_parser(new wrap_type) 
  {}

  ~parser() 
  { delete m_parser; }
    
private:
  
  //! \name Wrapper core interface.
  //@{
  friend class borg::wrapper_core_access;
  
  wrap_type *m_parser;
  wrap_type *get() { return m_parser; }
  //@}
  
  //! \name No copy construction.
  //@{
  parser(const parser &);
  parser &operator=(const parser &);
  //@}
};*/
  
} // namespace dom
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_DOM_PARSER_HPP
