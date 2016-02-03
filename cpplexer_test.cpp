/*=============================================================================
    Boost.Wave: A Standard compliant C++ preprocessor library

    http://www.boost.org/

    Copyright (c) 2001-2005 Hartmut Kaiser. Distributed under the Boost 
    Software License, Version 1.0. (See accompanying file 
    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/

#include <iostream>
//#include <iomanip>
//#include <fstream>
#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem/convenience.hpp>

// For indented output
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <io/filter/indent_output.hpp>

// Include Wave itself
#include <boost/wave.hpp>

// Include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

#include <boost/program_options.hpp>

#include <borg/color/rgb.hpp>
#include <borg/util/ansi_code.hpp>
#include <borg/util/ansi_color.hpp>
#include <borg/util/state_observer.hpp>

#define NUM_CONTEXTS 3

using namespace boost;

static int indent_step;

typedef tuple<wave::token_id, wave::token_id, int, const char *, const char *> context_type;
typedef array<context_type, NUM_CONTEXTS> contexts_type;

// current file position is saved for exception handling
static wave::util::file_position_type current_position;

// open an input file and push it to the filtering chain...
template<typename FilteringStreamT>
bool open_read(FilteringStreamT &stream, const std::string &name)
{
  using namespace iostreams;
  
  if(name == "-")
  {
    stream.push(file_descriptor_source(0));
    return true;
  }

  stream.push(file_source(name));
  return (stream.template component< 0, file_source >())->is_open();
}

void process_file(const std::string &filename, contexts_type &contexts)
{
  using namespace std;
  using namespace wave;
  
  iostreams::filtering_istream input;
  
  if(!open_read(input, filename))
  {
    cerr << "Could not open input file: " << filename << endl;
    return;
  }
  
  string instr;
  
  input.unsetf(ios::skipws);
  
  // need bidirectional iterators, so we buffer it into a string.
  instr = string(istreambuf_iterator<char>(input.rdbuf()),
                 istreambuf_iterator<char>());
  
  // create an output filter chain for indentation
  using namespace io;
  
  iostreams::filtering_ostream output;
  
  output.push(filter::indent_output(' ', false));
  output.push(iostreams::file_descriptor_sink(1));
  
  filter::detail::indentation_state &indent_state =
    output.component<filter::indent_output>(0)->state();
  
  // tokenize the input data into C++ tokens using the C++ lexer
  typedef cpplexer::lex_token<> token_type;
  typedef cpplexer::lex_iterator<token_type> lexer_type;
  typedef token_type::position_type position_type;
  
  position_type pos(filename.c_str());
  int support = (support_cpp|
#if BOOST_VERSION >= 103400
                 support_option_long_long
#else
                 support_long_long
#endif
                 );
  lexer_type it = lexer_type(instr.begin(), instr.end(), pos, language_support(support));
  lexer_type end = lexer_type();
  std::stack< boost::tuple<context_type *, bool> > ctxstack;
  
  while(it != end) 
  {
    token_type tok = *it;
    current_position = tok.get_position();  // for error reporting
    
    typedef cpplexer::lex_token<>::string_type string_type;
    
    int depth = indent_state.depth();
    
    if(!ctxstack.empty())
    {
      context_type &context = *ctxstack.top().get<0>();
      
      if(token_id(tok) == context.get<1>())
      {
        if(ctxstack.top().get<1>())
        {
          output << endl;
          output.flush();
        
          indent_state.pop();
        }
        
        ctxstack.pop();
      }
    }
      
    int fgcolor = borg::ansi::fgnd_white;
    
    if(IS_CATEGORY(tok, KeywordTokenType) || IS_CATEGORY(tok, BoolLiteralTokenType))
      fgcolor = borg::ansi::fgnd_red;
    else if(IS_CATEGORY(tok, OperatorTokenType)
            || IS_CATEGORY(tok, StringLiteralTokenType)
            || IS_CATEGORY(tok, IntegerLiteralTokenType)
            || IS_CATEGORY(tok, CharacterLiteralTokenType)
//            || (CATEGORY_FROM_TOKEN(tok) & LiteralTokenType) && (CATEGORY_FROM_TOKEN(tok) &  ~LiteralTokenType)
            )
      fgcolor = borg::ansi::fgnd_cyan;
    else if(IS_CATEGORY(tok, IdentifierTokenType))
      fgcolor = borg::ansi::fgnd_yellow;
    else //if(IS_CATEGORY(tok, PPTokenType) && IS_CATEGORY(tok, LiteralTokenType))
      fgcolor = borg::ansi::fgnd_green;
      
    output << borg::ansi_color_code(fgcolor, borg::ansi::attr_bold);    
    output << tok.get_value();
    output << borg::ansi_color_code(borg::ansi::attr_normal);
    
    if(!ctxstack.empty())
    {
      if(token_id(tok) == T_COMMA && ctxstack.top().get<1>())
      {
        output << endl;
        output.flush();
      }
    }
    
    for(int i = 0; i < NUM_CONTEXTS; ++i)
    {
      if(token_id(tok) == contexts[i].get<0>())
      {
        bool indent = false;
        
        if(indent_state.depth() < contexts[i].get<2>())
        {
          output << endl;
          output.flush();

          indent_state.push(indent_step);
          indent = true;
        }

        ctxstack.push(make_tuple(&contexts[i], indent));
      }
    }
    
    ++it;
  }

  output.flush();
}
   
struct notifier
{
  template<typename ObserverT>
  static void
  notify(ObserverT &observer)
  {
    std::cout << "notify(" << observer << ")" << std::endl;
  }
};

// main entry point
int main(int argc, char *argv[])
{
  using namespace std;
  using namespace borg;
  using namespace wave;

  try 
  {
    filesystem::path name(argv[0], filesystem::native);
      
    vector<string> input_files;
    contexts_type contexts;
    
    state_observer<int, notifier> observe = 
      state_observe(int(4), notifier());
    
    observe = 6;
    observe = 8;
    
    ansi_sequence<> ansi = ansi_color_code(ansi::fgnd_blue, ansi::bgnd_black, ansi::attr_bold);
    ansi_sequence<> none = ansi_color_code(ansi::attr_normal);

    
   // rgb<bool> color(true,true,false);
    rgb<double> color(1.0, 0.0, 1.0);
    
    borg::ansi_color c_test(color, true);
    
    cout << (int)c_test.scalar() << endl;
    cout << c_test.red() << endl;
    cout << c_test.green() << endl;
    cout << c_test.blue() << endl;

//    ansi.cmd('e');
//    ansi.add(1);
    
    cout << none.to_string("ESC") << endl;
    cout << ansi.to_string("\033") << endl;
    cout << ansi_color_code(ansi::fgnd_blue) << "this should be blue" << none << endl;
    
//    cout << ansi << endl;
    
    contexts[0] = make_tuple(T_LESS, T_GREATER, 0, "template-args,t", "break template argument list up to this depth");
    contexts[1] = make_tuple(T_LEFTPAREN, T_RIGHTPAREN, 0, "parenthesis,p", "break parenthesis up to this depth");
    contexts[2] = make_tuple(T_LEFTBRACKET, T_RIGHTBRACKET, 0, "brackets,b", "break brackets up to this depth");
    
    // parse command line options...
    using namespace program_options;
      
    command_line_parser parser(argc, argv);
    options_description desc("Usage: " + filesystem::basename(name) + " [options] file ...");
    positional_options_description pd;

    desc.add_options()
      ("help,h", "print out program usage (this message)")
      ("input-file", value(&input_files), "input file(s)")
      ("indent-step,i", value(&indent_step)->default_value(4), "number of indentation characters");
    
    for(int i = 0; i < NUM_CONTEXTS; ++i)
    {
      desc.add_options()
        (contexts[i].get<3>(),
         value(&contexts[i].get<2>())->default_value(contexts[i].get<2>()), 
         contexts[i].get<4>());
    }
    
    pd.add("input-file", -1);
      
    parser.options(desc);
    parser.positional(pd);
    parser.style(command_line_style::unix_style);

    program_options::variables_map vm;
    program_options::parsed_options opts = parser.run();

    store(opts, vm);
    notify(vm);

    if(vm.count("help"))
    {
      cout << desc << endl;
      return 1;
    }
      
    // if there is no input file given, then exit
    if(!input_files.size())
    {
      cerr 
        << filesystem::basename(name) << ": No input file given. "
        << "Use --help to get a hint." << endl;
      
      return 5;
    }
    
    for_each(input_files.begin(), 
             input_files.end(), bind(process_file, _1, contexts));
  }
  
  
  catch(cpplexer::lexing_exception &e)
  {
    // some lexing error
    cerr
      << e.file_name() << "(" << e.line_no() << "): "
      << e.description() << endl;

    return 2;
  }
  
  catch(exception &e) 
  {
    // use last recognized token to retrieve the error position
    cerr 
      << current_position.get_file() 
      << "(" << current_position.get_line() << "): "
      << "exception caught: " << e.what()
      << endl;
    
    return 3;
  }

  catch(...)
  {
    // use last recognized token to retrieve the error position
    cerr 
      << current_position.get_file() 
      << "(" << current_position.get_line() << "): "
      << "unexpected exception caught." << endl;

    return 4;
  }

  return 0;
}
