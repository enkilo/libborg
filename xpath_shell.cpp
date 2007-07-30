#include <cstring>
#include <cerrno>
#include <cstdio>
#include <exception>

#include <readline/readline.h>
#include <readline/history.h>

//#include <boost/array.hpp>
#include <boost/ref.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/timer.hpp>
#include <boost/program_options.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/core/scanner/skipper.hpp>
#include <boost/spirit/tree/parse_tree.hpp>

#include <borg/util/array.hpp>
#include <borg/util/string.hpp>
#include <borg/util/command_parser.hpp>
#include <borg/libxml2.hpp>
#include <borg/preproc.hpp>

//using namespace borg::libxml2;
using namespace boost;
//using namespace std;

using std::cout;
using std::cerr;
using std::endl;
using std::exception;
using std::for_each;
using std::logic_error;
using std::pair;

using borg::util::array;
using borg::stdcxx::string;
using borg::command_parser;
using borg::lexical_function;
using borg::lexical_call;

static string program_name;

static array<string> input_files;

static bool running = true;  
static array<borg::libxml2::dom::document_t> document_list;

//---------------------------------------------------------------------------
borg::libxml2::dom::document_t
open_document
  (const filesystem::path &file, 
   const borg::libxml2::dom::parser::option &opt = borg::libxml2::dom::parse_noblanks)
{
  using namespace borg::libxml2::dom;

  timer parse_time;
  parser p;

  cerr << "Parsing '" << file.string() << "'... ";
  cerr.flush();

  p.parse_file(file.string().c_str(), opt);

  if(p.document())
    cerr << "ok (completed in " << parse_time.elapsed() << " seconds)" << endl;
  else
    cerr << "failed" << endl;
  
  return p.document();
}

//---------------------------------------------------------------------------

void
print_xml(const borg::libxml2::dom::writer &w, const borg::libxml2::dom::node_t &n)
{
  w.write(n);

  if(!w.get_indent())
    w.write("\n");

  w.flush();
}

//---------------------------------------------------------------------------
void
evaluate_expr(borg::libxml2::xpath::evaluator &eval, const string &expr_str)
{
  using namespace borg::libxml2::xpath;

  expression_t expr = eval.compile(expr_str.c_str());
  
  if(!expr)
  {
    cerr << "Failed compiling xpath expression: " << expr_str << endl;
    return;
  }

//  cerr << "evaluate_expr: " << expr_str << endl;

  cerr << "Compiled expression: " << expr_str.c_str() << endl;
  cerr.flush();

  result_t res = eval(expr);
  
  if(!res)
  {
    cerr << "No XPath result!" << endl;
    return;
  }
  
  if(res.type() == res.nodeset_result)
  {
    nodeset_t ns = res.nodeset();

    
/*    void print(MyObject &myobj, int)
    {
    }
    
    
    class fear_print
    {
      MyObject &myobj;
      
      operator()(int i)
      {
        print(myobj, i);
      }
      
    };
    
    
    std::vector<int> intv;
    
    std::list<int> intl;
    
    MyObject myobj;
    fear_print pr_functor;
    
    pr_functor(sdgkshg);
    
    std::for_each(intv.begin(), intv.end(), bind(print_int, ref(myobj), _1));
      
    BOOST_FOREACH(std::pair(intv.begin(), intv.end())
    
                  
    array.each { ¦index¦ 
    jhsadjksad
        sadsa
        
        dsa
    }
    
*/
    cerr << "type is nodeset ";
    
    if(!ns.empty())
    {
      cerr << "(" << ns.size() << " nodes):" << endl;
      
      using namespace borg::libxml2::dom;
      
      borg::libxml2::output_buffer buf(stdout);
      writer wr(buf);
      
      wr.set_indent("  ");
      
      for_each(ns.begin(), ns.end(), bind(print_xml, ref(wr), _1));
    }
    else
    {
      cerr << "(empty)" << endl;
    }
  }
  else
  {
    cerr << "type is " << res.typestr() << endl;
    
    switch(res.type())
    {
      case result_t::string_result:
      {
        cerr << "value is " << res.string() << endl;
        break;
      }

      case result_t::number_result:
      {
        cerr << "value is " << res.number() << endl;
        break;
      }

      case result_t::boolean_result:
      {
        cerr << "value is " << (res.boolean() ? "true" : "false") << endl;
        break;
      }

      case result_t::undefined_result:
      {
        cerr << "value is " << res.typestr() << endl;
        break;
      }
    }
  }
}
  
