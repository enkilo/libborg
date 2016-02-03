#ifndef BORG_UTIL_LEXICAL_FUNCTION_HPP
#define BORG_UTIL_LEXICAL_FUNCTION_HPP

#include <boost/function.hpp>
#include <boost/range.hpp>
#include <boost/lexical_cast.hpp>
#include <borg/preproc.hpp>
#include <borg/util/dereference_cast.hpp>
#include <borg/util/array.hpp>
#include <borg/util/string.hpp>
#include <borg/wrap/traits/remove_const_reference.hpp>

#include <boost/preprocessor/comma.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>

namespace borg {

//----------------------------------------------------------------------------
#define BORG_UTIL_LEXICAL_ENABLE_IF(trait, T) \
  typename boost::enable_if_c< trait< T >::value, stdcxx::string>::type
  
//----------------------------------------------------------------------------
#define BORG_LEXICAL_APPLY_SIGNATURE(T, is_void) \
  apply(BaseT &base, const util::array<stdcxx::string> &argv \
  BOOST_PP_COMMA_IF(BOOST_PP_NOT(is_void)) \
  BOOST_PP_IF(is_void, , T *result = 0))
  
//----------------------------------------------------------------------------
#define BORG_LEXICAL_APPLY_DECL() \
  template<class BaseT> static \
  BORG_UTIL_LEXICAL_ENABLE_IF(!boost::is_void, typename BaseT::result_type) \
  BORG_LEXICAL_APPLY_SIGNATURE(typename BaseT::result_type, 0)
  
//----------------------------------------------------------------------------
#define BORG_LEXICAL_APPLY_DECL_VOID() \
  template<class BaseT> static \
  BORG_UTIL_LEXICAL_ENABLE_IF(boost::is_void, typename BaseT::result_type) \
  BORG_LEXICAL_APPLY_SIGNATURE(void, 0)
  
//----------------------------------------------------------------------------
template<typename FunctionT>
class lexical_function;

//----------------------------------------------------------------------------
class lexical_invoker
{
public:
  virtual ~lexical_invoker() {}
  virtual stdcxx::string operator()(const util::array<stdcxx::string> &argv) = 0;
};

//----------------------------------------------------------------------------
template<class ReturnT, class ArgumentT>
typename borg::remove_const_reference<ReturnT>::type
argument_cast(const ArgumentT &arg)
{
  typedef typename borg::remove_const_reference<ReturnT>::type return_type;
  return boost::lexical_cast<return_type>(arg);
}  
  
//----------------------------------------------------------------------------
template<class FunctionT, unsigned Arity = boost::function<FunctionT>::arity>
struct lexical_helper;
  
template<class FunctionT>
struct lexical_helper<FunctionT, 0>
{
  typedef lexical_function<FunctionT> outer_type;
  typedef boost::function<FunctionT> base_type;
  typedef FunctionT fn_type;

  BORG_LEXICAL_APPLY_DECL()
  {
    return boost::lexical_cast<stdcxx::string>(base());
  }

  BORG_LEXICAL_APPLY_DECL_VOID()
  {
    base();
    return stdcxx::string();
  }
};  
  
template<class FunctionT>
struct lexical_helper<FunctionT, 1>
{
  typedef lexical_function<FunctionT> outer_type;
  typedef boost::function<FunctionT> base_type;

  BORG_LEXICAL_APPLY_DECL()
  {
    return boost::lexical_cast<stdcxx::string>(base(argument_cast<typename outer_type::arg1_type>(argv[0])));
  }

  BORG_LEXICAL_APPLY_DECL_VOID()
  {
    base(argument_cast<typename outer_type::arg1_type>(argv[0]));
    return stdcxx::string();
  }
};  
  
template<class FunctionT>
struct lexical_helper<FunctionT, 2>
{
  typedef lexical_function<FunctionT> outer_type;
  typedef boost::function<FunctionT> base_type;
  
  BORG_LEXICAL_APPLY_DECL()
  {
    return boost::lexical_cast<stdcxx::string>(base
       (argument_cast<typename outer_type::arg1_type>(argv[0]),
        argument_cast<typename outer_type::arg2_type>(argv[1])));
  }  
};  
  
template<class FunctionT>
struct lexical_helper<FunctionT, 4>
{
  typedef lexical_function<FunctionT> outer_type;
  typedef boost::function<FunctionT> base_type;
  
  stdcxx::string
  apply(const util::array<stdcxx::string> &argv)
  {
    return boost::lexical_cast<stdcxx::string>
      (static_cast<base_type *>(static_cast<outer_type *>(this))->operator()
       (argument_cast<typename outer_type::arg1_type>(argv[0]),
        argument_cast<typename outer_type::arg2_type>(argv[1]),
        argument_cast<typename outer_type::arg3_type>(argv[2]),
        argument_cast<typename outer_type::arg4_type>(argv[3])));
  }  
};  
  
//----------------------------------------------------------------------------
template<typename FunctionT>
class lexical_function
    : public boost::function<FunctionT>
    , public lexical_invoker
    , public lexical_helper<FunctionT>
{
public:
  typedef boost::function<FunctionT> base;
  typedef lexical_helper<FunctionT> helper;
  typedef lexical_invoker invoker;
  static const unsigned arity = base::arity;
  
  lexical_function(FunctionT *fn) : base(fn)
  {}
  
  stdcxx::string
  operator()(const util::array<stdcxx::string> &v)
  {
    util::array<stdcxx::string> argv = v;
    
    if(base::arity && argv.size())
    {
      while(argv.size() < arity)
        argv.push(stdcxx::string());
      
      if(argv.size() > arity)
      {
        stdcxx::string &back = argv[base::arity - 1];
        
        back += ' ';
        back += argv.tail(base::arity).join(' ');
        
        std::cerr << "extra args: " << back << std::endl;
      }
    }
    
//      std::cerr << "extra args: " << argv.tail(base::arity).join(' ') << std::endl;
//      argv.back().append(" " + argv.tail(base::arity).join(' '));

//    array<stdcxx::string> argv = v;
    return helper::apply(dereference_cast<base>(this), argv);
  }
};
  
//---------------------------------------------------------------------------
template<typename FunctionT>
inline static stdcxx::string
lexical_call(FunctionT *fn, const util::array<stdcxx::string> &argv)
{
  lexical_function<FunctionT> lex_fn(*fn);
  return lex_fn(argv);
}  
  
//---------------------------------------------------------------------------

}// namespace borg

#endif //ndef BORG_UTIL_LEXICAL_FUNCTION_HPP
