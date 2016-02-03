#ifndef BORG_UTIL_COMMAND_PARSER_HPP
#define BORG_UTIL_COMMAND_PARSER_HPP

#include <boost/range.hpp>
#include <boost/tuple/tuple.hpp>
#include <borg/util/lexical_function.hpp>

namespace borg {

//----------------------------------------------------------------------------
struct no_such_command
{
  static bool handle_error(const stdcxx::string &str)
  {
    std::cerr << str << std::endl;
    return false;
  }
};
  
//----------------------------------------------------------------------------
template<class ContainerT, class ErrorHandler = no_such_command >
class command_parser
{
public:
  typedef typename ContainerT::value_type value_type;
  typedef typename ContainerT::const_iterator token_iterator;
  typedef boost::tuple<lexical_invoker *, const char *> command_type;
  typedef std::pair<value_type, command_type> assoc_type;
  
  command_parser()
  {}
  
  ~command_parser()
  {
    assoc_type cmd;
      
    BOOST_FOREACH(cmd, m_cmds)
    {
      lexical_invoker *i = boost::get<0>(cmd.second);
      delete i;
    }
  }
  
  template<class FunctionT>
  lexical_function<FunctionT> &
  add_command(const value_type &name, FunctionT *fn, const char *desc)
  {
    lexical_function<FunctionT> *ret = new lexical_function<FunctionT>(*fn);
    
    m_cmds[name] = command_type(ret, desc);
    return *ret;
  }

  template<class FunctionT>
  lexical_function<FunctionT> &
  set_default(FunctionT *fn)
  {
    lexical_function<FunctionT> *ret = new lexical_function<FunctionT>(*fn);
    m_default = ret;
    return *ret;
  }
  
  template<class RangeT>
  bool
  parse(const RangeT &rng)
  {
//    std::cout << "range size: " << boost::size(rng) << std::endl;
    return parse(boost::begin(rng), boost::end(rng));
  }

  bool
  parse(const token_iterator &b, const token_iterator &e)
  {
    token_iterator it = b;
    command_type cmd = m_cmds[*b];
    lexical_invoker *fn = boost::get<0>(cmd);

    // No invoker?
    if(fn == 0)
    {
      if((fn = m_default) == 0)
        return reinterpret_cast<ErrorHandler *>(this)->handle_error("No such command: " + *b);
    }
    
    if(fn != m_default)
      ++it;

    util::array<stdcxx::string> argv(it, e);
    
//    std::cout << "function pointer: " << fn << std::endl;
    
    (*fn)(argv);
    return true;
  }

private:
  std::map<value_type, command_type> m_cmds;
  lexical_invoker *m_default;
};

}// namespace borg
//---------------------------------------------------------------------------
#endif //ndef BORG_UTIL_COMMAND_PARSER_HPP
