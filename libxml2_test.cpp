#include <iostream>
#include <exception>
#include <algorithm>
#include <libxml/parser.h>
#include <boost/integer_traits.hpp>
#include <boost/foreach.hpp>

#include <borg/libxml2/list.hpp>
#include <borg/libxml2/dom/adapters.hpp>
#include <borg/libxml2/xpath/adapters.hpp>

using std::cout;
using std::cerr;
using std::endl;
using std::for_each;
using std::exception;

#define PRINT_EXPR(expr) std::cout << #expr ": " << (expr) << std::endl;


void node_fn(const borg::libxml2::dom::node_t &n)
{
  cout << "node name: " << n.name() << endl;
}

void attr_fn(const borg::libxml2::dom::attribute_t &n)
{
  cout << n.name() << "=\"" << n.value() << "\"" << endl;
}

int main()
{
//  xmlParserCtxt ctx;
//  xmlParserCtxtPtr ctx_ptr;
  try
  {

    LIBXML_TEST_VERSION
      //  xmlInitParser();
      //  xmlInitParserCtxt(&ctx);
      //
    using namespace borg::libxml2;
    using namespace borg::libxml2::dom;
    using namespace borg::libxml2::xpath;
    
    
    list<void *> test_list;
    
    parser_t parser = xmlNewParserCtxt();
//    parser.parse_file("xerces_parser.xml");
    parser.parse_file("xmllint.xml");
    
    if(parser.error())
    {
      cerr << "error!" << endl;
      return 1;
    }
    
    document_t doc = parser.document();
    element_t root = doc.root();
   
    cout << "test" << endl;
 
    attribute_t attr = root.get_attribute_node("cvs_revision");  
    node_t first = root.first_child().next_sibling();

//    expression expr("/GCC_XML");
//    evaluator eval(doc);

    evaluator eval(doc);
    expression_t expr = eval.compile("//Typedef[@id=\"_223\"]");
    
    cout << "xpath expression: " << (void *)expr << endl;

    result_t res = eval.eval(expr);
    
    if(res.type() == res.nodeset_result)
    {
      nodeset_t nset = res.nodeset();
    
      if(!nset.empty())
      {
        std::for_each(nset.begin(), nset.end(), node_fn);
      
        nodemap_t attrs = element_t(*nset.begin()).attributes();
    
        cout << "xpath result: " << (void *)res << endl;
        cout << "xpath nodeset: " << (void *)nset << endl;
        cout << "xpath nodeset size: " << nset.size() << endl;

        nodemap_t::iterator b = attrs.begin();
        nodemap_t::iterator e = attrs.end();

        for_each(b, e, attr_fn);
      }
    }
    

//    cout << "cmp=" << (++b == e) << endl;
//    cout << "n attrs: " << attrs.item(0).name() << endl;

    cout << "n children: " << root.child_nodes().size() << endl;
    
    idref_t idref("_766", doc);
    
//    cout << "*idref(_223) = " << (*idref).name() << endl;
    cout << "*idref(_766)->name() = " << idref->name() << endl;
    
    idreflist_t reflist = idref->get_attribute_node("members");
    
    idreflist_t::iterator refit = reflist.begin();
    idreflist_t::iterator refend = reflist.end();
    
    cout << "members: " << idref->get_attribute("members") << endl;

//    while(!refit.equal(refend))
    while(refit != refend)
    {
      cout << "ref: " << refit.ref() << endl;
      cout << "elm: " << (*refit).name() << endl;
      ++refit;
    }
  
//    PRINT_EXPR( std::ispunct('_') )
    
/*    BOOST_FOREACH(element_t elm, reflist)
    {
      cout << "element name: " << elm.name() << endl;
    }
  */  
    
//    for_each(root.child_nodes().begin(), root.child_nodes().end(), node_fn);
exit(0);

  }
  catch(const exception &e)
  {
    cerr << "exception: " << e.what() << endl;
  }
  catch(...)
  {
    cerr << "unknown exception" << endl;
  }
  
}

