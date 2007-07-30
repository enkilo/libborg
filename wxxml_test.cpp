#include <iostream>
#include <wx/xml/xml.h>
#include <borg/xml/dom/adapters.hpp>
#include <borg/wx/dom/parser.hpp>
#include <borg/wx/dom/document.hpp>
#include <borg/wx/string.hpp>

int main()
{
  using namespace std;
  using borg::wx::string;
  using namespace borg::wx::dom;

  parser p;
  
  p.parse_file("xerces_parser.xml");
  
  string blah = "test";
  
  wxXmlDocument *doc = p.document();
  wxXmlNode *root = p.document().root();
  
  cout << "isOk: " << doc->IsOk() << endl;
  cout << "version: " << doc->GetVersion() << endl;
  cout << "root node: " << root << endl;
  cout << "root name: " << root->GetName() << endl;
  
  return 0;
}
