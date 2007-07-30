#ifndef BORG_LIBXML2_XPATH_ADAPTERS_HPP
#define BORG_LIBXML2_XPATH_ADAPTERS_HPP

#include <borg/libxml2/xpath/evaluator.hpp>
#include <borg/libxml2/xpath/result.hpp>
#include <borg/libxml2/xpath/expression.hpp>
#include <borg/libxml2/xpath/nodeset.hpp>

namespace borg { 
namespace libxml2 { 
namespace xpath {

//----------------------------------------------------------------------------
typedef xml::xpath::evaluator_t<traits> evaluator_t;
typedef xml::xpath::evaluator<traits> evaluator;

typedef xml::xpath::result_t<traits> result_t;

typedef xml::xpath::expression_t<traits> expression_t;
typedef xml::xpath::expression<traits> expression;

typedef xml::xpath::result_t<traits> result_t;
typedef xml::xpath::result<traits> result;

typedef xml::xpath::nodeset_t<traits> nodeset_t;
typedef xml::xpath::nodeset<traits> nodeset;

} // namespace xpath
} // namespace libxml2
} // namespace borg

//---------------------------------------------------------------------------
#endif //ndef BORG_LIBXML2_XPATH_ADAPTERS_HPP
