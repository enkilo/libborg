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

/*void attr_fn(xerces::dom::node_t const &n)
{
}*/

template<class AttributeT>
void test_fn(AttributeT const &a)
{
  wcout << a.name() << "=\"" << a.value() << "\"" << endl;
}

template<class NodeT>
void node_fn(NodeT const &n)
{
  using namespace borg::xerces::dom;
  
  if(n.type() == borg::xml::dom::element_node)
  {
    element_t elm(n);    
    cout << "element name: " << n.name() << endl;
    
//    nodemap_t map = elm.attributes();
//    for_each(map.begin(), map.end(), test_fn);
//    nodemap_t map = elm.attributes();
    for_each(elm.attributes().begin(), elm.attributes().end(), test_fn<attribute_t>);
  }
  else if(n.type() == borg::xml::dom::attribute_node)
  {
    cout << n.name() << "=\"" << n.value() << "\"" << endl;
  }
}

template<class Traits>
void test()
{
  using namespace borg::xml::dom;
  
  parser<Traits> p;

  cout << "parser: " << (void *)p << endl;
  
  std::string filename = "xerces_parser_utf16.xml";
  
  p.parse_file((char *)filename.c_str());
  
  cout << "p.error() = " << p.error() << endl;
  
  // get the DOM representation
  document_t<Traits> doc = p.document();
  
  wcout << "encoding is: " << doc.get_actual_encoding() << endl;
  
  if(!doc)
    throw logic_error("document is NULL");
  
  if(!doc.first_child())
    throw logic_error("document has no child nodes");
  
  wcout << "doc.name() = " << doc.name() << endl;
  wcout << "doc.type() = " << doc.type() << endl;
  
  element_t<Traits> elm = doc.first_child();
  cout << "doc.first_child() = " << (void *)elm << endl;
  
  element_t<Traits> rec = elm.first_child().next_sibling();
  wcout << "rec.name = " << rec.name() << endl;
  
  nodemap_t<Traits> attrs = rec.attributes();
  cout << "elm.attributes() = " << (void *)attrs << endl;
  
  cout << "elm.attributes().size() = " << attrs.size() << endl;
  
  typename nodemap_t<Traits>::iterator b = attrs.begin();
  typename nodemap_t<Traits>::iterator e = attrs.end();
  
  for_each(b, e, test_fn< attribute_t<Traits> >);
  
  wcout << "attr[0]: " << attrs.item(0).name() << endl;
    
  wcout << "doc.first_child().name() = " << doc.first_child().name() << endl;
  wcout << "doc.first_child().get_attribute() = " << element_t<Traits>((borg::xerces::traits::element_type)(borg::xerces::traits::node_type)doc.first_child()).get_attribute("cvs_revision") << endl;
  wcout << "doc.first_child().first_child().next_sibling().name() = " << doc.first_child().first_child().next_sibling().name() << endl;
  
  nodelist_t<Traits> children = doc.first_child().child_nodes();
  
  cout << "number of children: " << children.size() << endl;
  
  nodelist_t<Traits> functions = doc.get_elements_by_tag_name("Function");
  nodelist_t<Traits> methods = doc.get_elements_by_tag_name("Method");
  nodelist_t<Traits> typedefs = doc.get_elements_by_tag_name("Typedef");
  nodelist_t<Traits> arguments = doc.get_elements_by_tag_name("Argument");
  element_t<Traits> no3 = doc.get_element_by_id("_3");
  
  cout << "number of functions: " << functions.size() << endl;
  cout << "number of methods: " << methods.size() << endl;
  cout << "number of typedefs: " << typedefs.size() << endl;
  cout << "number of arguments: " << arguments.size() << endl;
  
  element_t<Traits> ex = doc.create_element("test");
  
  text_t<Traits> txt = doc.create_text_node("blah blah blah");
  attribute_t<Traits> at = doc.create_attribute("aha");
    
  wcout << "test elm: " << ex.name() << endl;
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

    test<borg::xerces::traits>();
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
