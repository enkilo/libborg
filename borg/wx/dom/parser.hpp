#ifndef BORG_WX_DOM_PARSER_HPP
#define BORG_WX_DOM_PARSER_HPP

#include <borg/wx/traits.hpp>
#include <borg/xml/dom/interface.hpp>
#include <borg/xml/dom/parser.hpp>
#include <borg/wrap/core/inherit.hpp>
#include <borg/wrap/core/convertible.hpp>

namespace borg {
namespace xml {
namespace dom {

//----------------------------------------------------------------------------
template<>
struct parser_impl<wx::traits>
{
  XML_DOM_TYPES(wx::traits)

  typedef int options;
    
  //------------------------------------------------------------------------
  //! Parse a file.
  //------------------------------------------------------------------------
  template<class ParserT, class InputT>
  static bool
  parse_file(ParserT &p, InputT const &input)
  {
    if(p.m_document)
    {
      delete p.m_document;
      p.m_document = 0;
    }

    p.m_document = new wxXmlDocument(input);
    p.m_ok = p.m_document->IsOk();
    
    return p.m_ok;
  }

  //------------------------------------------------------------------------
  //! Return the parsed document.
  //------------------------------------------------------------------------
  template<class ParserT>
  static document_type
  document(ParserT const &p)
  {
    return p.m_ok ? p.m_document : 0;
  }        

  //------------------------------------------------------------------------
  //! Return number of errors.
  //------------------------------------------------------------------------
  template<class ParserT>
  static bool
  error(ParserT const &p)
  {
    return !p.m_ok;
  }        
};

//----------------------------------------------------------------------------
template<>
class parser<wx::traits>
    : public borg::pointer_facade
      <
        parser<wx::traits>, 
        borg::wrap_traits<wx::traits::parser_type> 
      >
    , public parser_interface< wx::traits, parser<wx::traits> >
{
public:
  XML_DOM_TYPES(wx::traits)

  parser() : m_document(0)
  {}

  ~parser()
  {
    if(m_document)
      delete m_document;
  }
    
private:
  
  friend class parser_impl<wx::traits>;
  
  wxXmlDocument *m_document;
  bool m_ok;
};
  
}// namespace dom
}// namespace xml
//---------------------------------------------------------------------------

namespace wx {
namespace dom {
  
  typedef xml::dom::parser<traits> parser;

} // namespace wx
} // namespace dom
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_WX_DOM_PARSER_HPP