//---------------------------------------------------------------------------
class command_handler : public command_parser< array<string> >
{
public:
  command_handler()
  {
    add_command("exit", &command_handler::bye,  "Exits the XPath shell.");
    add_command("quit", &command_handler::bye,  "Synonyme for 'exit'.");
    add_command("bye",  &command_handler::bye,  "Synonyme for 'exit'.");
    add_command("list", &command_handler::list, "Lists the loaded documents.");
    add_command("load", &command_handler::load, "Loads a new document.");
    add_command("eval", &command_handler::eval, "Evaluate an XPath expression.");
    add_command("help", &command_handler::help, "Show this help.");
    
    // By default, parse as XPath expression.
    set_default(&command_handler::eval);
  }
  
  static void
  help()
  {
  }

  static void
  bye()
  {
    running = false;
  }

  static void
  list()
  {
//    cerr << "Document list" << endl;
//    cerr << "--------------------------------" << endl;
    
    BOOST_FOREACH(string &filename, input_files)
    {
      cerr << filename << endl;
    }
  }
  
  static bool
  load(const std::string &file)
  {
    using namespace borg::libxml2::dom;
    
    document_t doc = open_document(file.c_str());
      
    if(doc)
    {
      input_files.push_back(file);
      document_list.push_back(doc);
      
      
//      borg::libxml2::string refstr("_123");
      idref_t ref("_2469", doc);
      
      std::cout << "ref name: " << (*ref).name() << std::endl;
//      std::cout << "ref: " << (void *)(*ref) << std::endl;
      
      return true;
    }
    
    return false;
  }
  
  static void
  eval(const std::string &expr)
  {
    if(document_list.empty())
    {
      cerr << "No documents loaded. Use 'load <file>'." << endl;
      return;
    }
    
    using namespace borg::libxml2::dom;
    
    BOOST_FOREACH(document_t doc, document_list)
    {
      using namespace borg::libxml2::xpath;
      
      evaluator eval(doc);
      evaluate_expr(eval, expr.c_str());
    }
  }
  
};

// Loads a document and evaluates the given XPath expressions on it.
//---------------------------------------------------------------------------
void
process_file(const filesystem::path &input, const array<string> &expressions)
{  
  using namespace borg::libxml2::dom;
  
  parser p;
  p.parse_file(input.string().c_str(), -1/*parse_noblanks*/);
  
  document_t doc = p.document();
  
  using namespace borg::libxml2::xpath;
  
  evaluator eval(doc);
  
  for_each(expressions.begin(), expressions.end(), 
           bind(evaluate_expr, ref(eval), _1));
}

//---------------------------------------------------------------------------
int
lexical_test(const std::string &a1, const std::string &a2, 
             const std::string &a3, const std::string &a4)
{
  BORG_PP_VERBOSE_CODE(a1)
  BORG_PP_VERBOSE_CODE(a2)
  BORG_PP_VERBOSE_CODE(a3)
  BORG_PP_VERBOSE_CODE(a4)
      
  return 2;
}

