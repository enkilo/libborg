#include <iostream>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/MemBufFormatTarget.hpp>
#include <borg/xerces.hpp>

using namespace std;

int main()
{
  int error_code = 0;
  using namespace ::XERCES_CPP_NAMESPACE;

  try
  {
    using namespace borg::xerces::dom;
    using namespace borg::xerces;
    
    borg::xerces::initialize();

    MemoryManagerImpl *mman = new MemoryManagerImpl();
    
    mman->allocate(20);
    
    implementation impl;
    borg::string<traits::wchar_type, traits> encoding_str = "UTF-8";

    document_t doc = impl.create_document();

    membuf_output_buffer_t memory_target;
    localfile_output_buffer_t localfile_target("blah.xml");
//    stdout_output_buffer_t output_buffer;
  
    stream_output_buffer output_buffer(cout);
    
    doc.set_encoding(encoding_str);
    doc.set_actual_encoding(encoding_str);

//    cerr << "encoding: " << doc.get_encoding() << endl;
//    cerr << "actual encoding: " << doc.get_actual_encoding() << endl;

    writer_t writer = impl.create_dom_writer();
    
    element_t html = doc.create_element("html");
    element_t head = doc.create_element("head");
    element_t scpt = doc.create_element("script");
    element_t body = doc.create_element("body");
    element_t tabl = doc.create_element("table");
    element_t trow = doc.create_element("tr");

    tabl.set_attribute("border", "0");
    tabl.set_attribute("cellpadding", "2");
    
    scpt.set_attribute("language", "JavaScript");
    scpt.set_attribute("type", "text/javascript");
    scpt.set_attribute("src", "test.js");

    head.append_child(scpt);
    html.append_child(head);
    html.append_child(body);
    body.append_child(tabl);
    tabl.append_child(trow);

    text_t ctnt = doc.create_text_node("this is some test content... הצü...");

    body.append_child(ctnt);
    doc.append_child(html);

    writer.set_encoding(encoding_str);
    writer.write(output_buffer, doc);
    output_buffer.flush();
    
    output_buffer.stream() << endl;
    output_buffer.stream() << endl;
    
    writer.set_encoding("UTF-16");
    doc.set_encoding("UTF-16");
    doc.set_actual_encoding("UTF-16");

    writer.set_newline("\n");
//    writer.set_feature("format-canonical", true);
    writer.set_feature("format-pretty-print", true);
    
    writer.write(localfile_target, doc);
    writer.write(memory_target, doc);

    cout << "result: " << memory_target.get_raw_buffer() << endl;
  }
  catch(const XERCES_CPP_NAMESPACE::OutOfMemoryException &e)
  {
    std::cerr << "OutOfMemoryException" << std::endl;
    error_code = 5;
  }
  catch(const XERCES_CPP_NAMESPACE::DOMException &e)
  {
    std::cerr << "DOMException code is:  " << e.code << std::endl;
    error_code = 2;
  }
  catch(exception &e)
  {
    cerr << "e.what() = " << e.what() << endl;
  }
  catch(...)
  {
    cerr << "unknown exception" << endl;
  }

  cout << "done!" << endl;
  
  borg::xerces::shutdown();

//  XMLPlatformUtils::Terminate();
  return 0;
}
