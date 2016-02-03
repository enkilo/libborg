#include <iostream>
#include <boost/foreach.hpp>
#include <borg/util/array.hpp>
#include <borg/ast/algorithms.hpp>
#include <borg/ast/node.hpp>
#include <borg/ast/scoped.hpp>
#include <borg/ast/function.hpp>
#include <borg/gccxml.hpp>
#include <borg/gccxml/libxml2.hpp>

using namespace std;
using namespace borg;
using namespace libxml2;

using borg::exception;

static class blah_class
{
  int m;
  
} blah_object;

void ast_test()
{
  dom::parser p;
  dom::document_t doc;

  if(p.parse_file("array_test.xml", dom::parse_noblanks))
    doc = p.document();
  
  cerr << "document: " << (void *)doc << endl;
  
  gccxml::tree_t tree(doc);
  
/*  typeof(tree.children.begin()) it = tree.children.begin();
  typeof(tree.children.begin()) end = tree.children.end();
  
  gccxml::node_t n = *it;
  ++it;
  it == it;*/
  
  BOOST_FOREACH(gccxml::node_t n, tree.children) {
    
    if(n.is_named())
      cout << ast::name(n) << "(\"" << gccxml::named_t(n).name() << "\")";
    else
      cout << ast::name(n);
    
    cout << ": " << n << endl;
  }
  
  
  dom::element_t gcc_xml = doc.first_child();
  util::array< gccxml::function_t > function_list;

  int nelems = 0;

  BOOST_FOREACH(dom::element_t elm, gcc_xml.child_nodes())
  {
    ++nelems;
    gccxml::node_t node(elm);
    
    if(node.id() == gccxml::namespace_node)
    {
      try
      {
//      if(gccxml::namespace_t(node).context())
        cout << "namespace: " << gccxml::namespace_t(node) << endl;
      }
      catch(const std::exception &e)
      {
        cerr << e.what() << endl;
      }      
    }

    if(elm.name() == "Function")
    {
      gccxml::function_t fn = elm;
      function_list.push(fn);
    }
  }

  cout << "Number of elements: " << nelems << endl;
  cout << "Function list size: " << function_list.size() << endl;

  libxml2::string id = "_1213c";
  dom::element_t elm = doc.get_element_by_id(id);

  if(elm)
    cout << "Element with id=" << id << ": " << /*(string_t)*/elm.name() << endl;  
}

int main(int argc, char *argv[])
{
  try {
    ast_test();
  }
  catch(const std::exception &e) {
    cerr << "Exception: " << e.what() << endl;
  }
  
  return 0;
}
