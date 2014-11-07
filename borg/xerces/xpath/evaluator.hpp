#ifndef BORG_XERCES_XPATH_EVALUATOR_HPP
#define BORG_XERCES_XPATH_EVALUATOR_HPP

#include <borg/xerces/traits.hpp>
#include <borg/xml/xpath/expression.hpp>
#include <borg/xml/xpath/evaluator.hpp>

namespace borg { 
namespace xml { 
namespace xpath {

//----------------------------------------------------------------------------
template<>
class evaluator_impl<xerces::traits>
{
public:
  XML_XPATH_TYPES(xerces::traits)
  
  //-----------------------------------------------------------------------
  //-----------------------------------------------------------------------
  template<class ExpressionT>
  xerces::traits::result_type
  evaluate(document_type const eval, const ExpressionT &expr)
  {
    return eval->evaluate
      (expr, eval->getDocumentElement(), 
       eval->createNSResolver(eval->getDocumentElement()), 0);
  }
};

} // namespace xpath
} // namespace xml
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_XERCES_XPATH_EVALUATOR_HPP
