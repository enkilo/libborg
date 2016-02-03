#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/dom/DOMXPathException.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>

#include <borg/util/assert.hpp>
#include <borg/xerces.hpp>
//#include <borg/xml/lib/facades.hpp>
#include <borg/xml/dom/nodemap.hpp>

using namespace std;
using namespace borg;

/// error reporter
class DOMTreeErrorReporter 
  : public ::XERCES_CPP_NAMESPACE::ErrorHandler
{
public:
  DOMTreeErrorReporter() 
    : fSawErrors(false)
  {}

  virtual ~DOMTreeErrorReporter()
  {}

  void warning(const ::XERCES_CPP_NAMESPACE::SAXParseException &toCatch)
  {
    fSawErrors = true;
    cerr << "warning on file=" << ::XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getSystemId()) << ",line=" << toCatch.getLineNumber() << ",col=" << toCatch.getColumnNumber() << std::endl;
  }
  
  void error(const ::XERCES_CPP_NAMESPACE::SAXParseException &toCatch)
  {
    fSawErrors = true;
    cerr << "error on file=" << ::XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getSystemId()) << ",line=" << toCatch.getLineNumber() << ",col=" << toCatch.getColumnNumber() << std::endl;
  }
  
  void fatalError(const ::XERCES_CPP_NAMESPACE::SAXParseException &toCatch)
  {
    fSawErrors = true;
    cerr << "fatalError on file=" << ::XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getSystemId()) << ",line=" << toCatch.getLineNumber() << ",col=" << toCatch.getColumnNumber() << std::endl;
  }

  void resetErrors() { fSawErrors = false; }
  bool getSawErrors() const { return fSawErrors; }

private:
  bool fSawErrors;  
};

/*void attr_fn(xerces::dom::node_t const &n)
{
}*/

void test_fn(borg::xerces::dom::attribute_t const &a)
{
  wcout << (XMLCh const *)a.name() << "=\"" << (XMLCh const *)a.value() << "\"" << endl;
}


void node_fn(borg::xerces::dom::node_t const &n)
{
  using namespace borg::xerces::dom;
  
  if(n.type() == borg::xml::dom::element_node)
  {
    element_t elm(n);    
    wcout << "element name: " << (XMLCh const *)n.name() << endl;
    
//    nodemap_t map = elm.attributes();
//    for_each(map.begin(), map.end(), test_fn);
//    nodemap_t map = elm.attributes();
    for_each(elm.attributes().begin(), elm.attributes().end(), test_fn);
  }
  else if(n.type() == borg::xml::dom::attribute_node)
  {
    wcout << (XMLCh const *)n.name() << "=\"" << (XMLCh const *)n.value() << "\"" << endl;
  }
}

int main()
{
  int error_code = 0;
  using namespace ::XERCES_CPP_NAMESPACE;

  try
  {
    using borg::xerces::string;
    using namespace borg::xerces::dom;
    using namespace borg::xerces::xpath;
    
    borg::xerces::initialize();

//    #define STR_SIZE(tempstr) ((sizeof(tempstr) / sizeof(tempstr[0])) - 1)
//    #define TRANSCODE(str) XMLString::transcode(str)
//    #define ENCODING "UTF-32"
    DOMTreeErrorReporter *errReporter = new DOMTreeErrorReporter();
///*   parser_t p = */new XercesDOMParser();
    parser p;

    cout << "parser: " << (void *)p << endl;
    
    p->setErrorHandler(errReporter);

    std::string filename = "xerces_parser_utf16.xml";
    
    p.parse_file((char *)filename.c_str());
    
    cout << "sawErrors: " << errReporter->getSawErrors() << endl;
    cout << "p.error() = " << p.error() << endl;
    
    // get the DOM representation
    document_t doc = p.document();
    
    wcout << "encoding is: " << (XMLCh const *)doc.get_actual_encoding() << endl;
    
    
//    cout << "expression: " << (::XERCES_CPP_NAMESPACE::DOMXPathExpression const *)expr << endl;
    
    //    delete p;
    
    if(!doc)
      throw logic_error("document is NULL");
    
    if(!doc.first_child())
      throw logic_error("document has no child nodes");
    
    wcout << "doc.name() = " << (XMLCh const *)doc.name() << endl;
//    cout << "doc.value() = " << doc.value() << endl;
    cout << "doc.type() = " << (XMLCh const *)doc.type() << endl;

    element_t elm = doc.first_child();
    cout << "doc.first_child() = " << (void *)elm << endl;
    
    element_t rec = elm.first_child().next_sibling();
    wcout << "rec.name = " << (XMLCh const *)rec.name() << endl;
    
    nodemap_t attrs = rec.attributes();
    cout << "elm.attributes() = " << (void *)attrs << endl;
    
    cout << "elm.attributes().size() = " << attrs.size() << endl;

    nodemap_t::iterator b = attrs.begin();
    nodemap_t::iterator e = attrs.end();
    
/*    cout << (b == e) << endl;
    cout << "e - b = " << (e - b) << endl;
    cout << (*b).name() << endl;
    ++b;
    
    cout << (b == e) << endl;*/
    for_each(b, e, test_fn);
    
    wcout << "attr[0]: " << (XMLCh const *)attrs.item(0).name() << endl;
    
//    wcout << "doc.first_child().name() = " << doc.first_child().name() << endl;
//    wcout << "doc.first_child().get_attribute() = " << element_t((borg::xerces::traits::element_type)(borg::xerces::traits::node_type)doc.first_child()).get_attribute("cvs_revision") << endl;
//    wcout << "doc.first_child().first_child().next_sibling().name() = " << doc.first_child().first_child().next_sibling().name() << endl;
    
    
    nodelist_t children = doc.first_child().child_nodes();
    
    cout << "number of children: " << children.size() << endl;
    
  
  //  ns_resolver_t ns_r = doc.create_ns_resolver(doc.first_child());
  //  expression_t expr = doc.create_expression("/GCC_XML", ns_r);
      
    nodelist_t functions = doc.get_elements_by_tag_name("Function");
    nodelist_t methods = doc.get_elements_by_tag_name("Method");
    nodelist_t typedefs = doc.get_elements_by_tag_name("Typedef");
    nodelist_t arguments = doc.get_elements_by_tag_name("Argument");
    element_t no3 = doc.get_element_by_id("_3");
    
    cout << "number of functions: " << functions.size() << endl;
    cout << "number of methods: " << methods.size() << endl;
    cout << "number of typedefs: " << typedefs.size() << endl;
    cout << "number of arguments: " << arguments.size() << endl;
    
    element_t ex = doc.create_element("test");

    text_t txt = doc.create_text_node("blah blah blah");
    attribute_t at = doc.create_attribute("aha");
    
    wcout << "test elm: " << (XMLCh const *)ex.name() << endl;
  }
/*  catch(DOMXPathException const &e)
  {
    cerr << "DOMXPathException" << endl;
    error_code = 6;
  }
  catch(OutOfMemoryException const &e)
  {
    cerr << "OutOfMemoryException" << endl;
    error_code = 5;
  }*/
  catch(const ::XERCES_CPP_NAMESPACE::DOMException &e)
  {
    cerr << "DOMException code is:  " << e.code << endl;
    error_code = 2;
  }
/*  catch(exception const &e)
  {
    cerr << "e.what() = " << e.what() << endl;
  }
  catch(...)
  {
    cerr << "unknown exception" << endl;
  }*/

  cout << "done!" << endl;

  cout.flush();
  cerr.flush();
  
  borg::xerces::shutdown();
  return 0;
}
