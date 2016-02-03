#define PRINT_EXPR(expr) std::cout << #expr ": " << (expr) << std::endl;

#include <yaml.h>
#include <cstdio>
#include <iostream>
#include <exception>
#include <borg/yaml.hpp>

int main()
{
  try
  {
  using namespace std;
  using namespace borg;
  
  cout << "yaml version: " << yaml_get_version_string() << endl;

  using namespace yaml;
  
  emitter e;
  
  e.set_output_file(stdout);
  e.set_encoding(YAML_UTF8_ENCODING);
  
  yaml_event_t ev;
  
//  yaml_stream_start_event_initialize(&ev, YAML_UTF8_ENCODING);
//  PRINT_EXPR( ev.type )
//  yaml_event_delete(&ev);
//  PRINT_EXPR( ev.type )

  PRINT_EXPR( event::stream_start().get_type() )
  
//  e << event::stream_start();
  
  document doc;

  PRINT_EXPR( doc.get_version_directive() )
  
  typedef unsigned char *str_t;
      
  int seq_id = doc.add_sequence((str_t)"test-seq");
    
  PRINT_EXPR( seq_id )
    
  doc.append_sequence_item(
      seq_id, 
      doc.add_scalar((str_t)"member-1-value")
  );

  doc.append_sequence_item(
      seq_id, 
      doc.add_scalar((str_t)"seq-member-2", (str_t)"member-2-value")
  );
    
  node_id map_id = doc.add_mapping(default_mapping_tag);
    
  doc.append_mapping_pair(
      map_id,
      doc.add_scalar((str_t)"key-1-value"), 
      doc.add_scalar((str_t)"member-1-value")
  );

  doc.append_mapping_pair(
      map_id, 
      doc.add_scalar((str_t)"key-2-tag", (str_t)"key-1-value"),
      doc.add_scalar((str_t)"member-1-value")
  );

  doc.append_sequence_item(
      seq_id, 
      map_id
  );
    
  PRINT_EXPR( map_id )
  PRINT_EXPR( map_id.get_tag(doc) )
  PRINT_EXPR( map_id.get_type(doc) )
    
  e << doc;  
  e.flush();

  }
  catch(std::exception const &e)
  {
    std::cerr << "Exception: " << e.what() << std::endl;
  }
  
  return 0;
}