//---------------------------------------------------------------------------
void
interactive_loop(array<string> &expressions)
{
  string cmdline;
  array<string> argv;
  command_parser< array<string> > cmd_parser;

  document_list = input_files.map(&open_document);

  if(!document_list.empty())
    cerr << "Loaded " << document_list.size() << " documents." << endl
         << "Use 'list' command for an overview." << endl;

  ::using_history();
  
  while(running)
  {
    char *cmd_cstr = ::readline((program_name + "> ").c_str());

    if(cmd_cstr == NULL)
      break;

    ::add_history(cmd_cstr);    
    cmdline = cmd_cstr;

    //    
    using namespace spirit;

    typedef const char *iterator_t;
    typedef tree_match<iterator_t> parse_tree_match_t;
    typedef parse_tree_match_t::const_tree_iterator iter_t;
    typedef tree_node< node_val_data<iterator_t, nil_t> > tree_node_t;
    typedef pt_match_policy<iterator_t> match_policy_t;
    typedef scanner_policies<iteration_policy, match_policy_t, action_policy> scanner_policy_t;
    typedef scanner<iterator_t, scanner_policy_t> scanner_t;
    typedef rule<scanner_t> rule_t;

    // Pathname grammar.
/*    rule_t pathname, rootname, rootdir, relpath, filename;
    rule_t name, slash, dot;
        
    name
      = +(alnum_p | ch_p('.'))
      ;

    slash
      = ch_p('/') | ch_p('\\')
      ;

    dot
      = ch_p('.')
      ;

    pathname
      = *rootname >> *rootdir >> relpath
      ;

    rootname 
      = alpha_p >> ':'
      ;

    rootdir 
      = slash 
      | rootname >> slash >> rootdir >> slash
      | rootdir >> slash
      ;

    relpath
      = filename
      | relpath >> slash >> filename
      | relpath >> slash
      ;
    
    filename
      = name
      | dot
      | dot >> dot
      ;
//    rule_t pathname_p = 
//    rule_t filename_p =
    
    tree_parse_info<> info =
      pt_parse(cmd_cstr, pathname//, parser<skip_parser>
           );
    
    cout << "number of trees: " << info.trees.size() << endl;
    
    int i;
    std::pair<iter_t, iter_t> tree_range
      (info.trees.begin(), info.trees.end());
    
    BOOST_FOREACH(tree_node_t node, tree_range)
    {
//      cout << "node #" << ++i << ": " << node.value.value() << endl;
      cout << "node #" << ++i << " children: " << node.children.size() << endl;
    }*/
    
    argv = cmdline.split(' ');

    command_handler p;
    p.parse(argv);
  }

  if(running)
    cerr << endl;
}

int 
main(int argc, char *argv[])
{
  try
  {
    // Get the program name from argv[0]
    filesystem::path program_path(argv[0], filesystem::native);
    
    program_name = filesystem::basename(program_path);
    
    // Parse command line options.
    using namespace borg;
//    using namespace boost;
    using namespace program_options;
    
//    array<filesystem::path> input_files;
//    array<string> input_files;
    array<stdcxx::string> expressions;

    command_line_parser parser(argc, argv);
    options_description desc("Usage: " + program_path.string() + " [options] file ...");
    positional_options_description pd;

    desc.add_options()
      ("help,h", "print out program usage (this message)")
      ("input-file", value< array<stdcxx::string> >(), "input file(s)")
      ("batch,b", "batch mode")
      ("number-nodes,n", "number all nodes in a result set")
      ("expression,e", value(&expressions), "XPath expressions");

    pd.add("input-file", -1);
    
    parser.options(desc);
    parser.positional(pd);
    parser.style(command_line_style::unix_style);

    parsed_options opts = parser.run();
    variables_map params;

    store(opts, params);
    notify(params);

    bool batch_mode = params.count("batch");

    if(params.count("help"))
    {
      cout << desc << endl;
      return 1;
    }

    borg::libxml2::initialize();
    
//    array<string> input_files;
    
    if(params.count("input-file"))
      input_files = params["input-file"].as< array<stdcxx::string> >();
      
    if(batch_mode)
    {
      if(!params.count("input-file"))
      {
        cerr << "Please specify an input file. Use --help for syntax." << endl;
        return 1;
      }
      
      if(!params.count("expression"))
      {
        cerr << "Please specify one or more expressions. Use --help for syntax." << endl;
        return 1;
      }
      
      for_each(input_files.begin(), input_files.end(),
               boost::bind(process_file, boost::arg<1>(), expressions));
    }
    else
      interactive_loop(expressions);
    
    borg::libxml2::shutdown();
  }
  catch(const exception &e)
  {
    cerr << "Exception: " << e.what() << endl;
    return 2;
  }
  
  return 0;
}
