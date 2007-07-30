#ifndef BORG_LIBXML2_DOM_PARSER_HPP
#define BORG_LIBXML2_DOM_PARSER_HPP

#include <boost/filesystem/path.hpp>
#include <borg/libxml2/traits.hpp>
#include <borg/xml/dom/interface.hpp>
#include <borg/xml/dom/parser.hpp>

namespace borg { 
namespace xml { 
namespace dom {

//----------------------------------------------------------------------------
template<>
struct parser_impl<libxml2::traits>
{
  XML_DOM_TYPES(libxml2::traits)

//  typedef options_type options;  
//  BOOST_STATIC_CONSTANT(options_type, 
  
  BOOST_STATIC_CONSTANT(options_type, recover   = XML_PARSE_RECOVER);   //!< recover on errors.
  BOOST_STATIC_CONSTANT(options_type, noent     = XML_PARSE_NOENT);     //!< substitute entities.
  BOOST_STATIC_CONSTANT(options_type, dtdload   = XML_PARSE_DTDLOAD);   //!< load the external subset.
  BOOST_STATIC_CONSTANT(options_type, dtdattr   = XML_PARSE_DTDATTR);   //!< default DTD attributes.
  BOOST_STATIC_CONSTANT(options_type, dtdvalid  = XML_PARSE_DTDVALID);  //!< validate with the DTD.
  BOOST_STATIC_CONSTANT(options_type, noerror   = XML_PARSE_NOERROR);   //!< suppress error reports.
  BOOST_STATIC_CONSTANT(options_type, nowarning = XML_PARSE_NOWARNING); //!< suppress warning reports.
  BOOST_STATIC_CONSTANT(options_type, pedantic  = XML_PARSE_PEDANTIC);  //!< pedantic error reporting.
  BOOST_STATIC_CONSTANT(options_type, noblanks  = XML_PARSE_NOBLANKS);  //!< remove blank nodes.
    
  //! Create a parser.
  //-----------------------------------------------------------------------
  static parser_type
  create()
  {
    return xmlNewParserCtxt();
  }
    
  //! Parse a document (by URL).
  //-----------------------------------------------------------------------
  static bool
  parse_string(const parser_type &p, const wchar_type *cur, 
               const url_type &url = url_type(), 
               const options_type &opt = options_type())
  {
    p->myDoc = xmlCtxtReadDoc(p, cur, url, "UTF-8", opt);
    return (p->myDoc != 0);
  }
    
  //! Parse a file.
  //-----------------------------------------------------------------------
  static bool
  parse_file(const parser_type &p, const path_type &path,
             const options_type &opt = options_type())
  {
    p->myDoc = xmlCtxtReadFile(p, path, "UTF-8", opt);
    return (p->myDoc != 0);
  }

  //! Return the parsed document.
  //-----------------------------------------------------------------------
  static document_type
  document(const parser_type &p)
  {
    return p->myDoc;
  }        

  //! Return number of errors.
  //-----------------------------------------------------------------------
  static bool
  error(const parser_type &p)
  {
    return (p->lastError.level > XML_ERR_WARNING);
  }        

  //! Reset parser state.
  //-----------------------------------------------------------------------
  static void
  reset(const parser_type &p)
  {
    xmlCtxtReset(p);
  }        

  //! Destroy parser context.
  //-----------------------------------------------------------------------
  static void
  destroy(parser_type &p)
  {
    xmlFreeParserCtxt(p);
    p = 0;
  }        

  //! Initialize context-less parser.
  //-----------------------------------------------------------------------
  static void
  init()
  {
    xmlInitParser();
  }
  
  //-----------------------------------------------------------------------
  static void
  cleanup()
  {
    xmlCleanupParser();
  }        

  //-----------------------------------------------------------------------
  static void
  clear(parser_type p)
  {
    xmlClearParserCtxt(p);
  }        
};

//----------------------------------------------------------------------------
/*template<>
class parser<libxml2::traits>
    : public parser_interface< libxml2::traits, parser<libxml2::traits> >
    , public parser_facade< libxml2::traits, parser<libxml2::traits> >
{
public:
  typedef parser_impl<libxml2::traits> impl;
  
  parser() : m_parser(impl::create()) {}
  ~parser() { impl::destroy(m_parser); }
  
private:
  friend class parser_impl<libxml2::traits>;
  
  libxml2::traits::parser_type const m_parser;
  libxml2::traits::parser_type get() const { return m_parser; }
};*/
  
} // namespace dom
} // namespace xml

//---------------------------------------------------------------------------
namespace libxml2 {
namespace dom {

typedef xml::dom::parser_t<traits> parser_t;
typedef xml::dom::parser<traits> parser;

BORG_XML_DOM_PARSER_OPTIONS(traits);

} // namespace dom
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_DOM_PARSER_HPP
