#ifndef BORG_LIBXML2_XPATH_EVALUATOR_HPP
#define BORG_LIBXML2_XPATH_EVALUATOR_HPP

#include <borg/libxml2/traits.hpp>
#include <borg/xml/xpath/expression.hpp>
#include <borg/xml/xpath/evaluator.hpp>

extern "C" int xmlXPathRegisterFunc
  (xmlXPathContextPtr, const xmlChar *, xmlXPathFunction);

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class evaluator_impl<libxml2::traits>
{
public:
  XML_XPATH_TYPES(libxml2::traits)
  
  //! Create a new XPath context.
  //-----------------------------------------------------------------------
  static evaluator_type
  create(document_type const doc)
  {
    return xmlXPathNewContext(doc);
  }

  //-----------------------------------------------------------------------
  static void
  destroy(evaluator_type const eval)
  {
    xmlXPathFreeContext(eval);
  }

  //-----------------------------------------------------------------------
  static expression_type
  compile(evaluator_type const eval, const wchar_type *s)
  {
    return xmlXPathCtxtCompile(eval, s);
  }

  //-----------------------------------------------------------------------
  static result_type
  eval(evaluator_type const eval, expression_type const expr)
  {
    return xmlXPathCompiledEval(expr, eval);
  }

  //-----------------------------------------------------------------------
  template<class CharT>
  static result_type
  eval(evaluator_type const eval, CharT *const expr)
  {
    return xmlXPathEvalExpression(expr, eval);
  }
  
  //-----------------------------------------------------------------------
  template<class CharT>
  static result_type
  register_func(evaluator_type const eval, const CharT *const name,
                xpath_function_type const fn)
  {
    return xmlXPathRegisterFunc(eval, (const wchar_type *)name, fn);
  }
  
};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_EVALUATOR_HPP
