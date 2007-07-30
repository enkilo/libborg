//#define BOOST_SPIRIT_DEBUG

#include <iostream>
#include <vector>
#include <string>
#include <xpdf/PDFDoc.h>
#include <xpdf/TextOutputDev.h>
#include <xpdf/GlobalParams.h>

//#include <boost/lambda/lambda.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/iterator/position_iterator.hpp>

#include <recls/cpp/fileentry.hpp>
#include <recls/cpp/filesearch.hpp>
#include <recls/implicit_link.h>  

#include "io/container_sink.hpp"
#include "io/filter/printable_chars.hpp"
#include "io/filter/predicate_filter.hpp"
#include <borg/util/string.hpp>
#include <borg/util/algorithm.hpp>
#include <borg/nlp/grammar.hpp>
#include <borg/nlp/skipper.hpp>

using borg::stdcxx::string;

class pdf_exception : public std::exception
{
public:
  pdf_exception(const string &msg) : m_what(msg) {}
  ~pdf_exception() throw() {}  
  const char *what() const throw() { return m_what.c_str(); }

private:
  string m_what;
};

/// outputs text to an output stream.
class stream_output_device : public TextOutputDev
{
public:
  stream_output_device(std::ostream &stream)
    : TextOutputDev(&output_fn, static_cast<void *>(&stream), gFalse, gTrue)
  {}
  
private:
  static void
  output_fn(void *stream, char *text, int len)
  {
//    std::cout << "output_fn(" << stream << ", '" << std::string(text, len) << "', " << len << std::endl;
    
    std::ostream *osp = static_cast<std::ostream *>(stream);
    osp->write(text, len);
  }
};


void process_language(const string &text)
{
  using namespace borg::nlp;
  
  skipper skip_p;
  grammar< traits<english> > p;

#ifdef BOOST_SPIRIT_DEBUG
  BOOST_SPIRIT_DEBUG_NODE(skip_p);
  BOOST_SPIRIT_DEBUG_NODE(p);
#endif

/*  string::const_iterator first = text.begin();
  string::const_iterator last = text.end();
  
  parse_info<string::const_iterator> 
  info = nlp::parse(first, last, p, skip_p);
  
  if(info.full)
  {
    std::cerr << "Parses OK" << std::endl;
  }
  else
  {
    std::cerr << "Parsing failure:" << std::endl;
    std::cerr << string(info.stop, last) << std::endl;
  }
*/
//  typedef position_iterator<std::string::const_iterator> iterator_type;
  typedef string::const_iterator iterator_type;
  typedef node_val_data_factory<> factory_type;
    
//  iterator_type first(text.begin(), text.end());
  iterator_type first = text.begin();
  iterator_type last = text.end();
  
  tree_parse_info<iterator_type, factory_type> 
  info = pt_parse(first, last, p, skip_p);
  
  if(info.full)
  {
    std::cout << "got trees" << std::endl;
  }
  
}

void process_pdf(const string &filename)
{
  using borg::util::array;
  using std::cout;
  
  PDFDoc *pdf;
  
  try
  {
    GString fname(filename);
    pdf = new PDFDoc(&fname);
  
    // check for copy permission
    if(!pdf->okToCopy())
      throw std::logic_error(filename + " is copy protected");
  
    if(!pdf->isOk())
      throw std::logic_error(filename + " could not be opened");
    
    typedef io::container_sink<char, string> sink_type;
    sink_type sink;

    boost::iostreams::stream<sink_type> output(sink);
    boost::iostreams::filtering_ostream out;
    
    // filter non-whitespace control-chars...
    out.push(io::filter_if(boost::is_cntrl() && !boost::is_space()));
    out.push(sink);
    
    TextOutputDev *textOut = new stream_output_device(out);
    
    if(textOut->isOk())
    {
      pdf->displayPage(textOut, 1, 72, 72, 0, gFalse, gTrue, gFalse);
    }

    out.flush();

    sink_type *psink = out.component<1, sink_type>();

    // split lines
    std::cout << "lines: " << psink->container().split('\n').size() << std::endl;
    std::cout << psink->container().c_str() << std::endl;
    
    // split words
    array<string> words;
    boost::split(words, psink->container(), boost::is_space());
    std::cout << "words: " << words.length << std::endl;
    std::for_each(words.begin(), words.end(), borg::puts);

//    process_language(psink->container());
    process_language("This is a sentence. This is the 2nd.");
    
    cout.flush();

    delete textOut;
  }
  catch(std::exception &e)
  {
    std::cerr << "Exception while processing " << filename << ": " << e.what() << std::endl;
  }

//  if(pdf)
//    delete pdf;
}

int main(int argc, char *argv[])
{
  using std::cerr;
  using std::endl;
  
  try
  {
    globalParams = new GlobalParams((char *)"xpdf.conf");
    
    using namespace recls;
    using recls::uint32_t;
    
    uint32_t flags = RECLS_F_FILES/* | RECLS_F_RECURSIVE*/;

    cpp::FileSearch srch((argv[1] ? argv[1] : "."), "*.pdf", flags);
    
    for(; srch.HasMoreElements(); srch.GetNext())
    {
      cpp::FileEntry entry = srch.GetCurrentEntry();
      
      std::cout << entry.GetPath() << ":" << std::endl;
      process_pdf(entry.GetPath());
    }
    
  }
  catch(std::exception &e)
  {
    cerr << "e.what() = " << e.what() << endl;
  }
   catch(...)
  {
    cerr << "unknown exception" << endl;
  }
  
  cerr << "done!" << endl;
  
  return 0;
}
