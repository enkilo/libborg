#include <iostream>
#include <string>
#include <vector>

// basic boost facilities
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/filesystem/convenience.hpp>

// for indented output
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <io/filter/indent_output.hpp>

// include Wave itself
#include <boost/wave.hpp>

// include the lexer stuff
#include <boost/wave/cpplexer/cpp_lex_token.hpp>    // token class
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp> // lexer class

#include <boost/program_options.hpp>

//#include <borg/color/rgb.hpp>
#include <borg/util/ansi_code.hpp>
#include <borg/util/ansi_color.hpp>
#include <borg/util/state_observer.hpp>

// backward compatibility for boost::wave versions prior to 1.34.0
#if BOOST_VERSION < 103400
#define support_option_long_long support_long_long
#endif

using namespace boost;

static int indent_step;

//!< 3-bit per pixel color (maps to the 8 ANSI colors).
typedef borg::rgb<bool> color_type;

//!< hiliting colors.
static color_type c_identifier, c_keyword, c_operator, c_literal, c_comment;

typedef boost::tuple< wave::token_id, wave::token_id, int, const char *, const char * > context_def_type;

//typedef array< context_def_type, NUM_CONTEXTS > contexts_type;

// current file position is saved for exception handling
static wave::util::file_position_type current_position;

// open an input file and feed from it the given filtering chain...
template<class FilteringStream>
bool 
open_read(FilteringStream &stream, const std::string &name)
{
  using namespace iostreams;
  
  if(name == "-")
  {
    stream.push(file_descriptor_source(0));
    return true;
  }

  stream.push(file_source(name));
  return (stream.template component<0, file_source>())->is_open();
}

void
process_file(const std::string &filename, context_def_type contexts[])
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

  lexer_type end = lexer_type();
  lexer_type it = lexer_type
    (instr.begin(), instr.end(), pos, language_support(support_cpp|support_option_long_long));

  typedef boost::tuple<context_def_type *, bool> context_type;
  
  stack<context_type> ctxstack;
  
  while(it != end) 
  {
    token_type tok = *it;
    current_position = tok.get_position();  // for error reporting
    
    typedef cpplexer::lex_token<>::string_type string_type;
    
/*    int depth = indent_state.depth();
    
    if(!ctxstack.empty())
    {
      context_def_type &context = *ctxstack.top().get<0>();
      
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
    }*/
      
    borg::ansi_color fgcolor = borg::ansi::fgnd_white;
    
    if(IS_CATEGORY(tok, KeywordTokenType) || IS_CATEGORY(tok, BoolLiteralTokenType))
      fgcolor = borg::ansi::fgnd_red;

    else if(IS_CATEGORY(tok, OperatorTokenType) ||
            IS_CATEGORY(tok, StringLiteralTokenType) ||
            IS_CATEGORY(tok, IntegerLiteralTokenType) ||
            IS_CATEGORY(tok, CharacterLiteralTokenType))
      fgcolor = borg::ansi::fgnd_cyan;

    else if(IS_CATEGORY(tok, IdentifierTokenType))
      fgcolor = borg::ansi::fgnd_yellow;

    else //if(IS_CATEGORY(tok, PPTokenType) && IS_CATEGORY(tok, LiteralTokenType))
      fgcolor = borg::ansi::fgnd_green;

    output << borg::ansi_color_code(fgcolor.scalar(), borg::ansi::attr_bold);    
    output << tok.get_value();
    output << borg::ansi_color_code(borg::ansi::attr_normal);
    
/*    if(!ctxstack.empty())
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
    }*/
    
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
int 
main(int argc, char *argv[])
{
  using namespace std;
  using namespace borg;
  using namespace wave;

  static context_def_type contexts[] = 
  {
    make_tuple(T_LESS, T_GREATER, 0, "template-args,t", "break template argument list up to this depth"),
    make_tuple(T_LEFTPAREN, T_RIGHTPAREN, 0, "parenthesis,p", "break parenthesis up to this depth"),
    make_tuple(T_LEFTBRACKET, T_RIGHTBRACKET, 0, "brackets,b", "break brackets up to this depth")
  };
    
  //!< hilite color option.
  typedef boost::tuple<const char *, color_type *> hilite_type;
  
  //!< array of hilite color options (used to initialize options_desc for config file parsing).
  static hilite_type hilite_colors[] = 
  {
    make_tuple("identifier", &c_identifier),
    make_tuple("keyword", &c_keyword),
    make_tuple("operator", &c_operator),
    make_tuple("literal", &c_literal),
    make_tuple("comment", &c_comment),
  };

  try 
  {
    filesystem::path name(argv[0], filesystem::native);
      
    vector<string> input_files(1, string("-"));

    // parse command line options...
    using namespace program_options;
      
    command_line_parser parser(argc, argv);
    options_description desc("Usage: " + filesystem::basename(name) + " [options] file ...");
    positional_options_description pd;

    desc.add_options()
      ("help,h", "print out program usage (this message)")
      ("input-file", value(&input_files), "input file(s)")
      ("indent-step,i", value(&indent_step)->default_value(4), "number of indentation characters");
    
    // add context tracking options.
    BOOST_FOREACH(context_def_type scx, contexts)
    {
      desc.add_options()
        (scx.get<3>(), value(&scx.get<2>())->default_value(scx.get<2>()), scx.get<4>());
    }
    
    pd.add("input-file", -1);
      
    parser.options(desc);
    parser.positional(pd);
    parser.style(command_line_style::unix_style);

    program_options::variables_map vm;
    program_options::parsed_options opts = parser.run();

    ifstream cfg("codegrep.conf");

    options_description colors;
    
    // add hilite color options.
    BOOST_FOREACH(hilite_type h, hilite_colors)
    {
      colors.add_options()
        (h.get<0>(), value(h.get<1>()), h.get<0>());
    }

    store(opts, vm);
    store(program_options::parse_config_file(cfg, colors), vm);

    notify(vm);

    cout << "identifier color: " << c_identifier << endl;
    cout << "operator color: " << c_operator << endl;
    cout << "comment color: " << c_comment << endl;
  
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

    // process input files...
    try {
      for_each(input_files.begin(), 
               input_files.end(), bind(process_file, _1, contexts));
    }
    catch(cpplexer::lexing_exception &e)
    {
      // some lexing error
      cerr << e.file_name() << "(" << e.line_no() << "): "
           << e.description() << endl;
      
      return 2;
    }
  }
  // basically all exceptions.
  catch(exception &e) 
  {
    cerr << "exception caught: " << e.what() << endl;    
    return 3;
  }
  // definitely all exceptions.
  catch(...)
  {
    cerr << "unexpected exception caught." << endl;
    return 4;
  }

  return 0;
}
