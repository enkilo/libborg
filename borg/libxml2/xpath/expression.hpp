#ifndef BORG_LIBXML2_XPATH_EXPRESSION_HPP
#define BORG_LIBXML2_XPATH_EXPRESSION_HPP

#include <boost/utility/enable_if.hpp>
#include <borg/libxml2/traits.hpp>
#include <borg/xml/xpath/expression.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class expression_impl<libxml2::traits>
{
public:
  XML_XPATH_TYPES(libxml2::traits)
  
  //! Compile XPath expression from string.
  //! Enabled only if CharT is actually a string.
  //-----------------------------------------------------------------------
  template<class CharT>
  static typename boost::enable_if_c
    < boost::is_integral<CharT>::value, expression_type >::type
  compile(const CharT *str)
  {
    return xmlXPathCompile
      (reinterpret_cast<const wchar_type *>(str));
  }
  
  //-----------------------------------------------------------------------
  template<class CharT>
  static expression_type
  compile(evaluator_type const ctx, const CharT &str)
  {
    return xmlXPathCtxtCompile
      (ctx, reinterpret_cast<const wchar_type *>(str));
  }
  
  //! Free a compiled XPath expression.
  //-----------------------------------------------------------------------
  static void
  free(expression_type const expr)
  {
    xmlXPathFreeCompExpr(expr);
  }

  //! Evaluate XPath expression in the specified context.
  //-----------------------------------------------------------------------
  static result_type
  eval(expression_type const expr, evaluator_type const ctx)
  {
    return xmlXPathCompiledEval(expr, ctx);
  }

/*  static bool
  eval_to_boolean(expression_type const expr, evaluator_type const ctx)
  {
    return xmlXPathCompiledEvalToBoolean(expr, ctx);
  }*/
};
  
//---------------------------------------------------------------------------
template<>
class expression<libxml2::traits>
    : public expression_t<libxml2::traits>
{
  typedef expression_impl<libxml2::traits> impl;
  typedef expression_t<libxml2::traits> base_type;

public:
  template<class CharT>
  expression(const string<CharT, libxml2::traits> &str) 
      : base_type(impl::compile(str))
      , m_delete(true)
  {}

  template<class CharT>
  expression(const CharT *str)
      : base_type(impl::compile(str))
      , m_delete(true)
  {}

  ~expression()
  {
    if(m_delete)
      impl::free(unwrap_cast(*this));
  }
  
private:
  bool m_delete;
};
  
//---------------------------------------------------------------------------
  
} // namespace xpath
} // namespace xml

//---------------------------------------------------------------------------

namespace libxml2 {
namespace xpath {

typedef xml::xpath::expression_impl<traits> expression_impl;
typedef xml::xpath::expression_t<traits> expression_t;
typedef xml::xpath::expression<traits> expression;
  
} // namespace xpath
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_EXPRESSION_HPP
