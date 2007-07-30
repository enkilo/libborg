#include <iostream>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <io/filter/indent_output.hpp>

using namespace boost;
using namespace std;
using io::filter::indent_output;

int main()
{
  iostreams::filtering_ostream output;
  
  output.push(indent_output(' ', false));
  output.push(iostreams::file_descriptor_sink(1));

  indent_output &filter = *output.component<indent_output>(0);
  
  output << "test" << endl;
  
  filter.state().push(4);
  
  output << "line2" << endl;
  output << "line3" << endl;
  
  filter.state().pop();

  output << "line4" << endl;
  
  filter.state().pop();

  output << "line5" << endl;

  filter.state().set(0);
  
  output << "  line6" << endl;
}
